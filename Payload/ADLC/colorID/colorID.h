#ifndef COLORID_H
#define COLORID_H
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <string>
#include <assert.h> 
using namespace std;
using namespace cv::ml;
using namespace cv;
string colorClassify(float r, float g, float b);
string colorID(Mat src);

#endif
