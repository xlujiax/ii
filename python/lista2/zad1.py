"Maciej Pacut, Z1, L2"
import pygame
import pygame.locals
import os.path

def read_line(filename):
    "Read list of line points stored in file"
    if os.path.isfile(filename):
        line_file = open(filename, 'r')
        return eval(line_file.read()) # sploit alert
    else:
        return []

def store_line(filename, pts):
    "Writes list of line points to file"
    line_file = open(filename, 'w')
    line_file.write(str(pts))

class Editor:
    "Edytor Jednej Kreski"

    def __init__(self):
        pygame.init()
        self.circle_size = 10
        self.background = pygame.image.load("bg.jpg")
        self.screen_size = (640, 480)
        self.screen = pygame.display.set_mode(self.screen_size)
        self.active_circle = None
        self.pts = read_line('serialized.bin')

    def frame(self):
        "Frame of animation"
        self.screen.blit(self.background, (0, 0))

        self.draw_line()

        pygame.display.update()

    def draw_line(self):
        "Draw polyline with circles"
        if len(self.pts) >= 2:
            pygame.draw.lines(self.screen, (0, 0, 0), False, self.pts, 3)

        for i in self.pts:
            pygame.draw.circle(self.screen, (0, 0, 0), i, self.circle_size)


    def in_circle(self, circle, pos):
        "Checks if point is inside of the circle"
        deltax = pos[0] - circle[0]
        deltay = pos[1] - circle[1]
        dist = deltax**2 + deltay**2
        return dist < self.circle_size**2

    def find_circle(self, pos):
        "Find circle that contains pos"
        for i in range(0, len(self.pts)):
            if self.in_circle(self.pts[i], pos):
                return i
        return None

    def onmousemove(self, pos):
        "MOUSEMOTION event"
        if self.active_circle != None:
            self.pts[self.active_circle] = pos

    def onmouseclick(self, pos):
        "MOUSEBUTTONDOWN event"
        if self.active_circle != None:
            self.active_circle = None
        else:
            self.active_circle = self.find_circle(pos)
            if self.active_circle == None:
                self.pts.append(pos)

    def onexit(self):
        "QUIT event"
        store_line('serialized.bin', self.pts)

    def loop(self):
        "Main loop"
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.onexit()
                    pygame.quit()
                    exit(0)
                elif event.type == pygame.MOUSEMOTION:
                    self.onmousemove(event.pos)
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    self.onmouseclick(event.pos)
            self.frame()

Editor().loop()
