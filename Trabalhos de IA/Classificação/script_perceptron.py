import arquivos
import perceptron

def validacao_perceptron():
	train, teste = list(), list()
	op = 0
	dados_validacao = list()
	data = arquivos.fit_data()
	saidas = arquivos.gera_saida_perceptron(data)
	rede = perceptron.Perceptron(data, saidas)
	rede.train()
	while op < 10:
		data = arquivos.fit_data()
		teste, train = arquivos.validacao_cruzada(data, op)
		print("Testes: ", len(teste))
		print("Treino: ", len(train))
		porcentagem = perceptron.execute_teste(rede, teste)
		dados_validacao.append([len(train), len(teste), porcentagem])
		op+=1
	file = open("validacao_perceptron.txt", 'w')
	file.write("Resultados obtidos através de Validação cruzada para o algoritmo Perceptron \n")
	file.write("Algoritmo rodando com 1000 epocas e 0.005 de taxa de aprendizado.")
	file.write("Amostras de treino, Amostras de teste, Porcentagem de acertos\n")
	for amostra in dados_validacao:
		file.write(str(amostra) + "\n")
	file.close()

if __name__ == '__main__':
	validacao_perceptron()
