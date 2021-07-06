import random
#Metodologia usado para aleatoriezar os algoritmos a fim de tentar uma classificação de alguma classe esperada.

listaFiltros=["Convolucao_Bordas","Equalização_Histograma","Filtro_Cosseno","Filtro_logaritmo","Filtro_Media","Filtro_Mediana","Filtro_Seno","Filto_Cosseno","FiltroGausiano","Filtro_Laplaciano","LimiarizaçãoIterativa","LimiraziaçãoLocal","LimizarizaçãoOtsu","Filtro_MediaPonderada","FiltroNegativo","Filtro_Sobel"]

random.shuffle(listaFiltros)
for i in listaFiltros:
  print(i)
  
#random.sample(listaFiltros, 12)

'''
Fundamentos de imagens digitais (2/3)

● Operações aritméticas sobre imagens (F)
● Operações lógicas sobre imagens (F)

Transformações de intensidade (2/8)

● Negativo de uma imagem (F)
● Equalização de histograma (F)

Filtragem espacial para suavização (2/5)

● Filtro de média (F)
● Filtro de média ponderada (M)
● Filtro gaussiano (F)
● Filtro da mediana (F)

Filtragem espacial para aguçamento (2/3)

● Laplaciano (F)
● Gradiente (F)

Segmentação – Detecção de bordas (2/3)

● Efeitos da suavização da detecção de bordas (M)
● Efeitos da limiarização na detecção de bordas (M)

Segmentação – Limiarização (2/5)

● Limiarização iterativa (M)
● Limiarização utilizando o método de Otsu (M)
● Efeito da suavização na limiarização (D)
● Usando bordas para melhorar a limiarização. (D)
● Limiarização local (D)

'''
