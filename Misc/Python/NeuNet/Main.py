import Modular_NN as neunet
import Modular_GenAlg as genalg
import math, random
import numpy as np
from copy import deepcopy

# Train NeuNets to multiply?
# Generate Training and Testing sets
X = np.random.randn(5,20)
Y = []
for x in X:
	Y.append(x[0] * x[1])
Y = np.array(Y)

Xtest = np.random.randn(5,20)
Ytest = []
for x in Xtest:
	Ytest.append(x[0] * x[1])
Ytest = np.array(Ytest)
ch = "y"
fitnesses = []
aveFitness = 0
genCount = 0
beforeTopNet = []
NNlist = []
for x in range(5):
	NNlist.append(neunet.Neural_Network(20, 1, [5], 1))

#while(ch == "y"):
for c in range(1):
	print c
	aveFitness = 0
	fitnesses = []
	# Loop for training?
	for x in range(5):
		NNlist[x].forward(X)
		NNlist[x].fitnessFunc(Y)
		# print "fitness: ", NNlist[x].fitnessFunc(Y), "\n"

	genCount += 1
	NNlist.sort(key=lambda x: x.fitness, reverse=True)
	beforeTopNet = []
	beforeTopNet = deepcopy(NNlist[0].getParams())

	if(c >= 100):
		print "Berak"
		break
	# Loop for GenAlg?
	ga = genalg.GenAlg()
	neunetPopu = ga.CoSyNE(NNlist)
	for x in range(5):
		NNlist[x].setParams(neunetPopu[x])
		fitnesses.append(NNlist[x].fitness)
		aveFitness += NNlist[x].fitness
		# print "	Answer: ", NNlist[x].Yh[0]
	if c==0:
		print "Before GenAlg:"
		print fitnesses
	aveFitness /= 5
	'''
	print "Before GenAlg top net: ", beforeTopNet
	print "Aftere GenAlg top net: ", NNlist[0].getParams()
	print "Gen: ", genCount, ", AveFit: ", aveFitness
	print "Prev. Top Fitnesses: ", fitnesses[0:5]
	ch = raw_input("Continue?")
	'''

print "After: ", fitnesses
for nn in NNlist:
	print "Training Data"
	nn.forward(X)
	print nn.fitnessFunc(Y)
	#print "Y\n", Y
	#print "Yh\n", nn.Yh
	print "Testing Data"
	nn.forward(Xtest)
	print nn.fitnessFunc(Ytest)
print "Y\n", Y
NNlist[0].forward(X)
print "Yh\n", NNlist[0].Yh
