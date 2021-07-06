import cv2
import numpy as np
#Filtro com efeito de suavização.
def FiltroMediaPonderada(img):
	aux=np.zeros((img.shape[0],img.shape[1]),dtype=np.int)
	for i in range(1,img.shape[0]-1):
		for j in range(1,img.shape[1]-1):
			lista=[img.item(i-1,j-1),img.item(i-1,j),img.item(i-1,j+1),img.item(i,j-1),img.item(i,j),img.item(i,j+1),img.item(i+1,j-1),img.item(i+1,j),img.item(i+1,j+1)]
			lista.sort()
			valor=lista[2]+lista[3]+lista[4]+lista[5]+lista[6]
			valor=float(valor)/5.0
			aux.itemset((i,j),int(valor))
	return aux

path= r'C:\Users\Windows\Desktop\PDI\1.jpg'

img=cv2.imread(path,0)
cv2.imwrite("filtromediaponderada.jpg",FiltroMediaPonderada(img))