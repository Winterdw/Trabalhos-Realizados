import sklearn.svm
import arquivos
import random

def validacao_nb():
	train, teste = list(), list()
	op = 0
	dados_validacao = list()
	model = sklearn.svm.SVC()
	data = arquivos.fit_data()
	random.shuffle(data, random.random)
	while op < 10:
		teste, train = arquivos.validacao_cruzada_invertida(data, op)
		saidas = arquivos.gera_saida_perceptron(train)
		expec = arquivos.gera_saida_perceptron(teste)
		model.fit(train, saidas)
		predic = model.predict(teste)

		acertos = 0
		for i in range(len(expec)):
			if expec[i] == predic[i]:
				acertos+=1
		porcentagem = (100 * acertos / len(teste))
		dados_validacao.append([op, porcentagem])
		op+=1
	file = open("validacao_svm2.txt", 'w')
	file.write("Resultados obtidos através de Validação cruzada para o algoritmo Support Vector Machine utilizando biblioteca sklearn \n")
	file.write("Opcao da amostra, porcentagem de acerto\n")
	for amostra in dados_validacao:
		file.write(str(amostra) + "\n")
	file.close()


if __name__ == '__main__':
	validacao_nb()