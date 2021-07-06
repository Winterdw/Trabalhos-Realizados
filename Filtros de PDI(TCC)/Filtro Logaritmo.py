import cv2
import math
import numpy as np

#Filtro usado para remover altas frequências.s

def filtrolog(alfa):
	Logaritmo=[]
	for i in range(256):
		Logaritmo.append(int((255/(math.log(alfa*255+1)))*(math.log(alfa*i+1))))
	return Logaritmo

path= r'C:\Users\Windows\Desktop\PDI\1.jpg'

img= cv2.imread(path)

nValores=filtrolog(1)

for i in range(img.shape[0]):
	for j in range(img.shape[1]):
		img.itemset((i,j,0), nValores[img.item(i,j,0)])
		img.itemset((i,j,1), nValores[img.item(i,j,1)])
		img.itemset((i,j,2), nValores[img.item(i,j,2)])

cv2.imwrite("filtrolog.jpg",img)



