#ifndef SHAPE_DETECT_H
#define SHAPE_DETECT_H
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
class shape_detector
{

 public:
  shape_detector();
  std::string detect(cv::Mat img);

};
#endif
