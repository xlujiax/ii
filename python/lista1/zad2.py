import pygame
import math
from pygame.locals import *
from sys import exit

def init_game():
    global player_pos
    player_pos = (0,0)

def onmousemove(pos):
    global player_pos
    player_pos = pos

def draw_circle(pos):
    pygame.draw.circle(screen, (255, 0, 0), pos, 10)

def draw():
    print player_pos
    draw_circle(player_pos)

def frame():
    global screen
    screen.fill( (255,255,255) )
    draw()
    pygame.display.update()

def init_pygame():
    pygame.init()
    global screen
    screen = pygame.display.set_mode( (640,480) )

def loop():
    global screen
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
            elif event.type == MOUSEMOTION:
                onmousemove(event.pos)
            frame()

init_pygame()
init_game()
loop()
