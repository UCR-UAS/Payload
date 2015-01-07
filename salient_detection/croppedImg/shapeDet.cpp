// salient_detection.cpp : Defines the entry point for the console application.

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include <sstream>
#include <vector>
#include <stdio.h>

using namespace std;
using namespace cv;

int imageCounter = 490;
string imgName = "IMG_0494_22.JPG";
Mat letter, shape;


////////////////Functions/////////////////////////////
Mat segmentation(Mat roi);
Mat gradient(Mat src);
Mat CannyThreshold(Mat src, Mat grad);
void findObject(Mat mask, Mat src);
//////////////////////////////////////////////////////


int main() {
	Mat roi, mask;
	roi = imread(imgName);
	imshow("og image", roi);
	
		mask = segmentation(roi);
		imshow("mask", mask);
		findObject(mask, roi);
		while(1) {
		cvWaitKey(1);	}	
	
	
}

void findObject(Mat mask, Mat src) {
	Mat threshold_output;
	Mat roi;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	char buffer[40];


	/// Find contours
	findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	cout << "contours found" << endl;
	/// Approximate contours to polygons + get bounding rects and circles
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());
	//cout << contours.size() << endl;
	for (int i = 0; i < contours.size(); i++)
	{
		cout << contourArea(contours[i]) << endl;
		if (contourArea(contours[i]) < 600)
		{	
			approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
			boundRect[i] = boundingRect(Mat(contours[i]));
			roi = src(boundRect[i]);
			
			sprintf(buffer, "croppedImg/IMG_0%d_%d.JPG", imageCounter,i);

			imwrite(buffer, roi);
		}
	
	}

	cout << "bounded rectangles" << endl;
	/// Draw polygonal contour + bonding rects + circles
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		//cout << i << endl;
		Scalar color = Scalar(0, 255, 0);
		drawContours(src, contours_poly, i, color, 1, 1, vector<Vec4i>(), 0, Point());
		//rectangle(src, boundRect[i].tl(), boundRect[i].br(), color, 2, 1, 0);
	} 
	cout << "rectangles drawn" << endl;
	namedWindow("Contours", CV_WINDOW_NORMAL);
	imshow("Contours", src);
};

Mat segmentation(Mat roi){
	Mat hsl,h,s,l,hg,lg, blkWhte, grad;
	
	GaussianBlur(roi, roi, Size(3, 3), 0, 0, BORDER_DEFAULT);

	vector<Mat> channels(3);

	cvtColor(roi, hsl, CV_RGB2HLS);
	split(hsl, channels);


	h = channels[1];
	s = channels[0];
	l = channels[2];

	hg = gradient(h);
	lg = gradient(l);
	
	grad = h + l;

	grad = CannyThreshold(grad,grad);

	h = CannyThreshold(h,h);

	grad = (grad | h);
	
	return grad;
	
	namedWindow("salient objects", WINDOW_NORMAL);
	imshow("salient objects", grad);
};

Mat gradient(Mat src) {
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, grad, gradh, gradl;

	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(src, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(src, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// Total Gradient (approximate)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	
	return grad;
};

Mat CannyThreshold(Mat src, Mat grad)
{
	Mat detected_edges;
	int kernel_size = 3;
	int lowThreshold = 70;
	int ratio = 3;
	int morph_elem = 1;
	int morph_size = 2;
	/// Reduce noise with a kernel 3x3
	blur(grad, detected_edges, Size(1, 1));

	/// Canny detector
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * 1 + 1, 2 * 1 + 1),
		Point(1, 1));

	//dilate(detected_edges, detected_edges, element);
	//erode(detected_edges, detected_edges,element);
	//element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	//morphologyEx(detected_edges, detected_edges, MORPH_OPEN, element);
	
	return detected_edges;
};

