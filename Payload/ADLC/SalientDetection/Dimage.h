/* 
	UCR UAV Project
	Header file for Dimage objects.
	Last Modified: Rachel Mendiola, 1/25/2015
*/


#ifndef DIMAGE_H_
#define DIMAGE_H_

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include <sstream>
#include <vector>
#include <stdio.h>


using namespace std;

struct Target{
    Mat croppedImg;
    Rect coords;
    char letter;
    string shape;
    string shapeColor;
    string letterColor;
};

class Dimage{
    private:
    Mat image;
    bool target_flag;
    int altitude;
    int latitude;
    int longitude;
    float degrees;
    vector < Rect > ROI;
    vector < Target > objects;

    public:
    Dimage();
    Dimage(char * imagePath);
    bool hasTarget();
    void Salient();
    void ShapeDetection();
    void LetterDetection();
    void ColorDetection();
    void Tag();

};

#endif

