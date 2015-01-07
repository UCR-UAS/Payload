Description
===========
This folder contains the code for region of interest detection and cropping.

It is a salient object detection method that uses a sobel filter of the u* and v* channels of the Lu*v* color space.

Action/result chart:
====================
				 image input
                      |
                      |
			cropped regions of interest output
         
This is just showing how the code will work for testing purposes.

Algorithm description
=====================
convert to LUV colorspace
		   |
		   |
	 gaussian filter
		   |
		   |
	  Sobel filter
		   |
		   |
	 gaussian filter
		   |
		   |
	image normalization
		   |
		   |
	  Thresholding
		   |
		   |
		dilation
		   |
		   |
		Countours
		   |
		   |
	 Counter boxing
		   |
		   |
	Box size filtering

Whats been done
===============
-Code has been implemented

-Basic testing has been done

TODO
====
-test the algorithm

-optimize the algorithm (gpu?)

Files in folder
================
salient_detection.cpp - this is the main file that needs to be run

IMG_0494/0526 - test images that the code uses to crop

croppedImg - the file where detected roi of interest are saved

competitionPhotos - the folder that contains the test data set of photos taken during previous competitions

How to run
==========
cmake CMakeLists.txt 

make

./salient_det

Requirements
============
most recent version of cmake

opencv version 2.4.10