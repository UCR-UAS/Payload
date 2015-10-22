#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include <sstream>
#include <vector>
#include <stdio.h>

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
}

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

	dilate(detected_edges, detected_edges, element);
	//erode(detected_edges, detected_edges,element);
	//element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	//morphologyEx(detected_edges, detected_edges, MORPH_OPEN, element);
	
	return detected_edges;
}

void Dimage::salient_detection() {
	Mat hsl,h,s,l,hg,lg, blkWhte, grad, img;
	vector<vector<Point> > contours;
	Mat src = this->image;
	Mat cropped;
	string buffer;

	GaussianBlur(this->image, img, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cout << "blurred" << endl;
	vector<Mat> channels(3);

	cvtColor(img, hsl, CV_RGB2HLS);
	split(hsl, channels);
	cout << "splitted" << endl;

	h = channels[1];
	s = channels[0];
	l = channels[2];

	hg = gradient(h);
	lg = gradient(l);
	
	grad = h + l;

	grad = CannyThreshold(grad,grad);

	h = CannyThreshold(h,h);
	
	cout << "thresholded" << endl;
	grad = (grad & h);
		

	/// Find contours
	findContours(grad, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	/// Approximate contours to polygons + get bounding rects and circles
	cout << "countours found" << endl;
	cout << contours.size() << endl;	
	for (int i = 0; i < contours.size(); i++)
	{
		cout << "i: " << i << endl;

		if (contourArea(contours.at(i)) < 600)
		{	cout << "in da if" << endl;
			
			approxPolyDP(Mat(contours.at(i)), contours_poly.at(i), 3, true);
			cout << "at roi" << endl;
			//boundingRect(Mat(contours[i]));
			Rect roi = boundingRect(Mat(contours.at(i)));
			
			/*cropped = src(roi);
			
			imshow("Cropped image", cropped);
			cvWaitKey(0);*/ 
			this->ROI.push_back(roi);
			cout << "size of victor: " << this->ROI.size() << endl;
		}
	
	}
	cout << "bounding rect found" << endl;
};
