#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <string>
#include <assert.h>
#include "colorID.h"

using namespace std;
using namespace cv::ml;
using namespace cv;


struct Pair {
    int A;
    int B;

    bool operator<( const Pair& rhs ) const
        { return A < rhs.A; }
};

string colorClassify(float r, float g, float b){
  if(r > 200 && g > 200 && b > 200){
     return  "white";
   }
   else if (r < 65 && g < 40 && b < 40){
     return "black";
   }
   else if( ( r <= 255 && r > 191) && ( g < 229 && g > 55 ) && ( b >= 0 && b < 215 )){
      return "orange";
   }

   else if ((r <= 255 && r > 171 ) && (g <=255 && g > 175 ) && (b >= 5 && b < 90 ) )
   {
    return "yellow";
   }

   else if((r <=255 && r > 134) && (g < 55 && g >=0 ) && (b >=0  && b < 47)){
     return "red";
   }

   else if(( r >= 0 && r < 30 ) && (g < 120 && g > 30 ) && ( b <=255 && b > 171 ) ){
     return "blue";
   }

   else if(( r > 30 && r < 110) && (g > 74 && g <= 255 ) && ( b >= 0 && b < 50  ) ){
     return "green";
   }

   else if((r > 110 && r < 234 )&& ( g > 10 && g < 230 ) && (b > 100 && b <=255 )){
     return "purple";
   }
   return "brown";
 }

vector<string> colorID(Mat src) {

  GaussianBlur(src,src,Size(7,7), .1,.1);

  //imshow("blur", src);
  //waitKey(0);

  Mat samples(src.rows * src.cols, 3, CV_32F);
 for( int y = 0; y < src.rows; y++ )
   for( int x = 0; x < src.cols; x++ )
     for( int z = 0; z < 3; z++)
       samples.at<float>(y + x*src.rows, z) = src.at<Vec3b>(y,x)[z];

 int clusterCount = 4;
 vector<int>labels;
 int attempts = 2;
 Mat centers;//holds colors for each cluster
 kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers );

 //cout << "centers:"<<endl << centers << endl << endl;
 Mat new_image( src.size(), src.type() );
 // Mat new_image;
 // src.copyTo(new_image);
 for( int y = 0; y < src.rows; y++ )
   for( int x = 0; x < src.cols; x++ )
   {
     int cluster_idx = labels[y + x*src.rows];
     //change the rgb values
     new_image.at<Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
     new_image.at<Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
     new_image.at<Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
   }

 //imshow( "clustered image", new_image );
 //waitKey(0);
 //count the cluster count


 std::vector<int> counts(clusterCount);
 std::vector<int> tracker(clusterCount);
 std::vector<Pair> hopes;

//count labels
 for(unsigned i = 0; i < labels.size()-1; ++i){
   counts.at(labels.at(i)) +=1;
 }

 //set up the tracker
for(unsigned i = 0; i < tracker.size(); ++i){
  tracker.at(i) = i;
}

//std::cout << endl << endl << endl;
 for(unsigned i = 0; i < tracker.size(); ++i){
   //std::cout << i <<": " << centers.at<float>(i,2) << ", " << centers.at<float>(i,1) << ", " << centers.at<float>(i,0) << ":  " << counts[i];
   Pair p;
   p.A = counts[i];
   p.B = i;
   hopes.push_back(p);
   //std::cout << endl;
 }

std::sort(hopes.begin(),hopes.end());

/*
for(unsigned i = 0; i < hopes.size(); ++i){
  cout << hopes[i].B << " " <<  hopes[i].A;
  cout << endl;
}
cout << endl;
*/

 //have my clusters sorted
 //cluster count index
 unsigned first = tracker.at(hopes[clusterCount - 1].B);
 unsigned second = tracker.at(hopes[clusterCount - 2].B);

 Vec3b color_1;
 color_1[0] = centers.at<float>(first,0);
 color_1[1] = centers.at<float>(first,1);
 color_1[2] = centers.at<float>(first,2);

 float r1 = (float)color_1[2];
 float g1 = (float)color_1[1];
 float b1 = (float)color_1[0];

//cout << r1 << "," <<g1 << ","<<b1 << endl;

 Vec3b color_2;
 color_2[0] = centers.at<float>(second,0);
 color_2[1] = centers.at<float>(second,1);
 color_2[2] = centers.at<float>(second,2);

 float r2 = (float)color_2[2];
 float g2 = (float)color_2[1];
 float b2 = (float)color_2[0];
//cout << r2 << "," <<g2 << ","<<b2 << endl;
//store the colors
//first index holds biggest color
//second index holds the second biggest color
vector<string> colors;
colors.push_back(colorClassify(r1,g1,b1));
colors.push_back(colorClassify(r2,g2,b2));


return colors;
}

int main(int argc, char**argv) {


    string input("red.jpg");
    //string input("obj.jpg");
    Mat im = imread(input);
    resize(im,im,Size(800,600));
    if(!im.data)
        return -1;
    std::vector<string> v =  colorID(im);
    for(unsigned i = 0; i < v.size(); ++i){
        std::cout <<"cluster " << i << ": " << v.at(i) << endl;
    }
    //waitKey(0);

    return 0;
}
