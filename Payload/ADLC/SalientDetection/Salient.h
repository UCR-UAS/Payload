#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include <sstream>
#include <vector>
#include <stdio.h>

class Salient{ 
	private:
		Mat image
		vector<Rect> cropped
	public:
		//Constructer
		Salient();
		Salient(Mat image);
		Salient(Mat image, vector<Rect>) 
		
		//Function
		Mat salient_detection(Mat img);
		Mat CannyThreshold(Mat src, Mat grad);
		Mat gradient(Mat src);
		void findObject(Mat mask, Mat src);
};
	
