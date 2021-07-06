import arquivos
import knn

def validacao_knn():
	op = 0
	dados_validacao = list()
	K = 71
	while op < 10:
		data = arquivos.fit_data()
		teste, train = arquivos.validacao_cruzada(data, op)
		print("Testes: ", len(teste))
		print("Treino: ", len(train))
		porcentagem = knn.rodar_knn(train, teste, K)
		dados_validacao.append([K, porcentagem, op])
		op+=1

	file = open("validacao_knn.txt", 'w')
	file.write("Resultados obtidos através de Validação cruzada para o algoritmo KNN \n")
	file.write("K, Porcentagem de Acertos, Range dos dados \n")
	for amostra in dados_validacao:
		file.write(str(amostra))
	file.close()


if __name__ == '__main__':
	validacao_knn()

