#coding: utf-8
import cv2
#Filtro de limiarização com o objetivo de verificar um valor ideal de threshold para os elementos da imagem.
def LimiarizacaoOtsu(img): 
       
    th = 0
    max_val = 255
    
    ret, o1 = cv2.threshold(img, th, max_val, cv2.THRESH_BINARY + cv2.THRESH_OTSU )
    ret, o2 = cv2.threshold(img, th, max_val, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU )
    ret, o3 = cv2.threshold(img, th, max_val, cv2.THRESH_TOZERO + cv2.THRESH_OTSU )
    ret, o4 = cv2.threshold(img, th, max_val, cv2.THRESH_TOZERO_INV + cv2.THRESH_OTSU )
    ret, o5 = cv2.threshold(img, th, max_val, cv2.THRESH_TRUNC + cv2.THRESH_OTSU )
   

    cv2.imwrite("binaria.jpg",o1 )
    cv2.imwrite("binaria_invertida.jpg",o2 )
    cv2.imwrite("zero.jpg",o3 )
    cv2.imwrite("zeroinvertida.jpg",o4 )
    cv2.imwrite("truncada.jpg",o5 )


path= r'C:\Users\Windows\Desktop\PDI\1.jpg'

img=cv2.imread(path,0)

LimiarizacaoOtsu(img)
