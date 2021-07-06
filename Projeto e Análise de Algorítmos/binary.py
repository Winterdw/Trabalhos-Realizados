#!/usr/bin/python3
#-*-encoding:utf8-*-

#Júlio César Machado Álvares - 0023163
#Daniel Winter Santos Rocha - 0021760

#Implementação para propor solução para o problema Binary Knapsack


from random import random

def gerar_dados(qtd_tuplas = 500, range_peso = 50, range_valor = 50):
	file = open("data.csv", "w")
	for i in range(qtd_tuplas):
		data = int((random()*int(range_peso))+1)	
		data1 = int((random()*int(range_valor))+1)
		file.write(str(data)+ "," + str(data1) + ",")
		file.write("\n")
	file.close()


def ler_dados():
	data = list()
	file = open("data.csv", "r")
	for linha in file:
		v = linha.split(",")
		data1 = int(v[0])
		data2 = int(v[1])
		data.append([data1, data2, 0])
	return data


def min_peso(data, peso = 200):
	data.sort(key=lambda x: x[0], reverse = False)
	itens = list()
	pesoAtual = 0	
	for i in range(len(data)):
		if pesoAtual < peso:
			itens.append(data[i])
			pesoAtual = pesoAtual + data[i][0]
		elif pesoAtual > peso:
			itens.pop(len(itens)-1)
			return itens
		else:
			return itens

def max_valor(data, peso = 200):
	data.sort(key = lambda x: x[1], reverse = True)
	itens = list()
	pesoAtual = 0
	for i in range(len(data)):
		if pesoAtual < peso:
			itens.append(data[i])
			pesoAtual+=data[i][0]
		elif pesoAtual > peso:
			itens.pop(len(itens)-1)
			return itens
		else:
			return itens

def heuristica(data, peso = 200):
	for i in range(len(data)):
		data[i][2] = float(data[i][0]/data[i][1])
	data.sort(key = lambda x: x[2], reverse = False)
	itens = list()
	pesoAtual = 0
	for i in range(len(data)):
		if pesoAtual < peso:
			itens.append(data[i])
			pesoAtual+=data[i][0]
		elif pesoAtual > peso:
			itens.pop(len(itens)-1)
			return itens
		else:
			return itens

def calc_peso(data):
	pesoAtual = 0
	for i in range(len(data)):
		pesoAtual+=data[i][0]
	return pesoAtual

def calc_valor(data):
	valorAtual = 0
	for i in range(len(data)):
		valorAtual += data[i][1]
	return valorAtual
#Tuplas onde o primeiro item é o peso e o segundo o valor. (peso, valor)


def execute():
	data = list()
	qtd_tuplas = int(input("\nDigite a quantidade de itens: "))
	range_peso = int(input("Digite o range de pesos dos itens: "))
	range_valor = int(input("Digite o range de valores dos itens: "))

	gerar_dados(qtd_tuplas = qtd_tuplas, range_peso = range_peso, range_valor = range_valor)
	data = ler_dados()

	peso = int(input("Digite o peso total suportado: "))
	itens_min_peso = min_peso(data, peso)
	print("\t---Minimizado pelo peso---\n")
	print("Peso: ", calc_peso(itens_min_peso), "Valor: ", calc_valor(itens_min_peso))

	itens_max_valor = max_valor(data, peso)
	print("\n\n\t---Maximizado pelo valor---\n")
	print("Peso: ", calc_peso(itens_max_valor), "Valor: ", calc_valor(itens_max_valor))

	itens_heur = heuristica(data, peso)
	print("\n\n\t---Otimizado com heuristica---\n")
	print("Peso: ", calc_peso(itens_heur), "Valor: ", calc_valor(itens_heur))




if __name__ == "__main__":
	execute()