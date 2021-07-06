#!/usr/bin/python3
#-*-encoding:utf8-*-

#Rede perceptron

import numpy as np
import math
import random
import arquivos

class Perceptron:
    def __init__(self, amostras, saidas, taxa_aprendizado = 0.005, epocas = 1000, limiar = -1):
        self.amostras = amostras
        self.saidas = saidas
        self.taxa_aprendizado = taxa_aprendizado
        self.epocas = epocas
        self.limiar = limiar
        self.n_amostras = len(amostras)
        self.n_atrib = len(amostras[0])
        self.pesos = []

    def train(self):
        print("Training!", end = "\n")
        for amostra in self.amostras:
            amostra.insert(0, -1)
        for i in range(self.n_atrib):
            self.pesos.append(random.random())
        self.pesos.insert(0, self.limiar)
        n_epocas = 0 #contador para as épocas
        while True:
            erro = False
            for i in range(self.n_amostras):
                u = 0
                for j in range(self.n_atrib):
                    u += self.pesos[j] * self.amostras[i][j]
                y = self.sinal(u) #obtem a saida da rede
                #verifica se a saida da rede é diferente da saida desejada
                if y != self.saidas[i]:
                    erro_aux = self.saidas[i] - y
                    #ajusta pesos
                    for j in range(self.n_atrib):
                        self.pesos[j] = self.pesos[j] + self.taxa_aprendizado * erro_aux * self.amostras[i][j]
                    erro = True #erro ainda existente
            n_epocas += 1
            print("Época: %d" % n_epocas)
            #parada
            if not erro or n_epocas > self.epocas:
                break

    def teste(self, amostra):
        amostra.insert(0, -1)
        u = 0
        for i in range(self.n_atrib):
            u += self.pesos[i] * amostra[i]
        y = self.sinal(u)
        print('Classificado')
        return y


    def degrau(self, u):
        if u >= 0:
            return 1
        else:
            return 0

    def sinal(self, u):
        if u >= 0:
            return 1
        else:
            return -1


def execute(data):
    saidas = arquivos.gera_saida_perceptron(data)
    rede = Perceptron(data, saidas)
    rede.train()
    print("Rede treinada", end = "\n")

    train, teste = arquivos.gera_bases(data)

    acertos = 0
    for amostra in teste:
        classe = rede.teste(amostra)
        if classe == amostra[-1]:
            acertos += 1
    print('Total de Train: %d' % len(train))
    print('Total de testes: %d' % len(teste))
    print('Total de acertos: %d' % acertos)
    print('Porcentagem de acertos: %.2f%%' % (100 * acertos / len(teste)))

def execute_teste(rede, teste):
    acertos =0
    for amostra in teste:
        classe = rede.teste(amostra)
        if classe == amostra[-1]:
            acertos += 1
    print('Total de testes: %d' % len(teste))
    print('Total de acertos: %d' % acertos)
    print('Porcentagem de acertos: %.2f%%' % (100 * acertos / len(teste)))
    return (100 * acertos / len(teste))
