import math, random
import numpy as np
import Modular_GenAlg as genalg

# TO FINISH: Trainer
class Neuron(object):
	def __init__(self):
		self.inputWeights = []

	def __init__(self, inputN):
		self.inputWeights = np.random.randn(inputN)

class Neuron_Layer(object):
	def __init__(self):
		self.neurons = []
		self.weights = []
		self.inputLayerSize = 0
		self.currentLayerSize = 0

	def __init__(self, size, prevLayerSize):
		self.neurons = []
		self.weights = []
		for x in range(0, size):
			#print "New Neuron"
			self.neurons.append(Neuron(prevLayerSize))
		for y in range(0, prevLayerSize):
			tmp = []
			for x in self.neurons:
				tmp.append(x.inputWeights[y])
			self.weights.append(tmp)
		self.weights = np.array(self.weights)
		self.inputLayerSize = prevLayerSize
		self.currentLayerSize = size

class Neural_Network(object):
	def sigmoid(self, x):
		return 1/(1+np.exp(-x))

	def dsigmoid(self, x):
		return np.exp(-x)/((1+np.exp(-x))**2)

	# Based on a redefinition of sigmoid prime. Not 100% sure if totally correct
	def dsigmoid_new(self, ndx):
		return self.An[ndx] * (np.subtract(np.ones(self.An[ndx].shape), self.An[ndx]))

	def cost(self, Y):
		return 0.5*np.sum((Y-self.Yh)**2)

	# Based on a redefinition of sigmoid prime. Not 100% sure if totally correct
	def dcost_new(self, X, Y):
		bperr = []
		dJdW = []
		bpctr = 0
		bperr.append(np.multiply(-(Y-self.Yh), self.dsigmoid_new(-1)))
		dJdW.append(np.dot(self.An[-2].T, bperr[0]))
		for c in range(self.layerCount-1, 1, -1):
			bperr.append(np.dot(bperr[bpctr], self.layers[c].weights.T) * self.dsigmoid_new(c))
			dJdW.append(np.dot(self.An[c-2].T, bperr[bpctr+1]))
			bpctr += 1
		bperr.append(np.dot(bperr[bpctr], self.layers[1].weights.T) * self.dsigmoid_new(0))
		dJdW.append(np.dot(X.T, bperr[bpctr+1]))
		dJdW.reverse()
		return dJdW

	def dcost(self, X, Y):
		# self.Yh = self.forward(X)
		bperr = []
		dJdW = []
		bpctr = 0
		bperr.append(np.multiply(-(Y-self.Yh), self.dsigmoid(self.Zn[-1])))
		dJdW.append(np.dot(self.An[-2].T, bperr[0]))
		'''
		print "BPErr\n", bperr[bpctr]
		print "dJdW\n", dJdW[bpctr]
		'''
		for c in range(self.layerCount-1, 1, -1):
			bperr.append(np.dot(bperr[bpctr], self.layers[c].weights.T) * self.dsigmoid(self.Zn[c]))
			dJdW.append(np.dot(self.An[c-2].T, bperr[bpctr+1]))
			bpctr += 1
			'''
			print "BPErr\n", bperr[bpctr]
			print "AnT\n", self.An[c-1].T
			print "dJdW\n", dJdW[bpctr]
			'''
		bperr.append(np.dot(bperr[bpctr], self.layers[1].weights.T) * self.dsigmoid(self.Zn[0]))
		dJdW.append(np.dot(X.T, bperr[bpctr+1]))
		'''
		print "BPErr\n", bperr[bpctr+1]
		print "dJdW\n", dJdW[bpctr+1]
		'''
		dJdW.reverse()
		return dJdW

	def forward(self, X):
		self.Zn = [] #Array of dot product matrices
		self.An = [] #Array of activated matrices
		self.Zn.append(np.dot(X, self.layers[0].weights))
		self.An.append(self.sigmoid(self.Zn[0]))
		for c in range(1, self.layerCount):
			self.Zn.append(np.dot(self.An[c-1], self.layers[c].weights))
			self.An.append(self.sigmoid(self.Zn[c]))
		self.Yh = self.An[-1]
		return self.Yh

	# Where the neunet does its stuff
	def setFitness(self, value):
		self.fitness = value

	def fitnessFunc(self, Y):
		self.fitness = -(np.sum(np.abs(Y-self.Yh.ravel())))
		return self.fitness

	def getParams(self):
		params = self.layers[0].weights.ravel()
		for x in range(1, len(self.layers)):
			params = np.concatenate((params, self.layers[x].weights.ravel()))
		return params

	def setParams(self, params):
		weightStart = 0;
		weightEnd = 0
		for x in self.layers:
			weightStart = weightEnd
			weightEnd += x.inputLayerSize * x.currentLayerSize
			x.weights = np.reshape(params[weightStart:weightEnd], (x.inputLayerSize, x.currentLayerSize))

	def computeGradients(self, X, Y):
		dJdW = self.dcost(X, Y)
		output = dJdW[0].ravel()
		for x in range(1, len(dJdW)):
			output = np.concatenate((output, dJdW[x].ravel()))
		return output
	'''
	def train(self, X, Y):
		ctr = 0
		sc = 10
		print "~~START~~"
		while (ctr < 500 or self.cost(Y) > 0.00001):
			self.forward(X)
			print self.cost(Y)
			JW = self.dcost(X, Y)
			for x in range(0, len(JW)):
				self.layers[x].weights -= sc*JW[x]
			ctr += 1
	'''
	def __init__(self, inputLayerSize, hiddenLayers, hiddenLayerSizes, outputLayerSize):
		self.inputLayerSize = inputLayerSize
		self.outputLayerSize = outputLayerSize
		self.hiddenLayerSizes = hiddenLayerSizes
		self.layerCount = hiddenLayers + 1 #Not counting input layer

		# Add the layers
		self.layers = []
		self.layers.append(Neuron_Layer(hiddenLayerSizes[0], inputLayerSize))
		for x in range(1, hiddenLayers):
			self.layers.append(Neuron_Layer(hiddenLayerSizes[x], hiddenLayerSizes[x-1]))
		self.layers.append(Neuron_Layer(outputLayerSize, hiddenLayerSizes[hiddenLayers-1]))

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

'''
NN = Neural_Network(2, 2, [3, 2], 1)
print "NN"
for y in NN.layers:
	print y.weights, "\n"

X = np.array(([3,5],[5,1],[10,2]), dtype=float)
Y = np.array(([0.75],[0.82],[0.93]), dtype=float)
X = X/np.amax(X, axis=0)
print "Input: \n", X
print "Output: \n", Y
print "Estimate: \n", NN.forward(X)
for x in NN.Zn:
	print "Zn\n", x
for x in NN.An:
	print "An\n", x
print "Cost: \n", NN.cost(Y)
dJdW = NN.dcost(X, Y)
for x in dJdW:
	print "DCost_old\n", x
print "\n"

grad = NN.computeGradients(X, Y)
print "Gradients\n", grad

# ~~Weights~~
print "Weights: Indiv\n"
for x in NN.layers:
	print x.weights, "\n"
print "Weights: params\n"
params = NN.getParams()
print params

# ~~Fitness~~
print "Fitness:\n"
print NN.fitnessFunc()

NN.train(X, Y)
print "Final Estimate: \n", NN.forward(X)
print "Final Cost: \n", NN.cost(Y)

X = np.array(([3,5]), dtype=float)
X = X/np.amax(X, axis=0)
# Genetic Algorithm
NNlist = []
print "Each one's params\n"
for x in range(0,10):
	NNlist.append(Neural_Network(2, 1, [3], 1))
	NNlist[x].forward(X)
	print NNlist[x].getParams(), ", fitness: ", NNlist[x].fitnessFunc(), "\n"

ga = genalg.GenAlg()
ga.CoSyNE(NNlist)

'''
