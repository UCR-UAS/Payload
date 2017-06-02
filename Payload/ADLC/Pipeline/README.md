This is the 2017 pipeline code for the UAV 
The layout of the code goes as such

We have a while loop that always executes 
#while(true)

#step1
Take an image, and retreive the image from the camera 

currently looking for a way to grab the image without saving it on the SD card 

For now 
grab the image from ImageList, then remove the image

#Step 2
apply segmentation on the image 
returns a vector of mats 

#step 3 
for each mat, apply the algorithms
-Color
-Shape
-Letter 
-Geo

these return strings that we will put into a file and scp to the base stsation 

#step 4 
transfer to basestation
