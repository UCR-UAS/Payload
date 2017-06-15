#ifdef _SHAPE_SEG_
#define _SHAPE_SEG_
#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

bool blackWhite(Mat chans[3], int y, int x);
int numPixels(Mat& I);
Mat saliencySegmentation(string f);


#endif
