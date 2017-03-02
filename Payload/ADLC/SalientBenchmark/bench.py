import time
import cv2

filesPath = './testImages/images.txt'
file = open(filesPath)
imgList = []

for l in file:
    imgPath = 'testImages/' + l
    imgList.append(imgPath)

import os
startbench = time.perf_counter()
for img in imgList:
    start = time.perf_counter()
    command = "./SpectralSaliency " + img
    print(command)
    os.system(command)
    end = time.perf_counter()
    print(end - start)
endbench = time.perf_counter()
print("Benchmark time: {}".format(endbench - startbench))
