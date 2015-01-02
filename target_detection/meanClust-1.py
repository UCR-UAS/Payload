###################################################
##Name: Andrew Olguin
##
##Date: 1-1-15
##
##Functionality: This code is meant to show the functionality of k means clustering.
##It is a test harness for image preprocessing. The output of this file is meant for
##the object detection module.
##
##Version: 1
##
##Changes log: none
###################################################

import numpy as np
import cv2

def Sobel(gray):
    scale = 1
    delta = 0
    ddepth = cv2.CV_16S

    # Gradient-X
    grad_x = cv2.Sobel(gray,ddepth,1,0,ksize = 3, scale = scale, delta = delta,borderType = cv2.BORDER_DEFAULT)
    #grad_x = cv2.Scharr(gray,ddepth,1,0)

    # Gradient-Y
    grad_y = cv2.Sobel(gray,ddepth,0,1,ksize = 3, scale = scale, delta = delta, borderType = cv2.BORDER_DEFAULT)
    #grad_y = cv2.Scharr(gray,ddepth,0,1)

    # converting back to uint8
    abs_grad_x = cv2.convertScaleAbs(grad_x)  
    abs_grad_y = cv2.convertScaleAbs(grad_y)

    dst = cv2.addWeighted(abs_grad_x,5,abs_grad_y,5,0)

    return dst

def Clust(img, K):
    Z = img.reshape((-1,3))

    # convert to np.float32
    Z = np.float32(Z)

    # define criteria, number of clusters(K) and apply kmeans()
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 10, 1.0)

    #ret,label,center=cv2.kmeans(Z,K,None,criteria,10,cv2.KMEANS_RANDOM_CENTERS)
    ret, label, center = cv2.kmeans(Z, K, criteria, 10, 0)

    # Now convert back into uint8, and make original image
    center = np.uint8(center)
    res = center[label.flatten()]
    res2 = res.reshape((img.shape))

    return res2

#################################################################

img = cv2.imread('target\IMG_0490_1.jpg')


lb = 50
ub = 300
k  = 2

img = Clust(img, k)

img1 = cv2.cvtColor(img, cv2.COLOR_RGB2LUV)

uv_img = img1[:,:,1]+ img1[:,:,2]

img2 = cv2.pyrUp(uv_img)
img2 = cv2.pyrUp(img2)

grad = Sobel(img2)
edges = cv2.Canny(grad,lb,ub)

cv2.imwrite('img_0490_clustered.png', img)
cv2.imwrite('img_0490_edges.png', edges)
cv2.imshow('res2',img2)
cv2.imshow('edges', edges)
cv2.waitKey(0)
cv2.destroyAllWindows()
