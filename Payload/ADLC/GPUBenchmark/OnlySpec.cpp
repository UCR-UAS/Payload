//FrequencySaliencyDetection7.2 simplified so transmission and loading of image is done elsewhere

#include <iostream>
#include <opencv2/opencv.hpp>
//#include <dirent.h>
//#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  cv::Mat OriginalImage;
  char* path = argv[1];
  std::cout << "Reading..." << std::endl;
  OriginalImage = cv::imread(path);
  std::cout << "Writing..." << std::endl;
  cv::imwrite("copy.jpg", OriginalImage);
  std::cout << "Done." << std::endl;
    return 0;
}

