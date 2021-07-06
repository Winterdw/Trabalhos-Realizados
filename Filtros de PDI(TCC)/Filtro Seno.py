import cv2
import math
import numpy as np
#Filtro com objetivo de redução de ruído na imagem.
def filtroseno():
	Seno=[]
	for i in range(256):
		Seno.append(int(255*math.sin((3.1416*i)/510)))
	return Seno

path= r'C:\Users\Windows\Desktop\PDI\1.jpg'

img= cv2.imread(path)

nValores=filtroseno()

for i in range(img.shape[0]):
	for j in range(img.shape[1]):
		img.itemset((i,j,0), nValores[img.item(i,j,0)])
		img.itemset((i,j,1), nValores[img.item(i,j,1)])
		img.itemset((i,j,2), nValores[img.item(i,j,2)])

cv2.imwrite("filtroseno.jpg",img)


