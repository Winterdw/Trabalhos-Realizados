import cv2

#Filtro gaussiano com objetivo específico de reduzir os níveis de ruido e evitar a distorção de uma imagem
path= r'C:\Users\Windows\Desktop\PDI\1.jpg'

img= cv2.imread(path)
result=cv2.GaussianBlur(img,(5,5),0)
cv2.imwrite("filtro_gaussiano.jpg",result)
