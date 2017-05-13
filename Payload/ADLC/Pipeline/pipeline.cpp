#include <iostream>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
//#include "OnlySpec.h"
#include <fstream>
#include<dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

using namespace cv;
using namespace std;

void moveTofinished(string path){
  //first let us move the file into the finished folder
  string mv = "mv ";
  string dest_folder =  " ./Finished/";
  string command = mv + path + dest_folder;
  //move image to finished folder
  system(command.c_str());
}

int main(int argc, char ** argv){

  //variables to create
  string imagepath = "./crp";
  //command argument needed
  if(argc < 2){
    return -1;
  }
  ifstream file(argv[1]);
  if(!file.is_open()){
    return -1;
  }
  file.close();


  //while you can take an image
  while(true){
system("/home/ubuntu/a01/a01.py");
      //retrieve the image list, place it into a file
      system("/home/ubuntu/a01/a01.py --getImageList > list.txt");
      std::cout << "retrieved the list " << endl;
      ifstream file("list.txt");
      if(!file.is_open()){
          return -1;
      }
      string image;
      file >> image;
      file.close();
      //transfer the image
      string cmd = "/home/ubuntu/a01/a01.py --getImage ";
      cmd += image;
      system(cmd.c_str());
      //wait for the image to transfer
      system("sleep 5");
      //delete the image from the camera
      cmd = "/home/ubuntu/a01/a01.py --delImage ";
      cmd += image;
      system(cmd.c_str());

      //remove the list.txt file
      system("rm -rf list.txt");

      //apply the Saliency on the image
      vector<Mat> crp;
      //cp  = Saliency(image);

      //do the algorithms for each cropped image
      string temp;
      while(crp.size()>0){
        //string color = ColorID(crp.at(0));
        //string letter = letter(crp.at(0));
        //string shape = shape(crp.at(0));
        //somehow get the geo location

      }
  }
  return 0;
}
