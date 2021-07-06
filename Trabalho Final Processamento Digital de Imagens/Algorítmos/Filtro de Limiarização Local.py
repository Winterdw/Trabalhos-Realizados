import cv2
#Limiarização Local
path= r'C:\Users\Windows\Desktop\PDI\1.jpg'

img = cv2.imread(path, 0)
#utilizando uma limiarização média.
lim1 = cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_MEAN_C,cv2.THRESH_BINARY, 11, 2)
#utilizando a limiariação gausiana.
lim2 = cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY, 11, 2)

limLocal=lim1+lim2
cv2.imwrite("limiarizacao_local.jpg",limLocal)