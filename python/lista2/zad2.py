import pygame
import math
from pygame.locals import *
from sys import exit

screenx = 640
screeny = 480

pygame.init()
ekran = pygame.display.set_mode( (screenx, screeny) )

x = 100
y = 100
sizex = 128
sizey = 128

surfaces = {
    'no': [pygame.image.load(f) for f in ['horse.png']],
    'nw': [pygame.image.load(f) for f in ['walking nw0001.bmp', 'walking nw0002.bmp',
                                          'walking nw0003.bmp', 'walking nw0004.bmp',
                                          'walking nw0005.bmp', 'walking nw0006.bmp',
                                          'walking nw0007.bmp', 'walking nw0008.bmp',
                                          'walking nw0009.bmp', 'walking nw0010.bmp',
                                          'walking nw0011.bmp']],
    'sw': [pygame.image.load(f) for f in ['walking sw0001.bmp', 'walking sw0002.bmp',
                                          'walking sw0003.bmp', 'walking sw0004.bmp',
                                          'walking sw0005.bmp', 'walking sw0006.bmp',
                                          'walking sw0007.bmp', 'walking sw0008.bmp',
                                          'walking sw0009.bmp', 'walking sw0010.bmp',
                                          'walking sw0011.bmp']],
    'ne': [pygame.image.load(f) for f in ['walking ne0001.bmp', 'walking ne0002.bmp',
                                          'walking ne0003.bmp', 'walking ne0004.bmp',
                                          'walking ne0005.bmp', 'walking ne0006.bmp',
                                          'walking ne0007.bmp', 'walking ne0008.bmp',
                                          'walking ne0009.bmp', 'walking ne0010.bmp',
                                          'walking ne0011.bmp']],
    'se': [pygame.image.load(f) for f in ['walking se0001.bmp', 'walking se0002.bmp',
                                          'walking se0003.bmp', 'walking se0004.bmp',
                                          'walking se0005.bmp', 'walking se0006.bmp',
                                          'walking se0007.bmp', 'walking se0008.bmp',
                                          'walking se0009.bmp', 'walking se0010.bmp',
                                          'walking se0011.bmp']],
    's': [pygame.image.load(f) for f in ['walking s0001.bmp', 'walking s0002.bmp',
                                         'walking s0003.bmp', 'walking s0004.bmp',
                                         'walking s0005.bmp', 'walking s0006.bmp',
                                         'walking s0007.bmp', 'walking s0008.bmp',
                                         'walking s0009.bmp', 'walking s0010.bmp',
                                         'walking s0011.bmp']],
    'e': [pygame.image.load(f) for f in ['walking e0001.bmp', 'walking e0002.bmp',
                                         'walking e0003.bmp', 'walking e0004.bmp',
                                         'walking e0005.bmp', 'walking e0006.bmp',
                                         'walking e0007.bmp', 'walking e0008.bmp',
                                         'walking e0009.bmp', 'walking e0010.bmp',
                                         'walking e0011.bmp']],
    'n': [pygame.image.load(f) for f in ['walking n0001.bmp', 'walking n0002.bmp',
                                         'walking n0003.bmp', 'walking n0004.bmp',
                                         'walking n0005.bmp', 'walking n0006.bmp',
                                         'walking n0007.bmp', 'walking n0008.bmp',
                                         'walking n0009.bmp', 'walking n0010.bmp',
                                         'walking n0011.bmp']],
    'w': [pygame.image.load(f) for f in ['walking w0001.bmp', 'walking w0002.bmp',
                                         'walking w0003.bmp', 'walking w0004.bmp',
                                         'walking w0005.bmp', 'walking w0006.bmp',
                                         'walking w0007.bmp', 'walking w0008.bmp',
                                         'walking w0009.bmp', 'walking w0010.bmp',
                                         'walking w0011.bmp']],
    }

img_before = "no"
loop_counter = 0
frame = 0

while True:
    for zdarzenie in pygame.event.get():
        if zdarzenie.type == QUIT:
            pygame.quit()

    ekran.fill( (255,255,255) )

    key = pygame.key.get_pressed()

    img = "no"

    if key[pygame.K_LEFT] and key[pygame.K_UP]:
        img = "nw"
    elif key[pygame.K_LEFT] and key[pygame.K_DOWN]:
        img = "sw"
    elif key[pygame.K_RIGHT] and key[pygame.K_UP]:
        img = "ne"
    elif key[pygame.K_RIGHT] and key[pygame.K_DOWN]:
        img = "se"
    elif key[pygame.K_LEFT]:
        img = "w"
    elif key[pygame.K_RIGHT]:
        img = "e"
    elif key[pygame.K_UP]:
        img = "n"
    elif key[pygame.K_DOWN]:
        img = "s"

    print frame

    if not img_before == img:
        print "NEW IMAGE"
        frame = 0

    print frame

    img_before = img

    speed = 0.5

    if key[pygame.K_LEFT]:
        x = x - speed
    if key[pygame.K_RIGHT]:
        x = x + speed
    if key[pygame.K_UP]:
        y = y - speed
    if key[pygame.K_DOWN]:
        y = y + speed


    if x < 0:
        x = 0
    if y < 0:
        y = 0
    if x + sizex > screenx:
        x = screenx - sizex
    if y + sizey > screeny:
        y = screeny - sizey

    animation = surfaces[img]


    ekran.blit(animation[frame], (x,y))

    loop_counter = loop_counter + 1
    if loop_counter == 10:
        loop_counter = 0
        frame = frame + 1
        if frame >= len(animation):
            frame = 0


    pygame.display.update()
