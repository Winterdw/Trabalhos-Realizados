from dbz import *
from cosmetico import *
from random import *
'''global pesoD
global pesoC
global pesoE
global pesoB

pesoD = 20
pesoC = 20
pesoE = 20
pesoB = 20
'''
global franja
global caminho

franja = list()
caminho = list()

#def setor_borda(setores):
#	setor = list()
#	setor = ['norte', 'nordeste', 'leste', 'suldeste', 'sul', 'suldoeste', 'oeste', 'noroeste']
#	for i,k in enumerate(setor):
#		while i < 7:
#			if setores[setor[i]] != 0 and setores[setor[i-1]] != 0:
#				return setor[i]
#			elif setores[setor[i]] != 0 and setores[setor[i+1]] != 0:
#				return setor[i]
#			else:
#				break
#		
#	if setores['norte'] != 0 and setores['noroeste'] != 0:
#		return 'norte'
#	if setores['noroeste'] != 0 and setores['norte'] != 0:
#			return 'noroeste'

def setor_borda(setores):
	setores = list()
	setores = ['norte','nordeste','leste','suldeste','sul','suldoeste','oeste','noroeste']
	if setores['norte'] > 0 and setores['nordeste'] == 0 or setores['norte'] > 0 and setores['noroeste'] == 0:
		return 'norte'
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

def retornaTuple(mapa, posx, posy, franja, movimento):
		if mapa[posx][posy] == 1: franja.append((1, movimento))
		elif mapa[posx][posy] == 2: franja.append((2, movimento))
		else: franja.append((3, movimento))
		return franja

def esferaRestante(info):
	while radar_prox ==None:
		if setores['norte']!=0: return CIMA
		if setores['leste']!=0: return ESQUERDA
		if setores['oeste']!=0: return DIREITA
		else:return BAIXO


def cimaEsquerdaDireita(posx, posy, mapa, casaKamex, casaKamey, franja, caminhonte):
	direc = -1
	if posx + 1 <= len(mapa): franja = retornaTuple(mapa, posx+1, posy, franja, DIREITA)
	if posy - 1 >= 0: franja = retornaTuple(mapa, posx, posy-1, franja, CIMA)
	if posx -1 >= 0: franja = retornaTuple(mapa, posx-1, posy, franja, ESQUERDA)
	if isnotNone(franja):	
		sorted(franja)
		caminho.append(franja[0])
		direc = franja[0][1]
		franja.pop(0)
		return direc		

def cimaBaixoEsquerda(posx, posy, mapa, casaKamex, casaKamey, franja, caminho):
	direc = -1
	if posy - 1 >= 0: franja = retornaTuple(mapa, posx, posy-1, franja, CIMA)
	if posy + 1 <= len(mapa): franja = retornaTuple(mapa, posx, posy+1, franja, BAIXO)
	if posx - 1 >= 0 : franja = retornaTuple(mapa, posx-1, posy, franja, ESQUERDA)
	if isnotNone(franja):
		sorted(franja)
		caminho.append(franja[0])
		direc = franja[0][1]
		franja.pop(0)
		return direc

def baixoDireitaEsquerda(posx, posy, mapa, casaKamex, casaKamey, franja, caminho):
	direc = -1
	if posy + 1 <= len(mapa): franja = retornaTuple(mapa, posx, posy+1, franja, BAIXO)
	if posx - 1 >= 0: franja = retornaTuple(mapa, posx-1, posy, franja, ESQUERDA)
	if posx + 1 <= len(mapa): franja = retornaTuple(mapa, posx+1, posy, franja, DIREITA)
	if isnotNone(franja):	
		sorted(franja)
		caminho.append(franja[0])
		direc = franja[0][1]
		franja.pop(0)
		return direc

def direitaBaixoCima(posx, posy, mapa, casaKamex, casaKamey, franja, caminho):
	direc = -1
	if posy - 1 >= 0: franja = retornaTuple(mapa, posx, posy-1, franja, CIMA)
	if posy + 1 <= len(mapa): franja = retornaTuple(mapa, posx, posy+1, franja, BAIXO)
	if posx + 1 <= len(mapa): franja = retornaTuple(mapa, posx+1, posy, franja, DIREITA)
	if isnotNone(franja):	
		sorted(franja)
		caminho.append(franja[0])
		direc = franja[0][1]
		franja.pop(0)
		return direc

def pegarEsfera(posx, posy, mapa, coordesfera):
	coordx = coordesfera[0]
	coordy = coordesfera[1]
	if posx < coordx and posx+1 <= len(mapa):
		return DIREITA

	if posx > coordx and posx-1 >= 0:
		return ESQUERDA

	if posy < coordy and posy+1 <= len(mapa):
		return BAIXO

	if posy > coordy and posy-1 >= 0:
		return CIMA

def pesoTerreno(mapa, posx, posy):
	return mapa[posx][posy]

def kameHouse(casaKamex, casaKamey, posatualx, posatualy):
	if casaKamey != posatualy or casaKamex != posatualx:
		return True
	else:
		return False

def andar(posx, posy, mapa, casaKamex, casaKamey, franja, caminho, setores, radar_prox,info):
	if radar_prox is None:
		if setor_borda(setores) == info['radar-direcao'['norte']]:
			#direita esquerda cima
			if posx+1 <= len(mapa) and kameHouse(casaKamex, casaKamey, posx+1, posy): franja.append((pesoTerreno(mapa, posx+1, posy), DIREITA))
			if posx-1 >= 0 and kameHouse(casaKamex, casaKamey, posx-1, posy): franja.append((pesoTerreno(mapa, posx-1, posy), ESQUERDA))
			if posy-1 >= 0 and kameHouse(casaKamex, casaKamey, posx, posy+1): franja.append((pesoTerreno(mapa,posx,posy-1), CIMA))
			sorted(franja)
			caminho.append(franja[0])
			return franja.pop(0)[1]
		elif setor_borda(setores) ==  'nordeste':
			#direita cima baixo
			print(kameHouse(casaKamex, casaKamey, posx+1, posy))
			print(kameHouse(casaKamex, casaKamey, posx, posy+1))
			print(kameHouse(casaKamex, casaKamey, posx, posy-1))
			if posx+1 <= len(mapa) and kameHouse(casaKamex, casaKamey, posx+1, posy): franja.append((pesoTerreno(mapa,posx+1, posy), DIREITA))
			if posy+1 <= len(mapa) and kameHouse(casaKamex, casaKamey, posx, posy+1): franja.append((pesoTerreno(mapa, posx, posy+1), BAIXO))
			if posy-1 >= 0 and kameHouse(casaKamex, casaKamey, posx, posy-1): franja.append((pesoTerreno(mapa,posx, posy-1), CIMA))
			sorted(franja)
			caminho.append(franja[0])
			return franja.pop(0)[1]
		elif setor_borda(setores) == 'leste':
			#direita cima baixo
			print(kameHouse(casaKamex, casaKamey, posx+1, posy))
			print(kameHouse(casaKamex, casaKamey, posx, posy+1))
			print(kameHouse(casaKamex, casaKamey, posx, posy-1))
			if posx+1 <= len(mapa) and kameHouse(casaKamex, casaKamey, posx+1, posy): franja.append((pesoTerreno(mapa,posx+1, posy), DIREITA))
			if posy+1 <= len(mapa) and kameHouse(casaKamex, casaKamey, posx, posy+1): franja.append((pesoTerreno(mapa, posx, posy+1), BAIXO))
			if posy-1 >= 0 and kameHouse(casaKamex, casaKamey, posx, posy-1): franja.append((pesoTerreno(mapa,posx, posy-1), CIMA))
			sorted(franja)
			caminho.append(franja[0])
			return franja.pop(0)[1]
			return franja.pop(0)[1]
		elif setor_borda(setores) ==  'suldeste':
			#direita cima baixo
			print(kameHouse(casaKamex, casaKamey, posx+1, posy))
			print(kameHouse(casaKamex, casaKamey, posx, posy+1))
			print(kameHouse(casaKamex, casaKamey, posx, posy-1))
			if posx+1 <= len(mapa) and kameHouse(casaKamex, casaKamey, posx+1, posy): franja.append((pesoTerreno(mapa,posx+1, posy), DIREITA))
			if posy+1 <= len(mapa) and kameHouse(casaKamex, casaKamey, posx, posy+1): franja.append((pesoTerreno(mapa, posx, posy+1), BAIXO))
			if posy-1 >= 0 and kameHouse(casaKamex, casaKamey, posx, posy-1): franja.append((pesoTerreno(mapa,posx, posy-1), CIMA))
			sorted(franja)
			caminho.append(franja[0])
			return franja.pop(0)[1]
		elif setor_borda(setores) == 'sul':
			#direita esquerda baixo
			if posx+1 <= len(mapa) and kameHouse(casaKamex, casaKamey, posx+1, posy): franja.append((pesoTerreno(mapa,posx+1, posy), DIREITA))
			if posx-1 >= 0 and kameHouse(casaKamex, casaKamey, posx-1, posy): franja.append((pesoTerreno(mapa,posx-1, posy), ESQUERDA))
			if posy+1 <= len(mapa) and kameHouse(casaKamex, casaKamey, posx, posy+1): franja.append((pesoTerreno(mapa, posx, posy+1), BAIXO))
			sorted(franja)
			caminho.append(franja[0])
			return franja.pop(0)[1]
		elif setor_borda(setores) == 'suldoeste':
			#cima, baixo esquerda
			if posy-1 >= 0 and kameHouse(casaKamex, casaKamey, posx, posy-1): franja.append((pesoTerreno(mapa,posx, posy-1), CIMA))
			if posy+1 <= len(mapa) and kameHouse(casaKamex, casaKamey, posx, posy+1): franja.append((pesoTerreno(mapa, posx,posy+1), BAIXO))
			if posx-1 >= 0 and kameHouse(casaKamex, casaKamey, posx-1, posy): franja.append((pesoTerreno(mapa, posx-1, posy), ESQUERDA))
			sorted(franja)
			caminho.append(franja[0])
			return franja.pop(0)[1]
		elif setor_borda(setores) == 'oeste':
			#cima, baixo esquerda
			if posy-1 >= 0 and kameHouse(casaKamex, casaKamey, posx, posy-1): franja.append((pesoTerreno(mapa,posx, posy-1), CIMA))
			if posy+1 <= len(mapa) and kameHouse(casaKamex, casaKamey, posx, posy+1): franja.append((pesoTerreno(mapa, posx,posy+1), BAIXO))
			if posx-1 >= 0 and kameHouse(casaKamex, casaKamey, posx-1, posy): franja.append((pesoTerreno(mapa, posx-1, posy), ESQUERDA))
			sorted(franja)
			caminho.append(franja[0])
			return franja.pop(0)[1]
		elif setor_borda(setores) == 'noroeste':
			#cima, baixo esquerda
			if posy-1 >= 0 and kameHouse(casaKamex, casaKamey, posx, posy-1): franja.append((pesoTerreno(mapa,posx, posy-1), CIMA))
			if posy+1 <= len(mapa) and kameHouse(casaKamex, casaKamey, posx, posy+1): franja.append((pesoTerreno(mapa, posx,posy+1), BAIXO))
			if posx-1 >= 0 and kameHouse(casaKamex, casaKamey, posx-1, posy): franja.append((pesoTerreno(mapa, posx-1, posy), ESQUERDA))
			sorted(franja)
			caminho.append(franja[0])
			return franja.pop(0)[1]

def joao_pascal_albuquerque(info):
	casaKame = info['casa-kame']
	casaKamex = casaKame[0]
	casaKamey = casaKame[1]
	mapa = info['mapa']
	if info['radar-proximo'] != []:
		radar_prox = info['radar-proximo']
	else:
		radar_prox = None

	posx = info['pos'][0]
	posy = info['pos'][1]

	if radar_prox == None:
		while info['esferas'] > 0:
			andar(posx, posy, mapa, casaKamex, casaKamey, franja, caminho, info['radar-direcao'], radar_prox,info)
		if info['esferas'] == 0:
			pegarEsfera(posx, posy, (casaKamex, casaKamey))
	else:
		pegarEsfera(posx, posy, mapa, radar_prox[0])

	posx = info['pos'][0]
	posy = info['pos'][1]
	if radar_prox is None:
		if info['esferas'] != 0:
			setorBorda = setor_borda(info['radar-direcao'])
			if setorBorda == 'norte': return cimaEsquerdaDireita(posx, posy, mapa, casaKamex, casaKamey, franja, caminho)
			# cima, esquerda e direita
			if setorBorda == 'oeste' or setorBorda == 'suldoeste' or setorBorda == 'noroeste': return cimaBaixoEsquerda(posx, posy, mapa, casaKamex, casaKamey, franja, caminho)
				#cima, baixo e esquerda	
			if setorBorda == 'sul': return baixoDireitaEsquerda(posx, posy, mapa, casaKamex, casaKamey, franja, caminho)
				#baixo esquerda direita
			if setorBorda == 'leste' or setorBorda == 'suldeste' or setorBorda == 'nordeste': return direitaBaixoCima(posx, posy, mapa, casaKamex, casaKamey, franja, caminho)
				#direita, baixo, cima
				
		elif info['esferas'] == 0:
			#direita baixo cima
			if posx < casaKamex: return direitaBaixoCima(posx, posy, mapa, casaKamex, casaKamey, franja, caminho)
			if posx > casaKamex: return cimaBaixoEsquerda(posx, posy, mapa, casaKamex, casaKamey, franja, caminho)
				#esquerda baixo cima
			if posy < casaKamey: return baixoDireitaEsquerda(posx, posy, mapa, casaKamex, casaKamey, franja, caminho)
				#esquerda baixo direita
			if posy > casaKamey: return cimaEsquerdaDireita(posx, posy, mapa, casaKamex, casaKamey, franja, caminho)
				#esquerda cima direita
	else:
		aux = radar_prox[0]
		esferax = aux[0]
		esferay = aux[1]
		if posx < esferax: return pegarEsfera(posx, posy, mapa, aux)
			#direita baixo cima
		if posx > esferax: return pegarEsfera(posx, posy, mapa, aux)
			#esquerda cima baixo
		if posy < esferay: return pegarEsfera(posx, posy, mapa, aux)
			#esquerda baixo direita
		if posy > esferay: return pegarEsfera(posx, posy, mapa, aux)
			#esquerda cima direita

if __name__ == "__main__":
	dbz = DragonBallZ(joao_pascal_albuquerque,tamanho = 10,semente =2)
	executar_jogo(dbz) 