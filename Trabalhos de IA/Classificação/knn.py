#!/usr/bin/python3
#-*-encoding:utf8-*-
import numpy as np
import math
import matplotlib.pyplot as plt
import random
import arquivos

def dist_euclidiana(p, q):
    dim, soma = len(p), 0
    for i in range(dim -1):
        soma+= math.pow(p[i] - q[i],2)
    return math.sqrt(soma)

def info_data(amostras, verbose = True):
    if verbose:
        print('Total de amostras: %d' % len(amostras))
    r1, r2 = 0, 0
    for amostra in amostras:
        if amostra[-1] == 1:
            r1 += 1
        else:
            r2 += 1
    if verbose:
        print('Total classe 1: %d' % r1)
        print('Total classe 2: %d' % r2)
    return [len(amostras), r1, r2]

def make_data(amostras, rot1, rot2, p):
    max_rot1, max_rot2 = int(p*rot1), int(p*rot2)
    total_rot1, total_rot2 = 0,0
    train, teste = [], []
    for amostra in amostras:
        if total_rot1 + total_rot2 < max_rot1 + max_rot2:
            train.append(amostra)
            if amostra[-1] == 1 and total_rot1 < max_rot1:
                total_rot1+=1
            else:
                total_rot2+=1
        else:
            teste.append(amostra)
    return train, teste

def knn(train, nova_amostra, K):
    dists, tam_train = {}, len(train)

    #calculando a distancia da nova amostra para todos os outros exemplos de trainamento
    for i in range(tam_train):
        d = dist_euclidiana(train[i], nova_amostra)
        dists[i] = d

    #obtem as keys dos k-vizinhos mais proximos
    k_vizinhos = sorted(dists, key = dists.get)[:K]

    #votação
    qtd_r1, qtd_r2 = 0,0 #quantidade de cada classe
    for index in k_vizinhos:
        if train[index][-1] == 1:
            qtd_r1+=1
        else:
            qtd_r2+=1

    if qtd_r1 > qtd_r2:
        return 1
    else:
        return -1


def rodar_knn(train, teste, K):
    acertos = 0
    cont = 1
    for amostra in teste:
        classe = knn(train, amostra, K)
        print("Classificado ", cont, end = "\n")
        cont+=1
        if amostra[-1] == classe:
            acertos+=1
    print('Total de Train: %d' % len(train))
    print('Total de testes: %d' % len(teste))
    print('Total de acertos: %d' % acertos)
    print('Porcentagem de acertos: %.2f%%' % (100 * acertos / len(teste)))
    return (100*acertos / len(teste))


if __name__ == '__main__':
#amostras dos dados

    data = arquivos.fit_data()
    _, r1, r2 = info_data(data, True)
    train, teste = arquivos.gera_bases(data)
    K = int(input("Defina o valor de K:"))
    
    rodar_knn(train, teste, K)
