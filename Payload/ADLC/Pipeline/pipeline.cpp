#include <iostream>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include<dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

//include the files from the algorithms
#include "Json.h"

using namespace cv;
using namespace std;

//something is wrong in this segment of code
bool inVec(vector<Json> v, Json b){
  for(unsigned i = 0; i < v.size(); ++i){
    if(v.at(i) == b){
      return true;
    }
  }
  return false;
}


int main(int argc, char ** argv){
//command argument needed
if(argc < 2){
	return -1;
}
//file tells us where to send the images
ifstream file(argv[1]);
if(!file.is_open()){
	return -1;
}
file.close();

int i = 1;
int j = 1;
vector<Json> labels;
//while you can take an image
while(i){
  j++;

  //TODO retreive gets the images from the current directory and stores them as mats

  vector<Mat> images; //= retreive();

  for(unsigned i = 0; i < images.size(); ++i){
    //SEGMENT the image
    vector<Mat> crp ;//= saliency(images.at(i));

    for(unsigned k = 0; k < crp.size(); ++k){
      //create the json container
      Json temp;
  		//TODO
      //Use the algorithms to fill the JSON

      temp.number = j;
      //get the type- not sure what this is exactly
      temp.type = "normal";
      //GEOTAGGING
      temp.lat;
      temp.lng;
      //ANGLE
      temp.angle;
      //SHAPE
      //temp.shape = shape(crp.at(0));
      //BCKGROUND COLOR
      //temp.bck_color = ;
      //LETTER
      //temp.let = letter(crp.at(k));
      //COLOR
      //temp.color = color(crp.at(k));

      if(!inVec(labels,temp)){
        labels.push_back(temp);
      }

  	}
    crp.clear();
  }
  //after that batch of images
  //check the Json images
  //send them somewhere
}
  return 0;
}
