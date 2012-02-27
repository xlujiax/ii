import pygame
import math
from pygame.locals import *
from sys import exit

size = (512, 512)

bg = pygame.Surface(size)
bg.fill((255,255,255))
pygame.draw.circle(bg, (255,0,0), (100,100), 30)
pygame.image.save(bg, "bg.jpg")
