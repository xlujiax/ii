import pygame
import math
import pygame.locals
import sys

screen_size = (640, 480)

def init_game():
    global player_pos
    player_pos = (0,0)
    prepare_background()

def onmousemove(pos):
    global player_pos
    player_pos = pos

def draw_circle(pos):
    size = 5 + 20 * pos[0] / screen_size[0]

    brightness = float(pos[0] + pos[1]) / float(screen.get_width() + screen.get_height())
    color = (0, 200 * (1 - brightness), 200 * (1 - brightness))
    pygame.draw.circle(screen, color, pos, int(size))

def frame():

def init_pygame():
    pygame.init()
    global screen
    screen = pygame.display.set_mode(screen_size)

def loop():
    global screen
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
            elif event.type == pygame.MOUSEMOTION:
                onmousemove(event.pos)
            frame()

init_pygame()
init_game()
loop()
