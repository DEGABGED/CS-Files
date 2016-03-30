import pygame
import Game

game = Game.Game()
while game.gameLoop:
	game.step(pygame.event.get())
