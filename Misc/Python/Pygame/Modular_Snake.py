import pygame
from copy import deepcopy
import Queue as q
import time
import random
import math

pygame.init()

# Colors
black = (63,63,63)
white = (190,190,190)
red = (255, 127, 127)
green = (31, 127, 31)
blue = (127, 127, 255)
bound = [0,39]

#Constants
windx = 600
windy = 600
box = 15
diagonal = 53.74011537017761

class Food(object):
	def __init__(self, snake):
		self.coords = snake.head
		while self.coords in snake.snake:
			self.xc = math.floor(random.random() * 38)+1
			self.yc = math.floor(random.random() * 38)+1
			self.coords = [int(self.xc), int(self.yc)]
		self.score = 50
		self.isEaten = False
		# print self.coords

class Snake(object):
	def __init__(self, snake = None):
		if snake is None:
			self.snake = []
			self.head = [19,11]
			self.snake.append(deepcopy(self.head))
			#print self.head
			for x in range(7):
				self.head[1] += 1
				self.snake.append(deepcopy(self.head))
				#print self.head
			self.head = self.snake[7]
			self.tail = self.snake[0]
		else:
			self.snake = snake
			self.head = snake[7]
			self.tail = snake[0]
		self.direction = pygame.K_DOWN
		self.score = 0
		self.size = 8
		self.hunger = 0
		self.distance = diagonal
		self.foodEaten = 0
		self.pedometer = 0

	def distFromFood(self, food):
		self.distance = math.sqrt(math.pow(self.head[0] - float(food.coords[0]), 2) + math.pow(self.head[1] - float(food.coords[1]), 2))
		return self.distance

	def isSnakeHeadCrash(self):
		return (self.head[0] in bound or self.head[1] in bound)

	def isSnakeSelfCollide(self):
		# print self.snake.count(deepcopy(self.head))
		return (self.snake.count(deepcopy(self.head)) > 1)

	def eatsFood(self, food):
		if (self.head == food.coords):
			self.score += food.score
			self.size += 1
			self.hunger -= food.score
			self.foodEaten += 1
		else:
			self.hunger += 1
		return self.head == food.coords

	def updateSnake(self, food, direction = None):
		'''
		# Check if a direction was given
		if direction is not None:
			# Check if direction is valid
			if not ((direction * self.direction) in (75900, 74802)):
				self.direction = direction
			print (self.direction * direction)
		'''
		# In hindsight, a self.tail isn't that necessary
		if(not self.eatsFood(food)):
			self.tail = deepcopy(self.snake.pop(0))
		else:
			food.isEaten = True
			# print self.size
		tmp = deepcopy(self.snake[self.size - 2])
		if self.direction == pygame.K_LEFT:
			tmp[0] -= -39 if tmp[0] == 0 else 1
		elif self.direction == pygame.K_RIGHT:
			tmp[0] += -39 if tmp[0] == 39 else 1
		elif self.direction == pygame.K_UP:
			tmp[1] -= -39 if tmp[1] == 0 else 1
		#elif self.direction == pygame.K_DOWN:
		else:
			tmp[1] += -39 if tmp[1] == 39 else 1
		self.snake.append(tmp)
		self.head = self.snake[self.size - 1]
		# print self.head

class Board(object):
	def __init__(self, snake, matrix = None):
		if matrix is None:
			# Create one from scratch
			self.matrix = []
			for x in range(40):
				boardRow = []
				for y in range(40):
					#insert border
					if(x in bound or y in bound):
						boardRow.append(-1)
					else:
						boardRow.append(0)
				self.matrix.append(boardRow)
		else:
			self.matrix = matrix
		self.genFood(snake)

	def genFood(self, snake):
		self.food = Food(snake)

	def drawBoard(self, gameDisplay, snake):
		## Update food
		if self.food.isEaten:
			self.food = Food(snake)
		blockColor = tuple()
		self.drawSnake(snake)
		self.matrix[self.food.coords[1]][self.food.coords[0]] = 2
		for x in range(40):
			for y in range(40):
				if self.matrix[y][x] == -1:
					blockColor = black
				if self.matrix[y][x] == 0:
					blockColor = white
				if self.matrix[y][x] == 1:
					blockColor = green
				if self.matrix[y][x] == 2:
					blockColor = red
				# if [x, y] in snake.snake:
					# blockColor = green
				# if [x, y] == self.food.coords:
					# blockColor = red
				gameDisplay.fill(blockColor, rect=[x*box, y*box, box, box])

	def drawSnake(self, snake):
		self.matrix[snake.tail[1]][snake.tail[0]] = 0
		for x in snake.snake:
			self.matrix[x[1]][x[0]] = 1

'''
gameDisplay = pygame.display.set_mode((windx, windy))
# pygame.display.update()

gameLoop = 300
board = Board()
snake = Snake()
# print board.matrix
print snake.snake

while gameLoop > 0:
	## Check for events
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			gameLoop = 0

		if event.type == pygame.KEYDOWN:
			board.matrix[snake.head[0]][snake.head[1]] = 0
			if event.key == pygame.K_LEFT:
				# snake.head[0] -= -37 if snake.head[1] == 1 else 1
				snake.updateSnake(event.key)
			elif event.key == pygame.K_RIGHT:
				snake.head[0] += -37 if snake.head[1] == 38 else 1
			elif event.key == pygame.K_UP:
				snake.head[1] -= -37 if snake.head[0] == 1 else 1
			elif event.key == pygame.K_DOWN:
				snake.head[1] += -37 if snake.head[0] == 38 else 1
			# Check if direction is valid
			if (snake.direction * event.key) not in (75900, 74802):
				snake.direction = event.key
			# Check if out of bounds
			print snake.snake

	## Update the snake and board
	snake.updateSnake()
	## Check for conditions
	if(snake.isSnakeHeadCrash()):
		print "Game Over"
		print "Score: ", snake.score
		gameLoop = 0
	## Update graphics
	board.drawBoard(gameDisplay, snake)
	# board.drawText(gameLoop, 50, 50)
	pygame.display.update()
	snake.score += 1
	gameLoop -= 1
	time.sleep(0.05)

pygame.quit()
quit()
'''
