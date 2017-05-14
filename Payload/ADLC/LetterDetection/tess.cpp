#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
using namespace cv;
using namespace std;

string intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}

int main(int argc, char* argv[]){
//original image
Mat frame;
//grey scale image
Mat grey;
frame = imread(argv[1],1);
namedWindow("original image",1);
namedWindow("gray image",1);
//convert image
cvtColor(frame,grey,COLOR_BGR2GRAY);
threshold(grey, grey, 100, 255,	THRESH_OTSU);
bitwise_not(grey,grey);

vector<Point> points;
findNonZero(grey, points);
RotatedRect box = minAreaRect(points);

double angle = box.angle;
cout << "origina, angle " <<  angle << endl;
if (box.size.width < box.size.height) {
  angle = 180 + angle;

}
else{
  angle = angle + 90;
}
cout << "shifted :" <<  angle << endl;
cv::Point2f vertices[4];
box.points(vertices);
for(int i = 0; i < 4; ++i){
  cv::line(grey, vertices[i], vertices[(i + 1) % 4], cv::Scalar(255, 0, 0));
}
Mat M = getRotationMatrix2D(box.center,angle,1.0);
warpAffine(grey,grey,M,grey.size(),INTER_CUBIC);

Point2f loc = Point2f(10,20);
putText(grey, "Angle:" + intToString(angle),loc,FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255));

imwrite("grey.jpg",grey);






  int choice;
  //command passed into tesseract
  string command;
  //name of the image file
  string fileName;
  //name of the output file, do not need to input extension
  string outPutFile;
  //result of classification
  string result;

  string image = "./grey.jpg";
  cin >> outPutFile;
  command = "tesseract " + image + " " + outPutFile  + " -psm 10" ;

  system(command.c_str());

  ifstream iFile;
  iFile.open((outPutFile + ".txt").c_str());
  if(!iFile.is_open())
  {
    return -1;
  }

  iFile >> result;
  iFile.close();
  cout << "the result is " << result << endl;


return 0;
}
