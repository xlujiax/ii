import pygame
import math
import random
from pygame.locals import *
from sys import exit

size = (512, 512)

bg = pygame.Surface(size)
bg.fill((255,255,255))

def cloud_level(level, color, points = 10, amplitude = 10):
    pts = []
    pts.append((0,0))
    pts.append((0,level))

    for i in range(1,points):
        x = int(float(i) / float(points + 1) * size[0])
        y = random.randrange(level - amplitude, level + amplitude)
        pts.append((x,y))
    
    pts.append((size[1],level))
    pts.append((size[1],0))
    pygame.draw.polygon(bg, color, pts)


levels = 10
for i in range(1,levels):
    y = size[1] - int(float(i) / float(levels) * float(size[1]))
    brightness = float(i) / float(levels + 1) * 255
    color = (int(brightness * 0.2), int(brightness * 0.2), int(brightness))
    cloud_level(y, color)

pygame.image.save(bg, "bg.jpg")
