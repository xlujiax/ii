"Maciej Pacut, Z1, L2"
import pygame
import math
import pygame.locals
import sys

screen_size = (640, 480)

bg = pygame.image.load("bg.jpg")

def init_pygame():
    pygame.init()
    global screen
    screen = pygame.display.set_mode(screen_size)

def frame():
    screen.blit(bg, (0, 0))
    pygame.display.update()

def onmousemove(pos):
    print pos

def loop():
    global screen
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit(0)
            elif event.type == pygame.MOUSEMOTION:
                onmousemove(event.pos)
            frame()

init_pygame()
loop()
