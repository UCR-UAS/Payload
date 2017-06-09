#include <opencv2/opencv.hpp>
#include <stdlib.h>

int main(int argc, char** argv) {
	cv::Mat image;
	image = cv::imread("OLYMP.jpg");
	cv::imwrite("copy.jpg", image);
	return 0;
}
