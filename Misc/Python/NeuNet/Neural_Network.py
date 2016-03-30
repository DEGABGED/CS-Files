import math, random
import numpy as np

class Neural_Network(object):
	def sigmoid(self, x):
		return 1/(1+np.exp(-x))

	def dsigmoid(self, x):
		return np.exp(-x)/((1+np.exp(-x))**2)

	def cost(self, Y):
		return 0.5*sum((Y-self.Yh)**2)

	def dcost(self, X, Y):
		# self.Yh = self.forward(X)
		bperr3 = np.multiply(-(Y-self.Yh), self.dsigmoid(self.Z3))
		dJdW2 = np.dot(self.A2.T, bperr3)
		bperr2 = np.dot(bperr3, self.W2.T)*self.dsigmoid(self.Z2)
		dJdW1 = np.dot(X.T, bperr2)
		return dJdW1, dJdW2

	def forward(self, X):
		self.Z2 = np.dot(X, self.W1)
		self.A2 = self.sigmoid(self.Z2)
		self.Z3 = np.dot(self.A2, self.W2)
		self.Yh = self.sigmoid(self.Z3)
		return self.Yh

	# Violently plagiarized code for numerical gradient checking
	#Helper Functions for interacting with other classes:
	def getParams(self):
		#Get W1 and W2 unrolled into vector:
		params = np.concatenate((self.W1.ravel(), self.W2.ravel()))
		return params

	def setParams(self, params):
		#Set W1 and W2 using single paramater vector.
		W1_start = 0
		W1_end = self.hiddenLayerSize * self.inputLayerSize
		self.W1 = np.reshape(params[W1_start:W1_end], (self.inputLayerSize , self.hiddenLayerSize))
		W2_end = W1_end + self.hiddenLayerSize*self.outputLayerSize
		self.W2 = np.reshape(params[W1_end:W2_end], (self.hiddenLayerSize, self.outputLayerSize))

	def computeGradients(self, X, Y):
		dJdW1, dJdW2 = self.dcost(X, Y)
		return np.concatenate((dJdW1.ravel(), dJdW2.ravel()))

	def train(self, X, Y):
		ctr = 0
		sc = 10
		print "~~START~~"
		while ctr < 500 or self.cost(Y)[0] > 0.00001:
			self.forward(X)
			#print self.cost(Y)
			JW1, JW2 = self.dcost(X, Y)
			self.W1 -= sc*JW1
			self.W2 -= sc*JW2
			ctr += 1

	def __init__(self):
		# Copied code lol gdi
		self.inputLayerSize = 2
		self.outputLayerSize = 1
		self.hiddenLayerSize = 3
		self.W1 = np.random.randn(self.inputLayerSize, self.hiddenLayerSize)
		self.W2 = np.random.randn(self.hiddenLayerSize, self.outputLayerSize)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def computeNumericalGradient(N, X, Y):
	paramsInitial = N.getParams()
	numgrad = np.zeros(paramsInitial.shape)
	perturb = np.zeros(paramsInitial.shape)
	e = 1e-4

	for p in range(len(paramsInitial)):
		#Set perturbation vector
		perturb[p] = e
		N.setParams(paramsInitial + perturb)
		NN.forward(X)
		loss2 = N.cost(Y)

		N.setParams(paramsInitial - perturb)
		NN.forward(X)
		loss1 = N.cost(Y)

		#Compute Numerical Gradient
		numgrad[p] = (loss2 - loss1) / (2*e)

		#Return the value we changed to zero:
		perturb[p] = 0

	#Return Params to original value:
	N.setParams(paramsInitial)
	return numgrad

NN = Neural_Network()
print "First weights: \n", NN.W1
print "Second weights: \n", NN.W2
X = np.array(([3,5],[5,1],[10,2]), dtype=float)
Y = np.array(([0.75],[0.82],[0.93]), dtype=float)
X = X/np.amax(X, axis=0)

print "Input: \n", X
print "Output: \n", NN.forward(X)
print "Cost: \n", NN.cost(Y)

JW1, JW2 = NN.dcost(X, Y)
print "JW1, JW2: \n", JW1, "\n", JW2

grad = NN.computeGradients(X, Y)
print "Gradients\n", grad

'''
grad = np.concatenate((JW1.ravel(), JW2.ravel()))
numgrad = computeNumericalGradient(NN, X, Y)
print "Grad\n", grad
print "Numgrad\n", numgrad
print np.linalg.norm(grad-numgrad)/np.linalg.norm(grad+numgrad)

NN.train(X, Y)
print "Final Output: \n", NN.forward(X)
print "Final Cost: \n", NN.cost(Y)
'''
