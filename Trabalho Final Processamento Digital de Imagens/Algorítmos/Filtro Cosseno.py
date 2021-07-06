import cv2
import math
import numpy as np

#Filtro de suavização da imagem.

def filtrcosseno():
	Cosseno=[]
	for i in range(256):
		Cosseno.append(int(255*(1-math.cos((3.1416*i)/510))))
	return Cosseno

path= r'C:\Users\Windows\Desktop\PDI\1.jpg'

img= cv2.imread(path)

nValores=filtrcosseno()

for i in range(img.shape[0]):
	for j in range(img.shape[1]):
		img.itemset((i,j,0), nValores[img.item(i,j,0)])
		img.itemset((i,j,1), nValores[img.item(i,j,1)])
		img.itemset((i,j,2), nValores[img.item(i,j,2)])

cv2.imwrite("filtrocosseno.jpg",img)


