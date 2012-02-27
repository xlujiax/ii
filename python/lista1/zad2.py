import pygame
import math
from pygame.locals import *
from sys import exit

screen_size = (640, 480)

def init_game():
    global player_pos
    player_pos = (0,0)
    prepare_background()

def onmousemove(pos):
    global player_pos
    player_pos = pos

def draw_circle(pos):
    pygame.draw.circle(screen, (255, 0, 0), pos, 10)

def prepare_background():
    global background
    background = pygame.Surface(screen_size)
    draw_gradient(background)

def draw_background(screen):
    global background
    screen.blit(background, (0,0))

def draw_gradient(screen):
    for x in range(0, screen.get_width() - 1):
        for y in range(0, screen.get_height() - 1):
            center = (100, 100)
            brightness = float(x + y) / float(screen.get_width() + screen.get_height())
            color = (100 * brightness, 200 * brightness, 20 * brightness)
            screen.set_at((x, y), color)

def draw():
    global screen
    draw_background(screen)
    draw_circle(player_pos)

def frame():
    global screen
    screen.fill( (255,255,255) )
    draw()
    pygame.display.update()

def init_pygame():
    pygame.init()
    global screen
    screen = pygame.display.set_mode(screen_size)

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
