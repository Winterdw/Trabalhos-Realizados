import cv2
import numpy as np

#Função de convolução para corrigir e realçar a imagem utilizando matrizes.

def Convolucao(img,c):
	aux=np.zeros((img.shape[0],img.shape[1]),dtype=np.int)
	for i in range(1,img.shape[0]-1):
		for j in range(1,img.shape[1]-1):
			valor=img.item(i-1,j-1)*c[0][0]+img.item(i-1,j)*c[0][1]+img.item(i-1,j+1)*c[0][2]+img.item(i,j-1)*c[1][0]+img.item(i,j)*c[1][1]+img.item(i,j+1)*c[1][2]+img.item(i+1,j-1)*c[2][0]+img.item(i+1,j)*c[2][1]+img.item(i+1,j+1)*c[2][2]
			if valor>255:
				valor=255
			elif valor<0:
				valor=0
			aux.itemset((i,j),valor)
	return aux

#As funções a seguir utilizam o filtro de convolução em diferentes eixos e direções.
def horizontalB(img):
	m= np.array([[-1,-1,-1],
             [2,2,2],
             [-1,-1,-1]],dtype='int')
	return Convolucao(img,m)

def verticalB(img):
	m= np.array([[-1,2,-1],
             [-1,2,-1],
             [-1,2,-1]],dtype='int')
	return Convolucao(img,m)

def deteccao45P(img):
	m= np.array([[-1,-1,2],
             [-1,2,-1],
             [2,-1,-1]],dtype='int')
	return Convolucao(img,m)

def deteccao45N(img):
	m= np.array([[-1,-1,2],
             [-1,2,-1],
             [2,-1,-1]],dtype='int')
	return Convolucao(img,m)

path= r'C:\Users\Windows\Desktop\PDI\1.jpg'

img= cv2.imread(path,0)

#Após cada imagem ser criada,somei todas a fim de buscar uma melhor resolução de diferentes lados.
imgSoma1= horizontalB(img)+verticalB(img)
imgSoma2=deteccao45N(img)+deteccao45P(img)
imgTOTAL=imgSoma1+imgSoma2

cv2.imwrite("convolucao_bordas.jpg", imgTOTAL)
