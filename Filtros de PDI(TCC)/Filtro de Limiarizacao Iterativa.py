import cv2
#Limiarização iterativa

path= r'C:\Users\Windows\Desktop\PDI\1.jpg'

img=cv2.imread(path,0)
limiar,imgLimiarB=cv2.threshold(img,150,255,cv2.THRESH_BINARY) #se a cor do pixel for igual ao limiar,então recebe 0 vulgo preto.
limiar,imgLimiar=cv2.threshold(img,64,255,cv2.THRESH_TOZERO) #se o pixel estiver acima do limiar,ele continua,se não ele recebe 0(preto)
cv2.imwrite("limiarizacao_iterativa.jpg",imgLimiar)
cv2.imwrite("limiarizacao_iterativa.jpg",imgLimiarB)
