import cv2
import numpy as np

class ShapeDetector:
    
    def __init__(self):
        pass
    
    def detect(self,c):
        # init the shape name and approximate the contour
        # Ramer-Douglas Peucker algo will be used 
        shape = "unidentified"
        peri = cv2.arcLength(c,True)
        approx = cv2.approxPolyDP(c, .04*peri , True)

        # case for each shape

        # if triangle
        if len(approx) == 3:
            shape = "triangle"
        # if square or rectangle
        elif len(approx) == 4:
            #use shape factors
            # In order to determine which one we can calculate the ratio of the contours
            #figure out shape factor
            (x ,y ,w ,h) = cv2.boundingRect(approx)
            area = w*h
            areac = cv2.contourArea(c)
            print(area)
            print(areac)
            aspRatio = w / float(h)
            print(aspRatio)
            if aspRatio >= .95 and aspRatio <= 1.05:
                shape = "Square"
            elif aspRatio >= 1.05 and aspRatio <= 1.5:
                shape = "Rectangle"
            elif aspRatio > 1.5:
                shape = "Trapezoid"
            else:
                shape = "Diamond"
        elif len(approx) == 5:
            shape = "Pentagon"
        elif len(approx) == 10:
            shape = "Star"

        elif len(approx) == 12:
            shape = "Plus"
        else:
            #utilize hough circle to identify circles
            shape = "Circle"
        return shape

