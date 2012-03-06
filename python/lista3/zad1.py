#!/usr/bin/env python

import pygame
from pygame.locals import *
from sys import exit
from random import randint

def draw(pos, color):
  (xm, ym) = pos
  x = xm / 10
  y = ym / 10
  if x >= 0 and x < 64 and y >= 0 and y < 48:
    image.set_at((x, y), color)

pygame.init()
screen = pygame.display.set_mode((640, 480))

image = pygame.Surface((64, 48))

mouseButtonDown = False
rightButton = False

clearColor = (255, 255, 255)
image.fill(clearColor)

fillColor = [(0, 0, 0),
             (255, 0, 0),
             (255, 255, 0),
             (0, 255, 0),
             (255, 0, 255),
             (0, 0, 255)]
colorIndex = 0

small = False

while True:
  for event in pygame.event.get():
    if event.type == QUIT:
      exit()
    if event.type == MOUSEBUTTONDOWN:
      if event.button == 3:
        rightButton = True
        draw(event.pos, clearColor)
      else:
        draw(event.pos, fillColor[colorIndex])
        rightButton = False
      mouseButtonDown = True

    if event.type == MOUSEMOTION:
      if mouseButtonDown:
        if rightButton:
          draw(event.pos, clearColor)
        else:
          draw(event.pos, fillColor[colorIndex])
           
    if event.type == MOUSEBUTTONUP:
      mouseButtonDown = False
      rightButton = False

    key = pygame.key.get_pressed()
    if key[pygame.K_1]: colorIndex = 0
    if key[pygame.K_2]: colorIndex = 1
    if key[pygame.K_3]: colorIndex = 2
    if key[pygame.K_4]: colorIndex = 3
    if key[pygame.K_5]: colorIndex = 4
    if key[pygame.K_6]: colorIndex = 5

    if key[pygame.K_SPACE]: small = True
    else: small = False
    
    if small:
      screen.fill(clearColor)
      screen.blit(image, (0, 0))
    else:
      working = pygame.Surface((640, 480))
      pygame.transform.scale(image, (640, 480), working)
      screen.blit(working, (0, 0))
     
    pygame.display.update()
    
