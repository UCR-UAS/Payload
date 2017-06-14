#include <iostream>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include<dirent.h>
#include <utility>      // std::pair, std::make_pair
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


//SO WE DONT READ THE SAME IMAGE, AFTER WE READ THAT IMAGE, MOVE IT to a new directroy called finished
void moveTofinished(string path){
   //first let us move the file into the finished folder
   string mv = "mv ";
   string dest_folder =  " ./Finished/";
   string command = mv + path + dest_folder;
   //move image to finished folder
   system(command.c_str());
 }

//this is going to find and image and return the name
string readCurrentDirectory(string path){
  DIR *dir;
  struct dirent *ent;
  string result;
  if ((dir = opendir(path.c_str())) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      //printf ("%s\n", ent->d_name);
      result = ent->d_name;
    }
  closedir (dir);
  return result;
  }
  else {
  /* could not open directory */
  perror ("");
  return 0;
  }
}

bool inVec(const vector<Json> &v, Json b){
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
//read file
ifstream file(argv[1]);
if(!file.is_open()){
	return -1;
}
//WHAT EVER IS NEEDED FROM THE FILE
//FORMAT OF file
//1.image source list

//read the directory to get the image
string dir;
file >> dir;


file.close();

int i = 1;
int j = 1;
vector<Json> labels;

//while you can take an image
while(i){
  j++;

  //retreive gets the images from the directory and stores them as mats
  string name = readCurrentDirectory(dir);
  Mat image = imread(name, CV_LOAD_IMAGE_COLOR);
  string p = dir + "/" + name;
  moveTofinished(p);

  //segment the image
  vector<Mat> crp ;//= saliency(image);

  for(unsigned k = 0; k < crp.size(); ++k){
    //create the json container
    Json temp;
		//TODO
    //Use the algorithms to fill the JSON
    //NUMBER
    temp.number = j;
    //get the type- not sure what this is exactly
    temp.type = "normal";
    //GEOTAGGING
    pair<float, float> coord; // = GEO;
    temp.lat = coord.first;
    temp.lng = coord.second;
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
  //after that batch of images
  //check the Json images
  //send them somewhere
}

  return 0;
}
