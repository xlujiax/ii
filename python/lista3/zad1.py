#!/usr/bin/env python

import pygame
import os
from pygame.locals import *
from sys import exit
from random import randint

def draw(pos, color):
  (xm, ym) = pos
  x = xm / 10
  y = ym / 10
  draw_aux(x, y, color)
  if a3x3:
    draw_aux(x - 1, y - 1, color)
    draw_aux(x - 1, y, color)
    draw_aux(x - 1, y + 1, color)
    draw_aux(x, y - 1, color)
    draw_aux(x, y + 1, color)
    draw_aux(x + 1, y - 1, color)
    draw_aux(x + 1, y, color)
    draw_aux(x + 1, y + 1, color)

def draw_aux(x, y, color):
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
a3x3 = False
mousePos = (0, 0)

while True:
  for event in pygame.event.get():
    if event.type == QUIT:
      pygame.image.save(image, "rys.bmp")
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
      mousePos = event.pos
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
    
    if key[pygame.K_LSHIFT]: a3x3 = True
    else: a3x3 = False
    
    if small:
      screen.fill(clearColor)
      screen.blit(image, (0, 0))
    else:
      working = pygame.Surface((640, 480))
      working.convert(image)
      pygame.transform.scale(image, (640, 480), working)
      screen.blit(working, (0, 0))

      if a3x3:
        cursor = pygame.Surface((30,30))
        cursor.fill((128, 128, 128))
        screen.blit(cursor, (((mousePos[0] / 10) - 1) * 10, ((mousePos[1] / 10) - 1) * 10))
     
    pygame.display.update()
    
