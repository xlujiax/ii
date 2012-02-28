import pygame
import math
from pygame.locals import *
from sys import exit

pygame.init()
ekran = pygame.display.set_mode( (640,480) )
punkty = []
tryb = 0

def dist(p1, p2):
    dx = p1[0] - p2[0]
    dy = p1[1] - p2[1]
    return math.sqrt(dx**2 + dy**2)

def line_length(pts):
    sum = 0
    for i in range(0, len(pts) - 1):
        sum += dist(pts[i], pts[i+1])
    return sum

def shorten_path(pts):
    max_length = 400
    pts_shorten = pts
    if line_length(pts_shorten) <= max_length:
        return pts
   
    tail_point = (0,0)
    while line_length(pts_shorten) > max_length:
        tail_point = pts_shorten[0]
        del pts_shorten[0]
    assert tail_point != (0,0)
   
   
    actual_length = line_length(pts_shorten)
    diff_length = max_length - actual_length
    assert diff_length > 0
    assert len(pts_shorten) > 0
    last_point = pts_shorten[0]
   
    assert last_point != tail_point
    vector_dx = last_point[0] - tail_point[0]
    vector_dy = last_point[1] - tail_point[1]
    vector_len = dist(tail_point, last_point)
    vector_dx = vector_dx / vector_len # normalizacja 
    vector_dy = vector_dy / vector_len
    vector_dx = vector_dx * diff_length
    vector_dy = vector_dy * diff_length
    between_last_and_tail = (last_point[0] + vector_dx, last_point[1] + vector_dy)
   
    pts_shorten = [between_last_and_tail] + pts_shorten
   
    return pts_shorten

while True:
    for zdarzenie in pygame.event.get():
        if zdarzenie.type == QUIT:
            exit(0)
        if zdarzenie.type == MOUSEMOTION:
            punkty.append(zdarzenie.pos)
        if zdarzenie.type == MOUSEBUTTONDOWN:
            tryb += 1
            if tryb > 2: tryb = 0
         
    ekran.fill( (255,255,255) )
   
    if len(punkty) > 2:
        if tryb == 0:
            pygame.draw.lines(ekran, (70,255,10), False, punkty, 2)
        elif tryb == 1:
            pygame.draw.lines(ekran, (70,255,10), True, punkty, 4)
        else:
            pygame.draw.polygon(ekran,(70,255,10), punkty)
   
        punkty = shorten_path(punkty)     
    print line_length(punkty)
   
    pygame.display.update()   
