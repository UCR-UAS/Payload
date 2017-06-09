//FrequencySaliencyDetection7.2 simplified so transmission and loading of image is done elsewhere

#include <iostream>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

void fftShift(Mat image);
void HighPassRect(Mat image, float PercentageLow1);
void CropTargets(Mat imgThresholded, Mat OriginalImage, int sizeReduced, string fileName, string imgName);


int main(int argc, char** argv)
{
  Mat I, rawr,ImageHSV,ReducedIMG,HSVplane,BorderedImage;
  vector<Mat> HSVplanes;
  Mat OriginalImage;

  if(argc < 2)
    return -1;
  OriginalImage = imread(argv[1]);

  // Reduce image here
  //why 5 i have no idea
  int SizeReduced = 5;
  resize(OriginalImage,ReducedIMG,Size(OriginalImage.cols/SizeReduced,
                                       OriginalImage.rows/SizeReduced));

  //Convert Colors to HSV
  cvtColor(ReducedIMG,ImageHSV,COLOR_BGR2HSV);
  //will split into three channels H,S,V
  split(ImageHSV,HSVplanes);
  //gets Value plane of HSV
  HSVplane = HSVplanes[2];
  I = HSVplane;

  //will expand the input image to an optimal size
  Mat padded;
  //m is the optimal discrete fourier transform size
  int m = getOptimalDFTSize(I.rows);

  //add zero values on the border
  int n = getOptimalDFTSize(I.cols);
  copyMakeBorder(I,padded,0,m-I.rows,0,n-I.cols,BORDER_CONSTANT,Scalar::all(0));

  
  //show padded for debugging
  //imshow("padded",padded);
  //waitKey(0);

  Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(),CV_32F)};
  //imaginary image?
  Mat complexI;
  //merge planes and ComplexI
  merge(planes,2,complexI);

  //discrete fourier transform 
  for(int ii = 0; ii < 1; ii++) dft(complexI,complexI);
  split(complexI,planes);

  Mat magI, phaseI;
  cartToPolar(planes[0],planes[1],magI,phaseI);
  //switches to logarithmic scale
  magI += Scalar::all(1);
  log(magI,magI);
  fftShift(magI);

  Mat magAverage, magRes, Sum, InverseFourier, kernel;

  medianBlur(magI,magAverage,5);

  magRes = magI - magAverage;
  exp(magRes,magRes);

  polarToCart(magRes,phaseI,planes[0],planes[1]);

  merge(planes,2,Sum);

  dft(Sum,InverseFourier,cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT);
  pow(InverseFourier,2,InverseFourier);
  GaussianBlur(InverseFourier,InverseFourier,Size(3,3),0);
  normalize(InverseFourier,InverseFourier,0,1,NORM_MINMAX);
  //imshow("INverse Four",InverseFourier);
  //waitKey(0);

  Mat Threshold;
  //THreshold the image
  inRange(InverseFourier,.4,1,Threshold);

  CropTargets(Threshold,OriginalImage,SizeReduced,"result.jpg",argv[1]);

  return 0;
}

void fftShift(Mat image)
{
  //reararnge the quadrants of the Fourier image so that the origin is at the image center
  int cx = image.cols/2;
  int cy = image.rows/2;

  //top left
  Mat q0(image,Rect(0,0,cx,cy));
  //topRight
  Mat q1(image,Rect(cx,0,cx,cy));
  //bottom left
  Mat q2(image,Rect(0,cy,cx,cy));
  //bottom right
  Mat q3(image,Rect(cx,cy,cx,cy));

  //swap topleft with bottom right
  Mat tmp;
  q0.copyTo(tmp);
  q3.copyTo(q0);
  tmp.copyTo(q3);

  //swap quadrant top right with bottom left
  q1.copyTo(tmp);
  q2.copyTo(q1);
  tmp.copyTo(q2);
}

void HighPassRect(Mat image, float PercentageLow1)
{
  float PercentageLow2 = (1-PercentageLow1) + 1;
  Point2f PointLow1 = Point2f((image.cols/2)*PercentageLow1,
                              (image.rows/2)*PercentageLow1);
  Point2f PointLow2 = Point2f((image.cols/2)*PercentageLow2,
                              (image.rows/2)*PercentageLow2);
  rectangle(image,PointLow1,PointLow2,Scalar(0,0,0),-1,8,0);
}

void CropTargets(Mat imgThresh, Mat OriginalImage, int sizeReduced, string FileName,string imgName)
{
  Mat BorderedImage;
	float BorderSize = 0.1;
	int top = (int)(BorderSize*OriginalImage.rows); int bottom = (int)(BorderSize*OriginalImage.rows);
	int left = (int)(BorderSize*OriginalImage.cols); int right = (int)(BorderSize*OriginalImage.cols);
	copyMakeBorder(OriginalImage, BorderedImage, top, bottom, left, right, BORDER_CONSTANT, Scalar::all(0));

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	/// Find contours
	findContours(imgThresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
  //imshow("Thres",imgThresh);
  imwrite("./SpecMap.jpg",imgThresh);
  //waitKey(0);

	/// Get the moments
	vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		mu[i] = moments(contours[i], false);
	}

	///  Get the mass centers:
	vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	/// Draw contours
	vector<Mat> ROI;
	Mat drawing = Mat::zeros(imgThresh.size(), CV_8UC3);
	//printf("\t Info: Area and Contour Length \n");

	int index = 0;
	RNG rng;
	for (int i = 0; i < contours.size(); i++) {
		int area;
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		//printf(" * Contour[%d] - Area (M_00) = %.2f - X %.2f Y %.2f - Length: %.2f \n", i, mu[i].m00, mc[i].x, mc[i].y, arcLength(contours[i], true));

		area = contourArea(contours[i]);

		int CaptureArea = 100;

		if ((mc[i].x >= 0) && (mc[i].y >= 0)) {
			//cout << "x:" << (int)(mc[i].x * SizeReduced) - CaptureArea/2 + int(BorderSize*OriginalImage.cols) + CaptureArea << "y:" << (int)(mc[i].y * SizeReduced) - CaptureArea/2 + int(BorderSize*OriginalImage.rows) + CaptureArea << " " << BorderedImage.cols << " " << BorderedImage.rows << "\n \n";
			ROI.push_back(BorderedImage(Rect((int)(mc[i].x * sizeReduced) - (CaptureArea/2) + int(BorderSize*OriginalImage.cols),(int)(mc[i].y*sizeReduced)- (CaptureArea/2) + int(BorderSize*OriginalImage.rows), CaptureArea, CaptureArea)));
			
			index++;
		}
	}
	FileName.append(":");
  string command = "mkdir -p res";
  command += imgName;
  system(command.c_str());
  string name = "res";
  name += imgName + "/" + FileName;
  for(int i =0; i < (index); i++)
    {
      ostringstream convert;
      convert << i;
      string ROIString = name;
      ROIString.append(convert.str());
      string ROIStringFileType = ROIString;
      imwrite(ROIStringFileType,ROI[i]);
    }
}
