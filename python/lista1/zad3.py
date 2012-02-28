"""
Maciej Pacut, 1.3
"""
import pygame
import random
import pygame.locals

SIZE = (512, 512)

BG = pygame.Surface(SIZE)
BG.fill((0, 255, 0))

def cloud_level(level, color, points = 10, amplitude = 10):
    """
    Renders polygon
    """
    pts = []
    pts.append((0, 0))
    pts.append((0, level))

    for i in range(1, points):
        x_coord = int(float(i) / float(points + 1) * SIZE[0])
        y_coord = random.randrange(level - amplitude, level + amplitude)
        pts.append((x_coord, y_coord))
    
    pts.append((SIZE[1], level))
    pts.append((SIZE[1], 0))
    pygame.draw.polygon(BG, color, pts)


def draw_bg(levels):
    """
    grass then sky
    """
    for i in range(0, 4):
        y_coord = SIZE[1] - int(float(i) / float(levels) * float(SIZE[1]))
        brightness = float(4 + i) / float(8) * 255
        color = (int(brightness * 0.2), int(brightness), int(brightness * 0.2))
        cloud_level(y_coord, color, 20)

    for i in range(4, levels):
        y_coord = SIZE[1] - int(float(i) / float(levels) * float(SIZE[1]))
        brightness = 255 - float(i) / float(levels + 1) * 128
        color = (int(brightness * 0.1), int(brightness * 0.1), int(brightness))
        cloud_level(y_coord, color, 20)

draw_bg(10)

pygame.image.save(BG, "bg.jpg")
