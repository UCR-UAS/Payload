#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <string>
#include <utility>
#include "RobustMatcher.h"
#include "shape_detector.h"
#include <math.h>

using namespace std;
using namespace cv;



shape_detector::shape_detector()
{
  
}
float verifyCircle(cv::Mat dt, cv::Point2f center, float radius, std::vector<cv::Point2f> & inlierSet)
{
 unsigned int counter = 0;
 unsigned int inlier = 0;
 float minInlierDist = 2.0f;
 float maxInlierDistMax = 100.0f;
 float maxInlierDist = radius/25.0f;
 if(maxInlierDist<minInlierDist) maxInlierDist = minInlierDist;
 if(maxInlierDist>maxInlierDistMax) maxInlierDist = maxInlierDistMax;

 // choose samples along the circle and count inlier percentage
 for(float t =0; t<2*3.14159265359f; t+= 0.05f)
 {
     counter++;
     float cX = radius*cos(t) + center.x;
     float cY = radius*sin(t) + center.y;

     if(cX < dt.cols)
     if(cX >= 0)
     if(cY < dt.rows)
     if(cY >= 0)
     if(dt.at<float>(cY,cX) < maxInlierDist)
     {
        inlier++;
        inlierSet.push_back(cv::Point2f(cX,cY));
     }
 }

 return (float)inlier/float(counter);
}


inline void getCircle(cv::Point2f& p1,cv::Point2f& p2,cv::Point2f& p3, cv::Point2f& center, float& radius)
{
  float x1 = p1.x;
  float x2 = p2.x;
  float x3 = p3.x;

  float y1 = p1.y;
  float y2 = p2.y;
  float y3 = p3.y;

  // PLEASE CHECK FOR TYPOS IN THE FORMULA :)
  center.x = (x1*x1+y1*y1)*(y2-y3) + (x2*x2+y2*y2)*(y3-y1) + (x3*x3+y3*y3)*(y1-y2);
  center.x /= ( 2*(x1*(y2-y3) - y1*(x2-x3) + x2*y3 - x3*y2) );

  center.y = (x1*x1 + y1*y1)*(x3-x2) + (x2*x2+y2*y2)*(x1-x3) + (x3*x3 + y3*y3)*(x2-x1);
  center.y /= ( 2*(x1*(y2-y3) - y1*(x2-x3) + x2*y3 - x3*y2) );

  radius = sqrt((center.x-x1)*(center.x-x1) + (center.y-y1)*(center.y-y1));

}



std::vector<cv::Point2f> getPointPositions(cv::Mat binaryImage)
{
 std::vector<cv::Point2f> pointPositions;

 for(unsigned int y=0; y<binaryImage.rows; ++y)
 {
     //unsigned char* rowPtr = binaryImage.ptr<unsigned char>(y);
     for(unsigned int x=0; x<binaryImage.cols; ++x)
     {
         //if(rowPtr[x] > 0) pointPositions.push_back(cv::Point2i(x,y));
         if(binaryImage.at<unsigned char>(y,x) > 0) pointPositions.push_back(cv::Point2f(x,y));
     }
 }

 return pointPositions;
}
string shape_detector::detect( vector < Point > c, Mat img)
{
  string s = "unidentified";
  double peri = arcLength(c,true);
  vector<Point> approx;
  approxPolyDP(c,approx,.008*peri,true);
  cout << "Size" << approx.size() << endl;
  imshow("InputImg",img);
  waitKey(0);
  if(approx.size() == 3)
    s = "Triangle";
  else if (approx.size() == 4)
  {
    s = "Square";
  }
  else if (approx.size() == 5)
    s = "Pentagon";
  else if (approx.size() == 10)
    s = "Star";
  else if (approx.size() == 12)
    s = "Plus";
  else
  {
    //image needs to be output of canny edge detection
    GaussianBlur(img,img,Size(3,3),2,2);
    vector < Vec3f > circles;
    Mat canny;
    Mat _img;
    //double otsu_thresh = threshold(img,_img,0,255,CV_THRESH_BINARY|CV_THRESH_OTSU);
    //double high = otsu_thresh,low = otsu_thresh * .5;
    //Canny(img,canny,low,high);




    //Using image descriptrs

    RobustMatcher rm = RobustMatcher();
    Mat img1;
    vector<KeyPoint> img1_keypts;
    Mat img1_descriptors;
    Mat img2;
    vector<KeyPoint> img2_keypts;
    Mat img2_descriptors;
    vector < DMatch >  matches;
    img1 = imread("templates/Circle.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    int r = 300 / img.cols;
    Size dim = Size(300,(int)img.rows*r);
    resize(img1,img1,dim,0,0,INTER_AREA);
    img2 = img;
    //Ptr<FeatureDetector> detector = ORB::create(1500,1.2f,8,20);
    //Ptr<DescriptorExtractor> extractor = ORB::create();
    //Ptr<DescriptorMatcher> matcher = makePtr<BFMatcher>((int)cv::NORM_HAMMING,false);

    //detector->detect(img1,img1_keypts);
    //detector->detect(img2,img2_keypts);

    //extractor->compute(img1,img1_keypts,img1_descriptors);
    //extractor->compute(img2,img1_keypts,img2_descriptors);

    //matcher->match(img1_descriptors,img2_descriptors,matches);
    
    //Mat fund = rm.match(img1,img2,matches,img1_keypts,img2_keypts);

    Mat img_match;
    Mat color = img;
    cout <<"Type"<< img.type() << endl;

    cv::Mat mask = img > 0;
    std::vector<cv::Point2f> edgePositions;
    imshow("mask",mask);
    waitKey(0);
    edgePositions = getPointPositions(mask);

    cv::Mat dt;
    cv::distanceTransform(255-mask, dt,CV_DIST_L2, 3);

    //TODO: maybe seed random variable for real random numbers.
    cout << "Contour Area: " << contourArea(c) << endl;
    float realA = contourArea(c);

    unsigned int nIterations = 0;
    
    char quitKey = 'q';
    std::cout << "press " << quitKey << " to stop" << std::endl;
    vector<double> nums;
    while(nIterations < 15000)
      {
        //RANSAC: randomly choose 3 point and create a circle:
        //TODO: choose randomly but more intelligent, 
        //so that it is more likely to choose three points of a circle. 
        //For example if there are many small circles, it is unlikely to randomly choose 3 points of the same circle.
        unsigned int idx1 = rand()%edgePositions.size();
        unsigned int idx2 = rand()%edgePositions.size();
        unsigned int idx3 = rand()%edgePositions.size();

        // we need 3 different samples:
        if(idx1 == idx2) continue;
        if(idx1 == idx3) continue;
        if(idx3 == idx2) continue;

        // create circle from 3 points:
        cv::Point2f center; float radius;
        getCircle(edgePositions[idx1],edgePositions[idx2],edgePositions[idx3],center,radius);
        if(isinf(radius))
          continue;

        float minCirclePercentage = 0.2f;

        // inlier set unused at the moment but could be used to approximate a (more robust) circle from alle inlier
        std::vector<cv::Point2f> inlierSet;

        //verify or falsify the circle by inlier counting:
        float cPerc = verifyCircle(dt,center,radius, inlierSet);

        if(cPerc >= minCirclePercentage)
          {
            std::cout << "accepted circle with " << cPerc*100.0f << " % inlier" << std::endl;
            // first step would be to approximate the circle iteratively from ALL INLIER to obtain a better circle center
            if(cPerc*100.0f < 95.0f && (3.14159f * (radius*radius)) > realA/2 && (3.14159f * (radius*radius))< 2*realA  )
              nums.push_back(cPerc*100.0f);
            //std::cout << "circle: " << "center: " << center << " radius: " << radius << std::endl;
            cout << "Area: " << 3.1415f * radius * radius << endl;
            cv::circle(color, center,radius, cv::Scalar(255,255,0),1);
            // accept circle => remove it from the edge list
            cv::circle(mask,center,radius,cv::Scalar(0),10);
            //update edge positions and distance transform
            edgePositions = getPointPositions(mask);
            cv::distanceTransform(255-mask, dt,CV_DIST_L1, 3);
          }
        cv::Mat tmp;
        mask.copyTo(tmp);
        // prevent cases where no fircle could be extracted (because three points collinear or sth.)
        // filter NaN values
        if((center.x == center.x)&&(center.y == center.y)&&(radius == radius))
          {
            cv::circle(tmp,center,radius,cv::Scalar(255));
          }
        else
          {
            std::cout << "circle illegal" << std::endl;
          }
        
        ++nIterations;
      }

    double sum = 0;
    for(unsigned i = 0; i < nums.size();i++)
      {
        sum += nums.at(i);
      }
    cout <<"Median Value : "<< nums[(nums.size()+1)/2] << endl;
    cout <<"Average Value: "<< sum/nums.size() << endl;



    s = "Circle";
  }
  cout << "Contour Area: " << contourArea(c) << endl;
  imshow("img",img);
  waitKey(0);
  return s;
}

int main(int argc, char** argv)
{
  if (argc < 2)
    return -1;
  Mat img = imread(argv[1]);
  int r = 300 / img.cols;
  Size dim = Size(300,(int)img.rows*r);

  Mat resized;
  resize(img,resized,dim,0,0,INTER_AREA);
  float ratio = img.rows / (float)resized.rows;
  Mat gray;
  cvtColor(resized,gray,COLOR_RGB2GRAY);
  GaussianBlur(gray,gray,Size(5,5),.2,.2);

  Mat thresh;
  threshold(gray,thresh,230,255,THRESH_BINARY);
  imshow("img",resized);
  imshow("thresh",thresh);
  waitKey(0);

  vector< vector <Point> > c;
  findContours(thresh,c,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_TC89_KCOS );
  shape_detector sd;
  //sd.detect(c,gray);

  Mat cons(thresh.rows,thresh.cols,CV_8U);
  //cvtColor(cons,cons,COLOR_GRAY2BGR);
  for(unsigned i = 0 ; i < c.size();i++)
   {
     //draw contour above certain area
     drawContours(cons,c,-1,Scalar(255,55,255),4,8);
     Moments m = moments(c.at(i));
     float cX = (((int)m.m10/m.m00)*ratio);
     float cY = (((int)m.m01/m.m00)*ratio);
     string s = sd.detect(c.at(i),thresh);
     cout << s << endl;

   }
  imshow("cons",cons);
  waitKey(0);

  return 0;
}
