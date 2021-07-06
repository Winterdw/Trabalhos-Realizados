import cv2
import math
import numpy as np
#import time
#inicioGeral = time.time()
def Segmentador(path):
	
    def preparaSaida(path):

        fileOut = path.replace(".", "_out.")
        print("*********************************************")
        print("Imagem de Entrada: " + path)
        print("Imagem de Saída: "+ fileOut)   
        
        
        img=cv2.imread(path,0)
        cv2.imwrite(fileOut,img)
        return fileOut
     
    def LimiarizacaoOtsu(path):
        print("\nAplicando a LimiarizacaoOtsu...")
        #inicioLO = time.time()
        img=cv2.imread(path,0)
        th = 0
        max_val = 255
        ret, o3 = cv2.threshold(img, th, max_val, cv2.THRESH_TOZERO + cv2.THRESH_OTSU )
        cv2.imwrite(path,o3)
        
        #fimLO = time.time()
        #print("Tempo de execução da Limiarização Otsu: {:.2f}".format(fimLO-inicioLO),"segundos.")
	
    def Logaritmo(path):
        print("\nAplicando o Filtro Logaritmo...")
        #inicioLog = time.time()
        img=cv2.imread(path)
        def filtrolog(alfa):
            Logaritmo=[]
            for i in range(256):
                Logaritmo.append(int((255/(math.log(alfa*255+1)))*(math.log(alfa*i+1))))
            return Logaritmo
        nValores=filtrolog(1)
        for i in range(img.shape[0]):
            for j in range(img.shape[1]):
                img.itemset((i,j,0), nValores[img.item(i,j,0)])
                img.itemset((i,j,1), nValores[img.item(i,j,1)])
                img.itemset((i,j,2), nValores[img.item(i,j,2)])
        cv2.imwrite(path,img)
        #fimLog = time.time()
        #print("Tempo de execução da Logaritmo: {:.2f}".format(fimLog-inicioLog),"segundos")

    def FiltroMedia(path):
        print("\nAplicando Filtro da Media...")
        #inicioMe = time.time()
        img=cv2.imread(path,0)
        aux=np.zeros((img.shape[0],img.shape[1]),dtype=np.int)
        for i in range(1,img.shape[0]-1):
            for j in range(1,img.shape[1]-1):
                valor=float(img.item(i-1,j-1)+img.item(i-1,j)+img.item(i-1,j+1)+img.item(i,j-1)+img.item(i,j)+img.item(i,j+1)+img.item(i+1,j-1)+img.item(i+1,j)+img.item(i+1,j+1))
                valor=valor/9.0
                aux.itemset((i,j),int(valor))
        
        cv2.imwrite(path,img)
        #fimMe = time.time()
        #print("Tempo de execução da Media: {:.2f}".format(fimMe-inicioMe),"segundos")
        return aux       
       
    def Equalização(path):
        print("\nAplicando Filtro de Equalização...")
        #inicioEqua = time.time()
        img=cv2.imread(path)
        img_to_yuv = cv2.cvtColor(img, cv2.COLOR_BGR2YUV)
        img_to_yuv[:, :, 0] = cv2.equalizeHist(img_to_yuv[:, :, 0])
        hist_equalization_result = cv2.cvtColor(img_to_yuv, cv2.COLOR_YUV2BGR)
        cv2.imwrite(path, hist_equalization_result)
        #fimEqua = time.time()
        #print("Tempo de execução da Equalização: {:.2f}".format(fimEqua-inicioEqua),"segundos")


    def FiltroSeno(path):
        print("\nAplicando o Filtro Seno...")
        #inicioSen = time.time()
        img=cv2.imread(path)
        def filtroseno():
            Seno=[]
            for i in range(256):
                Seno.append(int(255*math.sin((3.1416*i)/510)))
            return Seno
        nValores=filtroseno()
        for i in range(img.shape[0]):
            for j in range(img.shape[1]):
                img.itemset((i,j,0), nValores[img.item(i,j,0)])
                img.itemset((i,j,1), nValores[img.item(i,j,1)])
                img.itemset((i,j,2), nValores[img.item(i,j,2)])
        
        cv2.imwrite(path,img)
        #fimSen = time.time()
        #print("Tempo de execução da Seno: {:.2f}".format(fimSen-inicioSen),"segundos")

    def FiltroCos(path):
        print("\nAplicando o Filtro Cosseno...")
        #inicioCos = time.time()
        img=cv2.imread(path)
        def filtrcosseno():
            Cosseno=[]
            for i in range(256):
                Cosseno.append(int(255*(1-math.cos((3.1416*i)/510))))
            return Cosseno
        nValores=filtrcosseno()
        

        for i in range(img.shape[0]):
            for j in range(img.shape[1]):
                img.itemset((i,j,0), nValores[img.item(i,j,0)])
                img.itemset((i,j,1), nValores[img.item(i,j,1)])
                img.itemset((i,j,2), nValores[img.item(i,j,2)])

        cv2.imwrite(path,img)
        #fimCos = time.time()
        #print("Tempo de execução da Cosseno: {:.2f}".format(fimCos-inicioCos),"segundos")

    def Negativo(path):
        print("\nAplicando o Filtro de Negativo...")
        #inicioNeg = time.time()
        img=cv2.imread(path) 
        img_not = cv2.bitwise_not(img)
        cv2.imwrite(path,img_not)
        #fimNeg = time.time()
        #print("Tempo de execução da Negativo: {:.2f}".format(fimNeg-inicioNeg),"segundos")
        
    def MostraImagens(path):
        print("\nGerando imagens de resultado...")
        pathOut = path
        path = path.replace("_out", "")
        aa = cv2.imread(path)
        bb = cv2.imread(pathOut)
        aa = cv2.resize(aa, (640, 360))
        bb = cv2.resize(bb, (640, 360))
        telaComparativa = np.concatenate((aa,bb),axis=1)

        #fimGeral = time.time()
        #print("Tempo de execução do Segmentador: {:.2f}".format(fimGeral-inicioGeral),"segundos")
        print("Executado com sucesso!")
        
        path = path.replace(".", "_comparacao.")
        cv2.imwrite(path,telaComparativa)
        
    	cv2.imshow("Resultado da Segmentação", telaComparativa)

        cv2.waitKey(0) 
        cv2.destroyAllWindows()
        

    #indica que a cópia da imagem que será aplicada os filtros
    path = preparaSaida(path)
    
    LimiarizacaoOtsu(path)
    Logaritmo(path)
    FiltroMedia(path)
    Equalização(path)
    FiltroSeno(path)
    FiltroCos(path)
    Negativo(path)
    MostraImagens(path)


