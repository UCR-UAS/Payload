#include "../inc/Dimage.h"	
#include "Salient.cpp"

Dimage :: Dimage(){
    target_flag = false;
    altitude = 0;
    latitude = longitude = 0;
    degrees = 0;
}

Dimage :: Dimage(char* imagePath){
    image = imread(imagePath, CV_LOAD_IMAGE_COLOR);
    target_flag = false;
    altitude = 0;
    latitude = longitude = 0;
    degrees = 0;

}

bool Dimage :: hasTarget(){
    return target_flag;
}



