from dbz import *
from cosmetico import *
from random import *

cima = 1
baixo = 2
direita = 4
esquerda = 3

caminho = list() #lista aberta do caminho percorrido
posCaminho = list()
def setorBorda(setores):
	if setores['norte'] > 0 and setores['nordeste'] == 0 or setores['norte'] > 0 and setores['noroeste'] == 0:
		return 'norte'
	elif setores['nordeste'] > 0 and setores['leste'] == 0 or setores['nordeste'] and setores['norte'] == 0:
		return 'nordeste'
	elif setores['leste'] > 0 and setores['nordeste'] == 0 or setores['leste'] > 0 and setores['suldeste'] == 0:
		return 'leste'
	elif setores['suldeste'] > 0 and setores['leste'] == 0 or setores['suldeste'] > 0 and setores['sul'] == 0:
		return 'suldeste'
	elif setores['sul'] > 0 and setores['suldeste'] == 0 or setores['sul'] > 0 and setores['suldoeste'] == 0:
		return 'sul'
	elif setores['suldoeste'] > 0 and setores['sul'] == 0 or setores['suldoeste'] > 0 and setores['oeste'] == 0:
		return 'suldoeste'
	elif setores['oeste'] > 0 and setores['suldoeste'] == 0 or setores['oeste'] > 0 and setores['noroeste'] == 0:
		return 'oeste'
	else:
		return 'noroeste'

def capture_sphere(posx, posy, mapa, esferax, esferay):
	if posx < esferax and posx+1 <= len(mapa):
		caminho.append((return_weight(posx+1, posy, mapa), direita, (posx+1, posy)))
		return direita
	elif posx > esferax and posx-1 >= 0:
		caminho.append((return_weight(posx-1, posy, mapa), esquerda, (posx-1, posy)))
		return esquerda
	if posy < esferay and posy+1 <= len(mapa):
		caminho.append((return_weight(posx, posy+1, mapa), baixo, (posx, posy+1)))
		return baixo
	elif posy > esferay and posy-1 >= 0:
		caminho.append((return_weight(posx, posy-1, mapa), cima, (posx, posy-1)))
		return cima

def is_not_kame_house(posx, posy, kamex, kamey):
	return posx != kamex or posy != kamey

def valid_movement(posx, posy, mapa, kamex, kamey):
	if 0 <= posx <= len(mapa) and 0 <= posy <= len(mapa) and is_not_kame_house(posx, posy, kamex, kamey):
		return True
	else:
		return False

def return_weight(posx, posy, mapa):
	return mapa[posx][posy]

def go_to_kame_house(posx, posy, mapa, kamex, kamey):
	if posx < kamex and posx+1 <= len(mapa):
		caminho.append((posx+1, posy))
		return direita
	elif posx > kamex and posx-1 >= 0:
		caminho.append((posx-1, posy))
		return esquerda
	if posy < kamey and posy+1 <= len(mapa):
		caminho.append((posx, posy+1))
		return baixo
	elif posy > kamey and posy-1 >= 0:
		caminho.append((posx, posy-1))
		return cima

def valid_path(posx, posy):
	posxcaminho = caminho[len(caminho)-1][0]
	posycaminho = caminho[len(caminho)-1][1]
	print("pos: (" + str(posx) + ", " + str(posy) + ")")
	print("poscaminho: (" + str(posxcaminho) + ", " + str(posycaminho) + ")")
	for i,k in enumerate(caminho):
		if posx != caminho[i][0] or posy != caminho[i][1]:
			flag = True
		else:
			flag = False

	return flag
#	if posx != posxcaminho or posy != posycaminho:
#		return True
#	else:
#		return False

#olhar de 10 em 10 caminhos
def gera_custo_cima(posx, posy, mapa):
	if posy-8 >= 0: 
		custo = mapa[posx][posy-1] + mapa[posx][posy-2] + mapa[posx][posy-3] + mapa[posx][posy-4] + mapa[posx][posy-5] + mapa[posx][posy-6] + mapa[posx][posy-7] + mapa[posx][posy-8]
		return custo
	elif posy-1 >= 0:
		return mapa[posx][posy-1]
	else:
		return mapa[posx][posy]


def gera_custo_baixo(posx, posy, mapa):
	if posy+8 < len(mapa): 
		custo = mapa[posx][posy+1] + mapa[posx][posy+2] + mapa[posx][posy+3] + mapa[posx][posy+4] + mapa[posx][posy+5] + mapa[posx][posy+6] + mapa[posx][posy+7] + mapa[posx][posy+8]
		return custo
	elif posy+1 < len(mapa):
		return mapa[posx][posy+1]
	else: return mapa[posx][posy]

def gera_custo_direita(posx, posy, mapa):
	if posx+8 < len(mapa): 
		custo = mapa[posx+1][posy] + mapa[posx+2][posy] + mapa[posx+3][posy] + mapa[posx+4][posy] + mapa[posx+5][posy] + mapa[posx+6][posy] + mapa[posx+7][posy] + mapa[posx+8][posy]
		return custo
	elif posx+1 < len(mapa):
		return mapa[posx+1][posy]
	else: return mapa[posx][posy]

def gera_custo_esquerda(posx, posy, mapa):
	if posx-8 >= 0: 
		custo = mapa[posx-1][posy] + mapa[posx-2][posy] + mapa[posx-3][posy] + mapa[posx-4][posy] + mapa[posx-5][posy] + mapa[posx-6][posy] + mapa[posx-7][posy] + mapa[posx-8][posy]
		return custo
	elif posx-1 >= 0:
		return mapa[posx-1][posy]
	else:
		return mapa[posx][posy]
'''
buscando custo de 8 posicoes, fazemos com que o custo para cada lado seja mais real e pesado, assim determinando com mais integridade qual o melhor lado para seguir
e tambem faz com que o código seja maleável à labirintos.
'''
def search_path(posx, posy, mapa, kamex, kamey, setor, radar_prox):
	franja = list()
	setorborda = setorBorda(setor)
	print(setor)
	print(setorborda)
	custo_total = 0
	custo_total1 = 0
	custo_total2 = 0
	if len(radar_prox) == 0:
		if setorborda == 'norte':
			custo_total = gera_custo_direita(posx, posy, mapa)
			custo_total1 = gera_custo_esquerda(posx, posy, mapa)
			custo_total2 = gera_custo_cima(posx, posy, mapa)
			if posx+1 < len(mapa): franja.append((custo_total, direita, (posx+1, posy))) #direita
			if posx-1 >= 0: franja.append((custo_total1, esquerda,(posx-1, posy))) #esquerda
			if posy-1 >= 0 : franja.append((custo_total2, cima, (posx, posy-1))) #cima
			franja = sorted(franja)
			if len(franja) > 0:
				caminho.append(franja[0])
				if tuple(franja[0][2]) not in posCaminho and is_not_kame_house(franja[0][2][0], franja[0][2][1], kamex, kamey):
					posCaminho.append(franja[0][2])
					return franja[0][1]
				else:
					del(franja[0])
					sorted(franja)
					if len(franja) > 0:
						caminho.append(franja[0])
						posCaminho.append(franja[0][2])
						return franja[0][1]
					elif posy-1 > 0:
						return cima	
		elif setor == 'nordeste':
			#ando pra cima e pra direita
			custo_total = gera_custo_direita(posx, posy, mapa)
			custo_total1 = gera_custo_cima(posx, posy, mapa)
			if posx+1 < len(mapa): franja.append((custo_total, direita, (posx+1, posy)))
			if posy-1 >= 0 : franja.append((custo_total1, cima, (posx, posy-1)))
			franja = sorted(franja)
			if len(franja) > 0:
				caminho.append(franja[0])
				if tuple(franja[0][2]) not in posCaminho and is_not_kame_house(franja[0][2][0], franja[0][2][1], kamex, kamey):
					posCaminho.append(franja[0][2])
					return franja[0][1]
				else:
					del(franja[0])
					sorted(franja)
					if len(franja) > 0:
						caminho.append(franja[0])
						posCaminho.append(franja[0][2])
						return franja[0][1]
					elif posx+1 < len(mapa):
						return direita	
		elif setor == 'leste':
			custo_total = gera_custo_direita(posx, posy, mapa)
			custo_total1 = gera_custo_baixo(posx, posy, mapa)
			custo_total2 = gera_custo_cima(posx, posy, mapa)
			if posx+1 < len(mapa): franja.append((custo_total, direita, (posx+1, posy))) #direita
			if posy-1 >= 0 : franja.append((custo_total2, cima, (posx, posy-1))) #cima
			if posy+1 < len(mapa): franja.append((custo_total1, baixo, (posx, posy+1))) #baixo
			franja = sorted(franja)
			if len(franja) > 0:
				caminho.append(franja[0])
				if tuple(franja[0][2]) not in posCaminho and is_not_kame_house(franja[0][2][0], franja[0][2][1], kamex, kamey):
					posCaminho.append(franja[0][2])
					return franja[0][1]
				else:
					del(franja[0])
					sorted(franja)
					if len(franja) > 0:
						caminho.append(franja[0])
						posCaminho.append(franja[0][2])
						return franja[0][1]
					elif posx+1 < len(mapa):
						return direita
		elif setor == 'suldeste':
			#baixo e direita
			custo_total = gera_custo_direita(posx, posy, mapa)
			custo_total1 = gera_custo_baixo(posx, posy, mapa)
			if posx+1 < len(mapa): franja.append((custo_total, direita, (posx+1, posy))) #direita
			if posy+1 < len(mapa): franja.append((custo_total1, baixo, (posx, posy+1)))#baixo
			franja = sorted(franja)
			if len(franja) > 0:
				caminho.append(franja[0])
				if tuple(franja[0][2]) not in posCaminho and is_not_kame_house(franja[0][2][0], franja[0][2][1], kamex, kamey):
					posCaminho.append(franja[0][2])
					return franja[0][1]
				else:
					del(franja[0])
					sorted(franja)
					if len(franja) > 0:
						caminho.append(franja[0])
						posCaminho.append(franja[0][2])
						return franja[0][1]
					elif posx+1 < len(mapa):
						return direita
		elif setor == 'sul':
			custo_total = gera_custo_baixo(posx, posy, mapa)
			custo_total1 = gera_custo_direita(posx, posy, mapa)
			custo_total2 = gera_custo_esquerda(posx, posy, mapa)
			if posx+1 < len(mapa): franja.append((custo_total1, direita, (posx+1, posy))) #direita
			if posy+1 < len(mapa): franja.append((custo_total, baixo, (posx, posy+1))) #baixo
			if posx-1 >= 0: franja.append((custo_total2, esquerda,(posx-1, posy))) #esquerda
			franja = sorted(franja)
			if len(franja) > 0:
				caminho.append(franja[0])
				if tuple(franja[0][2]) not in posCaminho and is_not_kame_house(franja[0][2][0], franja[0][2][1], kamex, kamey):
					posCaminho.append(franja[0][2])
					return franja[0][1]
				else:
					del(franja[0])
					sorted(franja)
					if len(franja) > 0:
						caminho.append(franja[0])
						posCaminho.append(franja[0][2])
						return franja[0][1]
					elif posy+1 < len(mapa):
						return baixo
		elif setor == 'suldoeste':
			custo_total = gera_custo_baixo(posx, posy, mapa)
			custo_total1 = gera_custo_esquerda(posx, posy, mapa)
			if posy+1 < len(mapa): franja.append((custo_total, baixo, (posx, posy+1))) #baixo
			if posx-1 >= 0: franja.append((custo_total1, esquerda,(posx-1, posy))) #esquerda
			franja = sorted(franja)
			if len(franja) > 0:
				caminho.append(franja[0])
				if tuple(franja[0][2]) not in posCaminho and is_not_kame_house(franja[0][2][0], franja[0][2][1], kamex, kamey):
					posCaminho.append(franja[0][2])
					return franja[0][1]
				else:
					del(franja[0])
					sorted(franja)
					if len(franja) >= 1:
						caminho.append(franja[0])
						posCaminho.append(franja[0][2])
						return franja[0][1]
					elif posy+1 < len(mapa):
						return baixo
		elif setor == 'oeste':
			#cima baixo esquerda
			custo_total = gera_custo_esquerda(posx, posy, mapa)
			custo_total1 = gera_custo_baixo(posx, posy, mapa)
			custo_total2 = gera_custo_cima(posx, posy, mapa)
			if posy+1 < len(mapa): franja.append((custo_total1, baixo, (posx, posy+1))) #baixo
			if posx-1 >= 0: franja.append((custo_total, esquerda,(posx-1, posy))) #esquerda
			if posy-1 >= 0 : franja.append((custo_total2, cima, (posx, posy-1))) #cima
			franja = sorted(franja)
			if len(franja) > 0:
				caminho.append(franja[0])
				if tuple(franja[0][2]) not in posCaminho and is_not_kame_house(franja[0][2][0], franja[0][2][1], kamex, kamey):
					posCaminho.append(franja[0][2])
					return franja[0][1]
				else:
					del(franja[0])
					sorted(franja)
					if len(franja) >= 1:
						caminho.append(franja[0])
						posCaminho.append(franja[0][2])
						return franja[0][1]
					elif posx-1 >= 0:
						return esquerda
		else:
			#esquerda cima
			custo_total = gera_custo_esquerda(posx, posy, mapa)
			custo_total1 = gera_custo_cima(posx, posy, mapa)
			if posx-1 >= 0: franja.append((custo_total, esquerda,(posx-1, posy))) #esquerda
			if posy-1 >= 0 : franja.append((custo_total1, cima, (posx, posy-1))) #cima
			franja = sorted(franja)
			if len(franja) > 0:
				caminho.append(franja[0])
				if tuple(franja[0][2]) not in posCaminho and is_not_kame_house(franja[0][2][0], franja[0][2][1], kamex, kamey):
					posCaminho.append(franja[0][2])
					return franja[0][1]
				else:
					del(franja[0])
					sorted(franja)
					if len(franja) >= 1:
						caminho.append(franja[0])
						posCaminho.append(franja[0][2])
						return franja[0][1]
					elif posx-1 >= 0:
						return esquerda
	else:
		radar_prox = sorted(radar_prox)
		esfera = radar_prox[0]
		esferax = esfera[0]
		esferay = esfera[1]
		return capture_sphere(posx, posy, mapa, esferax, esferay)

def joao_pascal_albuquerque(info):
	mapa = info['mapa']
	posx, posy = info['pos'][0], info['pos'][1]
	kamex, kamey = info['casa-kame'][0], info['casa-kame'][1]
	while info['esferas'] > 0:
		return search_path(posx, posy, mapa, kamex, kamey, info['radar-direcao'], info['radar-proximo'])

	if info['esferas'] == 0:
		return go_to_kame_house(posx, posy, mapa, kamex, kamey)

if __name__ == "__main__":
	dbz = DragonBallZ(joao_pascal_albuquerque, tamanho = 10,semente=0)
	executar_jogo(dbz)
'''
a heuristica apresentada para o problema é extremamente dependente de um funcionamento correto da função radar-direcao. Tal não
apresenta funcionamento correto, sendo que para testes (tam = 10, semente = 10), ao se encontrar no topo do mapa aonde não há possibilidade de 
andar mais para o norte, o radar direcao apresenta esferas no norte, fato que nao deveria ocorrer!
'''