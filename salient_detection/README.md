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
-Everything has been implemented

TODO
====
-test the algorithm

-optimize the algorithm (gpu?)

Files in folder
================