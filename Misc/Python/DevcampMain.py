import sys
sys.path.append('~/Documents/CS_Files/Misc/Python/NeuNet/')
sys.path.append('~/Documents/CS_Files/Misc/Python/Pygame/')

import Modular_NN as neunet
import Modular_GenAlg as genalg
import Game
import math, random
import pygame
import numpy as np
from copy import deepcopy

## Constants (lol)
GENS = 100
POPU = 12
RNDS = 3
DIAGONAL = 53.74011537017761
ga = genalg.GenAlg()
roundFitnesses = []

## For now, play a single neural network
NN = []
for x in range(POPU):
	NN.append(neunet.Neural_Network(6, 1, [5], 4))

for y in range(GENS):
	print "~~~GEN", y, "~~~"
	for x in range(POPU):
		print "\nBrain: ", x+1
		for z in range(RNDS):
			game = Game.Game()
			while game.gameLoop:
				Xsize = game.snake.size
				Xsize = np.array(Xsize, dtype=float)
				# Xhead = game.snake.head
				# Xhead = np.array(Xhead, dtype=float)
				# Xdir = game.snake.direction
				# Xdir = np.array(Xdir, dtype=float)
				# Xfood = game.board.food.coords
				# Xfood = np.array(Xfood, dtype=float)
				Xdist = game.snake.distance
				Xup = game.board.matrix[game.snake.head[1] - 1][game.snake.head[0]]
				Xdown = game.board.matrix[game.snake.head[1] + 1][game.snake.head[0]]
				Xleft = game.board.matrix[game.snake.head[1]][game.snake.head[0] - 1]
				Xright = game.board.matrix[game.snake.head[1]][game.snake.head[0] + 1]
				Xsight = np.array([Xup, Xdown, Xleft, Xright], dtype=float)
				# print Xsight

				# print "Init: "
				# print Xsize
				# print Xhead
				# print Xdir
				# print Xfood
	
				# Standardize
				Xsize = Xsize / 1444
				# Xhead = Xhead / 40
				# Xdir = (Xdir - 273) / 4
				# Xfood = Xfood / 40
				Xdist = Xdist / DIAGONAL
				Xsight = np.add(Xsight, 1) / 3

				# Concatenate
				X = [Xsize]
				# X = np.concatenate((X, Xhead))
				# X = np.concatenate((X, [Xdir]))
				# X = np.concatenate((X, Xfood))
				X = np.concatenate((X, [Xdist]))
				X = np.concatenate((X, Xsight))
				# print X
	
				# Run the NN
				output = np.argmax(NN[x].forward(X))
				# print NN[x].Yh
				# nextDir = None
				# print "Output: ", output
				
				# Try lang
				# output = math.ceil(output * 100) % 4
	
				nextDir = pygame.event.Event(pygame.KEYDOWN, {'key': output + 273})
				'''
				if 0.5 <= output < 0.55:
					nextDir = pygame.event.Event(pygame.KEYDOWN, {'key': pygame.K_LEFT})
				elif 0.55 <= output < 0.6:
					nextDir = pygame.event.Event(pygame.KEYDOWN, {'key': pygame.K_RIGHT})
				elif 0.6 <= output < 0.65:
					nextDir = pygame.event.Event(pygame.KEYDOWN, {'key': pygame.K_UP})
				elif 0.65 <= output < 0.7:
					nextDir = pygame.event.Event(pygame.KEYDOWN, {'key': pygame.K_DOWN})
				'''
				game.step([nextDir]) if (nextDir != None) else game.step()
				# print game.snakeDist
				# print game.gameLoop
			# roundFitnesses.append(game.snake.score + (DIAGONAL - game.snakeDist))
			# tmp = [game.snake.pedometer, game.board.food.score * game.snake.foodEaten, (DIAGONAL - game.snakeDist) * (game.snake.foodEaten + 1)]
			# print tmp
			roundFitnesses.append(game.snake.score + game.snakeDist)
		# print "Score: ", game.snake.score, "\n"
		print roundFitnesses
		NN[x].setFitness(sum(roundFitnesses) / len(roundFitnesses))
		roundFitnesses = []
	# GenAlg
	NN.sort(key=lambda x: x.fitness, reverse=True)
	neunetPopu = ga.CoSyNE(NN)
	for n in range(POPU):
		NN[n].setParams(neunetPopu[n])
