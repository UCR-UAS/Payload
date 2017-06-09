
import numpy as np
import cv2
import random
#import pandas as pd
import argparse
#from matplotlib import pyplot as plt

def getShape(num):
    if num == 1:
        name = 'Circle'
    elif num == 2:
        name = 'Diamond'
    elif num == 3:
        name = 'Plus'
    elif num == 4:
        name = 'QuarterCircle'
    elif num == 5:
        name = 'Rectangle'
    elif num == 6:
        name = 'Semicircle'
    elif num == 7:
        name = 'Square'
    elif num == 8:
        name = 'Star'
    elif num == 9:
        name = 'Trapezoid'
    elif num == 10:
        name = 'Triangle'
    return name
def getImage(num):
    if num == 1:
        shape = cv2.imread('./shapes/Circle.jpg')
        print("circle")
    elif num == 2:
        print("diamond")
        shape = cv2.imread('./shapes/Diamond.jpg')
    elif num == 3:
        print("plus")
        shape = cv2.imread('./shapes/Plus.jpg')
    elif num == 4:
        print("quarterC")
        shape = cv2.imread('./shapes/QuarterCircle.jpg')
    elif num == 5:
        print("rect")
        shape = cv2.imread('./shapes/Rectangle.jpg')
    elif num == 6:
        print("semi")
        shape = cv2.imread('./shapes/Semicircle.jpg')
    elif num == 7:
        print("sqr")
        shape = cv2.imread('./shapes/Square.jpg')
    elif num == 8:
        print("star")
        shape = cv2.imread('./shapes/Star.jpg')
    elif num == 9:
        print("trapezoid")
        shape = cv2.imread('./shapes/Trapezoid.jpg')
    elif num == 10:
        print("triangle")
        shape = cv2.imread('./shapes/Triangle.jpg')
    return shape
def saveImage(name,img,num):
    print("Saving")
    prefix = ".jpg"
    #if num == 1:
    #    name = 'Circle'
    #elif num == 2:
    #    name = 'Diamond'
    #elif num == 3:
    #    name = 'Plus'
    #elif num == 4:
    #    name = 'QuarterCircle'
    #elif num == 5:
    #    name = 'Rectangle'
    #elif num == 6:
    #    name = 'Semicircle'
    #elif num == 7:
    #    name = 'Square'
    #elif num == 8:
    #    name = 'Star'
    #elif num == 9:
    #    name = 'Trapezoid'
    #elif num == 10:
    #    name = 'Triangle'
    path = './results/'+name+'/'+name +str(num)+ prefix
    cv2.imwrite(path,img)
def Rotate(img):
    angle = random.randint(30,270)
    N = cv2.getRotationMatrix2D((50,50),angle,1)
    img = cv2.warpAffine(img,N,(100,100))
    return img
def GetPoints():
    #x = columns
    #y = rows
    X1 = random.randint(20,30)
    Y1 = random.randint(30,40)
    #keep the same Rows number
    X2 = random.randint(60,80)
    Y2 = Y1
    #keep same number of Columns
    X3 = X1
    Y3 = random.randint(60,70)
    #keep smae number of columns of point2
    X4 = X2
    Y4 = Y3
    arg = [(X1,Y1),(X2,Y2),(X3,Y3),(X4,Y4)]
    return arg;
#We can view the image in a possible of 4 ways
def RandomShift(arr):
    NX1 = arr[0][0] + random.randint(0,7)
    NY1 = arr[0][1] + random.randint(0,7)
    NX2 = arr[1][0] - random.randint(0,7)
    NY2 = arr[1][1] - random.randint(0,7)
    NX3 = arr[2][0] + random.randint(0,7)
    NY3 = arr[2][1] + random.randint(0,7)
    NX4 = arr[3][0] - random.randint(0,7)
    NY4 = arr[3][1] - random.randint(0,7)
    arg2 = [(NX1,NY1),(NX2,NY2),(NX3,NY3),(NX4,NY4)]
    return arg2;
ap = argparse.ArgumentParser()
ap.add_argument("-n","--num",type=int,default=100,help="Number of training images")
args = vars(ap.parse_args())
print(args)
n = args["num"]
training_data = []
file_names = []
for i in range(1,11):
    for j in range(n):
        num = i
        name = getShape(num)
        print("Expected shape {}".format(name))
        img = getImage(num)
        img = Rotate(img)
        saveImage(name,img,j)
