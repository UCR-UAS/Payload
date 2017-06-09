#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <string>
#include <utility>
#include "shape_detector.h"
#include <math.h>

using namespace std;
using namespace cv;



shape_detector::shape_detector()
{
  
}



vector<uchar> preproccess(Mat img)
{
  int r = 200 / img.cols;
  Size dim = Size(200,(int)img.rows*r);

  Mat resized;
  resize(img,resized,dim,0,0,INTER_AREA);
  float ratio = img.rows / (float)resized.rows;
  Mat gray;
  cvtColor(resized,gray,COLOR_RGB2GRAY);
  GaussianBlur(gray,gray,Size(5,5),.2,.2);

  Mat thresh;
  threshold(gray,thresh,230,255,THRESH_BINARY);

  vector< vector <Point> > c;
  findContours(thresh,c,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_TC89_KCOS );
  //sd.detect(c,gray);
  drawContours(thresh,c,-1,(255,255,255),2);
  std::vector<uchar> array;
  if (thresh.isContinuous()) {
    array.assign(thresh.datastart, thresh.dataend);
  } else {
    for (int i = 0; i < thresh.rows; ++i) {
      array.insert(array.end(),thresh.ptr<uchar>(i), thresh.ptr<uchar>(i)+thresh.cols);
    }
  }
  return array;
}






string shape_detector::detect(  Mat img)
{
  string s = "unidentified";
    int res;
    Ptr<ml::SVM> svm_classifier;
    svm_classifier = svm_classifier->load("svm.xml");
    vector<uchar> imgp = preproccess(img);

    Mat newImg(1,imgp.size(),CV_32F);
    for(unsigned i = 0; i < imgp.size(); i++)
      {
        newImg.at<float>(0,i) = imgp.at(i);
      }
    res = svm_classifier->predict(newImg);
    switch(res)
    {
    case 0: s = "Circle";break;
    case 1: s = "Semicircle"; break;
    case 2: s = "QuarterCircle"; break;
    case 3: s = "Diamond"; break;
    case 4: s = "Plus"; break;
    case 5: s = "Rectangle"; break;
    case 6: s = "Square"; break;
    case 7: s = "Star"; break;
    case 8: s = "Trapezoid"; break;
    case 9: s = "Triangle"; break;
    }
  return s;
}

int main(int argc, char** argv)
{
  if (argc < 2)
    return -1;
  Mat img = imread(argv[1]);
  shape_detector sd;
     string s = sd.detect(img);
     cout << s << endl;

  return 0;
}
