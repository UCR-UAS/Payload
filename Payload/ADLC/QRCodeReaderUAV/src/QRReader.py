import zbar
import cv2
import numpy as np
import argparse

def decodeQR(img):
    scanner = zbar.Scanner()
    results = scanner.scan(img)
    for result in results:
        print(result.type, result.data, result.quality, result.position)

def distance(p1,p2):
    return (((p1[0]-p2[0])**2 + (p1[1]-p2[1])**2) **.5)

def line_eqn(l,m,j):
    if m[0] == l[0]:
        return 0
    a = b = c = pdist = 0.0
    a = -((m[1] - l[1])/(m[0]-l[0]))
    b = 1.0
    c = (((m[1]-l[1])/(m[0]-l[0]))*l[0])-l[1]

    pdist = (a * j[0] + (b * j[1]) +c ) / ((a*a)+ (b*b)) ** .5
    return pdist

def line_slope(l,m,):
    dx = m[0] - l[0]
    dy = m[1] - l[1]

    if dy != 0:
        return dy/dx,1
    elif dy == 0:
        return 0.0,0

def getVerticies(cnts,c_id,slope):
    box = cv2.boundingRect(cnts[c_id])
    A = box.t1()
    print("GET VERTIECIES")
    return 1

def proccessImg(fileName):
    QR_NORTH = 0
    QR_EAST = 1
    QR_SOUTH = 2
    QR_WEST = 3
    img = cv2.imread(fileName)
    img_bk = img
    img = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    img = cv2.GaussianBlur(img,(3,3),.05)

    # need to account for angle of camera relative to qr code

    #we will be using sturcted contour detection
    ret,thresh = cv2.threshold(img,127,255,0)
    #apply edge detection
    edges = cv2.Canny(img,100,200)
    thresh = np.concatenate((thresh,edges),axis=1)
    im2,contours,hiearchy = cv2.findContours(edges,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    #get contour moments
    cnts = contours 
    MC = []
    for c in cnts:
        M = cv2.moments(c)
        if M['m00'] == 0:
            continue
        cX = int(M['m10']/M['m00'])
        cY = int(M['m01']/M['m00'])
        MC.append((cX,cY))

    mark = A = B = C = top = right = bottom = median1 = median2 = outlier = 0
    AB = BC = CA = dist = slope = areat = arear = areab = large = padding = 0.0

    for i in range(len(cnts)):
        k = i
        c = 0
        while hiearchy[0 , k , 2] != -1:
            k = hiearchy[0,k,2]
            c += 1

        if hiearchy[0 , k , 2] != -1:
            c += 1

        if c >= 5:
            if mark == 0: A = i
            elif mark == 1: B = i
            elif mark == 2: C = i
            mark += 1

    if c >= 3:
        AB = distance(MC[A],MC[B])
        BC = distance(MC[B],MC[C])
        CA = distance(MC[C],MC[A])

            #determine the top

        if AB > BC and AB > CA:
            outlier = C
            median1 = A
            median2 = B
        elif CA > AB and CA >BC:
            outlier = B
            median1 = A
            meidan2 = C
        elif BC > AB and BC > CA:
            outlier = A
            median1 = B
            median2 = C
        top = outlier

        dist = line_eqn(MC[median1],MC[median2],MC[outlier])
        slope,align = line_slope(MC[median1],MC[median2])

        if align == 0:
            bottom = median1
            right  = median2
        elif slope < 0 and dist < 0:
            bottom = median1
            right = median2
            orienation = QR_NORTH
        elif slope > 0 and dist < 0:
            right = median1
            bottom = median2
            orientation = QR_EAST
        elif slope < 0 and dist > 0:
            right = median1
            bottom = median2
            orienation = QR_SOUTH
        elif slope > 0 and dist > 0:
            bottom = median1
            right = median1
            orientation - QR_WEST

        area_top = area_right = area_bottom = 0.0

        cnts_size = len(cnts)
        print(cnts_size)
        print(top)
        print(right)
        print(bottom)
        print(cv2.contourArea(cnts[top]))
        print(cv2.contourArea(cnts[right]))
        print(cv2.contourArea(cnts[bottom]))
        print("Pre condiitonal")
        if top < cnts_size and right < cnts_size and bottom < cnts_size and cv2.contourArea(cnts[top]) > 10 and cv2.contourArea(cnts[right]) > 10 and cv2.contourArea(cnts[bottom]) > 10:
            L = []
            M = []
            O = []
            tempL = []
            tempM = []
            tempO = []
            src = []
            dst = []

            print("conditional")
            tempL = getVerticies(cnts,top,slope)
            tempM = getVerticies(cnts,right,slope)
            tempO = getVerticies(cnts,bottom,slope)





    cv2.drawContours(img_bk,contours,-1,(255,55,100),3)
    cv2.imshow("thresh",img_bk)

    cv2.waitKey(0)

    #decode
    decodeQR(img)


ap = argparse.ArgumentParser()
ap.add_argument("-i","--image",required=True)
args = vars(ap.parse_args())

proccessImg(args['image'])
 
