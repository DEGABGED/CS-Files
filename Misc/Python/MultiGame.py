import Modular_Snake as modsnake
import pygame
from pygame import font
import time

class MultiGame(object):
	def __init__(self, num):
		# print "game init"
		self.gameDisplay = pygame.display.set_mode((modsnake.windx, modsnake.windy))
		# pygame.display.update()

		self.gameLoopA = []
		self.snakeA = []
		self.boardA = []
		self.snakeDistA = []
		for x in range(num):
			self.gameLoopA.append(True)
			self.snakeA.append(modsnake.Snake())
			self.boardA.append(modsnake.Board(self.snakeA[x]))
			self.snakeDistA.append(self.snakeA[x].distance)
		'''
		self.gameLoop = True
		self.snake = modsnake.Snake()
		self.board = modsnake.Board(self.snake)
		self.snakeDist = self.snake.distance
		'''
		# print board.matrix
		# print self.snake.snake
		# self.screenFont = pygame.font.SysFont("monospace", 15)

	def genFood(self):
		self.food = modsnake.Food()
		for x in self.boardA:
			x.food = self.food

	def step(self, ndx, event = None):
		## Insert code for moving the game step by step here
		# print event
		if event:
			if event[0].type == pygame.QUIT:
				self.quit()
			elif event[0].type == pygame.KEYDOWN:
				'''
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
				'''
				# Check if direction is valid
				if (self.snake.direction * event[0].key) not in (75900, 74802):
					self.snake.direction = event[0].key
				# Check if out of bounds
				# print self.snake.snake

		## Update the self.snake and board
		self.snakeA[ndx].updateSnake(self.board.food)

		## Check for conditions (Crash, food, etc.)
		if(self.snake.isSnakeHeadCrash() or self.snake.isSnakeSelfCollide() or self.snake.hunger > 100):
			print "Game Over"
			print "Cause: ", "Hunger" if self.snake.hunger > 100 else "Collision"
			# Set final score
			print "Score: ", self.snake.score
			#self.snake.score -= int(self.snake.hunger / 2)
			#print "Score After: ", self.snake.score
			#print "Dist: ", self.snakeDist
			self.quit()
		'''
		else:
			if(self.snake.eatsFood(board.food)):
				print "Eat"
				self.snake.score += board.food.score
				board.food.isEaten = True
		'''
		## Update graphics
		if self.gameLoop:
			self.board.drawBoard(self.gameDisplay, self.snake)
			# scoreText = self.screenFont.render("Score: " + str(self.snake.score), 5, (63,63,63))
			# self.gameDisplay.blit(scoreText, (25,25))
			pygame.display.update()
			self.snake.score += 1
			self.snake.pedometer += 1
			self.snakeDist = self.snake.distFromFood(self.board.food)
			time.sleep(0.015)
