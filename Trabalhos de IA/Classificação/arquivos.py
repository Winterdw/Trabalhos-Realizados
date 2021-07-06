#!/usr/bin/python3
#-*-encoding:utf8-*-

import sklearn.feature_extraction.text
import numpy as np
import random

def fit_data():
    tfidf = sklearn.feature_extraction.text.TfidfVectorizer()
    dados_pos, dados_neg = list(), list()
    for i in range(12500):
        arq = "pos/" + str(i) + "_10.txt"
        dados_pos.append(tfidf.fit_transform(open(arq)).data)

    for i in range(12500):
        arq = "neg/" + str(i) + "_1.txt"
        dados_neg.append(tfidf.fit_transform(open(arq)).data)

    dados_pos, dados_neg = modulariza_dados(data_pos = dados_pos, data_neg = dados_neg)
    dados_pos,dados_neg = normaliza_dados(data_pos = dados_pos, data_neg = dados_neg)

    total_dados = list()
    for i in range(len(dados_pos)):
        total_dados.append(dados_pos[i])
        total_dados.append(dados_neg[i])
    return total_dados


def validacao_cruzada(data, op):
    teste = list()
    train = list()
    if op == 0:
        teste = data[:2500]
        train = data[2500:25000]
        return teste, train
    if op == 1:
        teste = data[2500:5000]
        train = data[:2499] + data[2499+2500: 25000]
        return teste, train
    if op == 2:
        teste = data[5000:7500]
        train = data[:4999] + data[4999+2500:25000]
        return teste, train
    if op == 3:
        teste = data[7500:10000]
        train = data[:7499] + data[7499+2500:25000]
        return teste, train
    if op == 4:
        teste = data[10000:12500]
        train = data[:9999] + data[9999+2500:25000]
        return teste, train
    if op == 5:
        teste = data[12500:15000]
        train = data[:12499] + data[12499+2500:25000]
        return teste, train
    if op == 6:
        teste = data[15000:17500]
        train = data[:14999] + data[14999+2500:25000]
        return teste, train
    if op == 7:
        teste = data[17500:20000]
        train = data[:17499] + data[17999+2500:25000]
        return teste, train
    if op == 8:
        teste = data[20000:22500]
        train = data[:19999] + data[19999+2500:25000]
        return teste, train
    if op == 9:
        teste = data[22500:25000]
        train = data[:22500]
        return teste, train


def validacao_cruzada_invertida(data, op):
    teste = list()
    train = list()
    if op == 0:
        teste = data[:2500]
        train = data[2500:25000]
        return train, teste 
    if op == 1:
        teste = data[2500:5000]
        train = data[:2499] + data[2499+2500: 25000]
        return train, teste 
    if op == 2:
        teste = data[5000:7500]
        train = data[:4999] + data[4999+2500:25000]
        return train, teste 
    if op == 3:
        teste = data[7500:10000]
        train = data[:7499] + data[7499+2500:25000]
        return train, teste 
    if op == 4:
        teste = data[10000:12500]
        train = data[:9999] + data[9999+2500:25000]
        return train, teste 
    if op == 5:
        teste = data[12500:15000]
        train = data[:12499] + data[12499+2500:25000]
        return train, teste 
    if op == 6:
        teste = data[15000:17500]
        train = data[:14999] + data[14999+2500:25000]
        return train, teste 
    if op == 7:
        teste = data[17500:20000]
        train = data[:17499] + data[17999+2500:25000]
        return train, teste 
    if op == 8:
        teste = data[20000:22500]
        train = data[:19999] + data[19999+2500:25000]
        return train, teste 
    if op == 9:
        teste = data[22500:25000]
        train = data[:22500]
        return train, teste 








def normaliza_dados(data_neg, data_pos):
    for i in range(len(data_neg)):
        while(len(data_neg[i])) < 964:
            data_neg[i].append(0)
        while(len(data_pos[i])) < 964:
            data_pos[i].append(0)
        data_neg[i].append(-1)
        data_pos[i].append(1)
    return data_pos, data_neg


def modulariza_dados(data_pos, data_neg):
    data_negativa = list()
    data_positiva = list()
    for i in range(len(data_pos)):
        data_negativa.append(list(data_neg[i]))
        data_positiva.append(list(data_pos[i]))
    return data_positiva, data_negativa

def gera_bases(data, p_train = 0.1):
    random.shuffle(data, random.random)
    q_train = int(p_train*len(data))
    print("Tamanho da base de teste %d" % q_train)
    teste = list()

    for i in range(q_train):
        teste.append(data[i])

    for i in range(q_train):
        data.pop(0)

    return data, teste


def gera_saida_perceptron(data):
    saida = list()
    for i in range(len(data)):
        saida.append(data[i][-1])
    return saida

def gera_base_testes(data, p):
    qt_teste = int(1000 * p)
    print(qt_teste)
    train = list()
    teste = list()
    for i in range(qt_teste):
        teste.append(data[i])

    for i in range(1000 - qt_teste):
        train.append(data[i])

    return train, teste, (train+teste)




