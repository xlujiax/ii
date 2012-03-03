#!/usr/bin/env python

import pygame
from pygame.locals import *
from sys import exit
from random import randint


   
rysunek = []
for i in range(48):
  rysunek.append( 64 * [0])
  
def uaktualnijRysunek(pos,bit):
    xm,ym = event.pos
    x = xm/10
    y = ym/10
    if x >=0 and x<64 and y >= 0 and y < 48:
      rysunek[y][x] = bit

pygame.init()
screen = pygame.display.set_mode((640, 480))

points = []

myszkaSieRusza = False

while True:
        
    for event in pygame.event.get():
        if event.type == QUIT:
            exit()
        if event.type == MOUSEBUTTONDOWN:
            uaktualnijRysunek(event.pos,1)
            myszkaSieRusza = True
                
        if event.type == MOUSEMOTION:
           if myszkaSieRusza:
              uaktualnijRysunek(event.pos,1)
           
        if event.type == MOUSEBUTTONUP:
           myszkaSieRusza = False
                     
                      
    screen.fill((255,255,255))
    
    for i in range(48):
       for j in range(64):
          if rysunek[i][j]:
             pygame.draw.rect(screen,(0,0,0), pygame.Rect(10*j,10*i,10,10) )
     
    pygame.display.update()
    
