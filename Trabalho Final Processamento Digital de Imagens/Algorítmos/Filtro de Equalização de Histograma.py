import cv2

path= r'C:\Users\Windows\Desktop\PDI\1.jpg'

img = cv2.imread(path)
#Convertendo a imagem em escala de cinza.
img_to_yuv = cv2.cvtColor(img, cv2.COLOR_BGR2YUV)
img_to_yuv[:, :, 0] = cv2.equalizeHist(img_to_yuv[:, :, 0])
#Equalização de histograma utilizando a opencv.
hist_equalization_result = cv2.cvtColor(img_to_yuv, cv2.COLOR_YUV2BGR)
cv2.imwrite('histograma_equalizado.jpg', hist_equalization_result)