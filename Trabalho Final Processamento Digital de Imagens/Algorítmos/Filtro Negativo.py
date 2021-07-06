import cv2
#Filtro para remover ou suavizar ruídos da imagem.
path= r'C:\Users\Windows\Desktop\PDI\1.jpg'
 
img = cv2.imread(path) 
img_not = cv2.bitwise_not(img)
cv2.imwrite("negativo.jpg",img_not)
