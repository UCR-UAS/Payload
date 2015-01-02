import numpy as np
import cv2
from matplotlib import pyplot as plt

def nothing(x):
    pass

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

    ret,label,center=cv2.kmeans(Z,K,None,criteria,10,cv2.KMEANS_RANDOM_CENTERS)
    #ret, label, center = cv2.kmeans(Z, K, criteria, 10, 0)

    # Now convert back into uint8, and make original image
    center = np.uint8(center)
    res = center[label.flatten()]
    res2 = res.reshape((img.shape))

    return res2

def SURFINPYR(img, K, lb, ub, srfVal):
    img1 = Clust(img, K)

    surf = cv2.SIFT(srfVal)

    img1 = cv2.cvtColor(img1, cv2.COLOR_RGB2LUV)

    uv_img = img[:,:,1]+ img[:,:,2]

    img2 = cv2.pyrUp(uv_img)
    img2 = cv2.pyrUp(img2)

    grad = Sobel(img2)
    edges = cv2.Canny(grad,lb,ub)

    kp, des = surf.detectAndCompute(edges, None)

    return kp, des

def SURFIN(img, K, lb, ub, srfVal):
    img = Clust(img, K)

    surf = cv2.SIFT(srfVal)

    img = cv2.cvtColor(img, cv2.COLOR_RGB2LUV)

    uv_img = img[:,:,1]+ img[:,:,2]

    grad = Sobel(img2)
    edges = cv2.Canny(grad,lb,ub)

    kp, des = surf.detectAndCompute(edges, None)

    return kp, des

###############################################################
img1 = cv2.imread('T.png')          # trainImage
img2 = cv2.imread('IMG_0494_22.jpg') # queryImage
img3 = cv2.imread('T.png') # queryImage
img4 = cv2.imread('A.png') # queryImage

#create windows
cv2.namedWindow('reference Image')

# create trackbars for parameter change
cv2.createTrackbar('Canny ub','reference Image',100,255,nothing)
cv2.createTrackbar('Canny lb','reference Image',200,255,nothing)
cv2.createTrackbar('K','reference Image',4,10,nothing)
cv2.createTrackbar('SURF Thresh','reference Image',400,4000,nothing)


while(1):
    K = cv2.getTrackbarPos('K', 'reference Image')
    lb = cv2.getTrackbarPos('Canny lb', 'reference Image')
    ub = cv2.getTrackbarPos('Canny ub', 'reference Image')
    srfVal = cv2.getTrackbarPos('SURF Thresh', 'reference Image')

    kp1, des1 = SURFIN(img1, K, lb, ub, srfVal)
    kp2, des2 = SURFINPYR(img2, K, lb, ub, srfVal)
    kp3, des3 = SURFIN(img3, K, lb, ub, srfVal)
    kp4, des4 = SURFIN(img4, K, lb, ub, srfVal)


    # FLANN parameters
    FLANN_INDEX_KDTREE = 0
    index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
    search_params = dict(checks=50)   # or pass empty dictionary

    flann = cv2.FlannBasedMatcher(index_params,search_params)

    matches1 = flann.knnMatch(des1,des2,k=2)
    matches2 = flann.knnMatch(des1,des3,k=2)
    matches3 = flann.knnMatch(des1,des4,k=2)

    # Need to draw only good matches, so create a mask
    matchesMask1 = [[0,0] for i in xrange(len(matches1))]
    matchesMask2 = [[0,0] for i in xrange(len(matches2))]
    matchesMask3 = [[0,0] for i in xrange(len(matches3))]

    # ratio test as per Lowe's paper
    for i,(m,n) in enumerate(matches1):
        if m.distance < 0.7*n.distance:
            matchesMask1[i]=[1,0]

    for i,(m,n) in enumerate(matches2):
        if m.distance < 0.7*n.distance:
            matchesMask2[i]=[1,0]

    for i,(m,n) in enumerate(matches3):
        if m.distance < 0.7*n.distance:
            matchesMask3[i]=[1,0]

            
    draw_params1 = dict(matchColor = (0,255,0),
                       singlePointColor = (255,0,0),
                       matchesMask1 = matchesMask1,
                       flags = 0)

    draw_params2 = dict(matchColor = (0,255,0),
                       singlePointColor = (255,0,0),
                       matchesMask2 = matchesMask2,
                       flags = 0)
    draw_params3 = dict(matchColor = (0,255,0),
                       singlePointColor = (255,0,0),
                       matchesMask3 = matchesMask3,
                       flags = 0)

    img5 = cv2.drawMatchesKnn(img1,kp1,img2,kp2,matches,None,**draw_params1)
    img6 = cv2.drawMatchesKnn(img1,kp1,img3,kp3,matches,None,**draw_params2)
    img7 = cv2.drawMatchesKnn(img1,kp1,img4,kp4,matches,None,**draw_params3)

    cv2.imshow('reference Image', img1)
    cv2. waitKey()

    plt.imshow(img5,),plt.show()
    plt.imshow(img6,),plt.show()
    plt.imshow(img7,),plt.show()
