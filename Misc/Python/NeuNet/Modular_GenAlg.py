import numpy as np
from copy import deepcopy

class GenAlg(object):
	def __init__(self):
		# Stuff
		self.weightPopu = []

	def permProb(self, fitness, fitnessMin, fitnessMax):
		return 1 - np.sqrt((fitness - fitnessMin) / (fitnessMax - fitnessMin)) if fitnessMax != fitnessMin else 1

	# Takes in a "generation", returns the succeeding one
	def CoSyNE(self, NNgroup):
		# This will be called once the NNgroup has been tested
		# NNgroup.sort(key=lambda x: x.fitness, reverse=True)

		# Create the population / group of subpopulations, one for each synaptic weight
		self.weightPopu = []
		self.fitnesses = []
		for x in NNgroup:
			self.weightPopu.append(x.getParams())
			self.fitnesses.append(x.fitness)
		self.weightPopu = np.array(self.weightPopu)
		self.neunetPopu = self.weightPopu # Each subarray is a NeuNet param
		self.weightPopu = self.weightPopu.T # Each subarray is a subpopulation
		# print "Old neunet popu First:\n", self.neunetPopu[0]

		# Create the self.offspring
		quarter = len(self.neunetPopu) / 4
		self.offspring = deepcopy(self.neunetPopu[0:quarter])
		# Magic numbers
		self.crossoverRate = 0.30
		self.mutationRate = 0.10
		# print "Before\n", self.offspring
		for x in range(0, quarter):
			for y in range(0, len(self.offspring[0])):
				randnum = np.random.random(2)
				if(randnum[0] < self.crossoverRate):
#					print "Crossover", x, y
					randnum[1] = 1
					swp = self.offspring[x][y]
					self.offspring[x][y] = self.offspring[x-1][y]
					self.offspring[x-1][y] = swp
				if(randnum[1] < self.mutationRate):
#					print "Mutation", x, y
					self.offspring[x][y] = np.random.randn()
#		print "After\n", self.offspring

		# Swap the weak ones
		for x in range(-1, -(quarter+1), -1):
			self.neunetPopu[x] = list(self.offspring[-(x+1)])

		# Permutate
#		print "Before perms\n", self.weightPopu
		populength = len(self.weightPopu)
		subpopulength = len(self.weightPopu[0])
		for x in range(0, populength):
			perm = []
			subpopulength = len(self.weightPopu[x])
			for y in range(0, subpopulength):
				if np.random.random() >= self.permProb(self.fitnesses[y], self.fitnesses[0], self.fitnesses[subpopulength-1]):
					perm.append(y)
#			print "perm: ", perm
			if perm:
				tmp = self.weightPopu[x][perm[0]]
				for z in range(0, len(perm)-1):
					self.weightPopu[x][perm[z]] = self.weightPopu[x][perm[z+1]]
				self.weightPopu[x][perm[-1]] = tmp
		# print "After perms\n", self.weightPopu

		# print "Final neunetPopu First: \n", self.neunetPopu[0]
		# To be checked, idk how
		return self.neunetPopu
