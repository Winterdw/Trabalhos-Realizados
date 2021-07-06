import cv2
import numpy as np
from matplotlib import pyplot as plt


path= r'C:\Users\Windows\Desktop\PDI\1.jpg'
img0 = cv2.imread(path)

#Mudança de escala para cinza.
gray = cv2.cvtColor(img0, cv2.COLOR_BGR2GRAY)

#Utilizando filtro de suavização.
img = cv2.GaussianBlur(gray,(3,3),0)

#Biblioteca da opencv.
laplacian = cv2.Laplacian(img,cv2.CV_64F)
cv2.imwrite("laplaciano.jpg",laplacian)
