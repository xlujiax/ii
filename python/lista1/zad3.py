import pygame
import math
import random
from pygame.locals import *
from sys import exit

size = (512, 512)

bg = pygame.Surface(size)
bg.fill((0,255,0))

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

for i in range(0,4):
    y = size[1] - int(float(i) / float(levels) * float(size[1]))
    brightness = float(4 + i) / float(8) * 255
    color = (int(brightness * 0.2), int(brightness), int(brightness * 0.2))
    cloud_level(y, color, 20)
    
for i in range(4,levels):
    y = size[1] - int(float(i) / float(levels) * float(size[1]))
    brightness = 255 - float(i) / float(levels + 1) * 128
    color = (int(brightness * 0.1), int(brightness * 0.1), int(brightness))
    cloud_level(y, color, 20)

pygame.image.save(bg, "bg.jpg")
