/* 
	UCR UAV Project
	Main file for running shape/leter/color detection
	Last Modified: Rachel Mendiola, 1/25/2015
*/
#include <vector>
#include "../inc/Dimage.h"
#include <cstring>
#include <iostream>
#include <dirent.h>
#include <wait.h>
#include <unistd.h>
#include "Dimage.cpp"

using namespace std;


int main(){
    char directory[400] = "/payload/img/raw";
    char processedDir[400] = "/payload/img/proc";
    vector < Dimage > images;		//vector of images, at the end of the process will contain images with targets
    while(1){		//main while loop
	DIR * dirp;
	if(!(dirp = opendir(directory))){		//open directory /img/RAW 
	    cerr << "error opening directory";		//send an error if unable to open 
	    exit(1);
	}
	dirent * currFile = readdir(dirp); 			//pointer to first file in /img/RAW
	char filePath [400];
	strcat(filePath, directory);
	strcat(filePath, "/");
	strcat(filePath, currFile->d_name);		//get full path to file
	char * c = filePath;
	Dimage currImage = Dimage(c);
	images.push_back(currImage);		//push a Dimage object into the vector also calls Dimage constructor
	if(fork() == 0){	//create a new process to mv the image file to /img/proc
	    char * args[] = {"mv", filePath, processedDir};
	    execvp("mv",args);		//child process
	    _exit(0);		//move current file from RAW to processed
	}
	else{			//parent process
	    wait(NULL);		//wait for child
	}
	closedir(dirp);		//closes directory RAW
	
	//NOW STARTING THE IMAGE PROCESSING 
	currImage.salient_detection();
	/*currImage.Letter();
	currImage.Shape();
	currImage.ColorDetection();
	Tag();
	*/
	if(currImage.hasTarget()){		//if image has target copy image to /img/targets folder
	    //copy image to /img/targets	
	}
	else{
	    //images.remove(currImage);		//if image has no target remove from images vector
	}
    }
    return 0;
}
