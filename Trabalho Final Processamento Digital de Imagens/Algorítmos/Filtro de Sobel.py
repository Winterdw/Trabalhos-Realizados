import cv2
import numpy as np

#Recebendo a imagem
path= r'C:\Users\Windows\Desktop\PDI\1.jpg'
img = cv2.imread(path)

#Função que irá transformar a imagem em escalas de cinza.
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

#Usando a função da open cv de filtro gausiano.
img = cv2.GaussianBlur(gray,(3,3),0)

#Utilizando o filtro de sobel em relação ao eixo X da imagem.
sobelx = cv2.Sobel(img,cv2.CV_64F,1,0,ksize=5)

#Utilizando o filtro de sobel em relação ao eixo Y da imagem.
sobely = cv2.Sobel(img,cv2.CV_64F,0,1,ksize=5) 

#Somando as 2 imagens em busca de uma melhor definição da imagem.
imgSobel= sobelx+sobely

cv2.imwrite("Sobel.jpg",imgSobel)