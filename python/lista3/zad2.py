"Maciej Pacut, Z2, L3"
import pygame

class Animation:
    "Train"

    def __init__(self):
        pygame.init()
        self.screen_size = (640, 480)
        self.screen = pygame.display.set_mode(self.screen_size)

    def draw_static(self):
        "Draw static part of train"
        start = (100, 100)
        movements = [(0, 100),
                     (-20, 20),
                     (0, 80),
                     (20, 20),
                     (400, 0),
                     (0, -100),
                     (-40, 0),
                     (0, -40),
                     (10, -5),
                     (-30, 0),
                     (10, 5),
                     (0, 40),
                     (-200, 0),
                     (0, -80),
                     (70, -40)]

        points = [start]
        for m in movements:
            start = (start[0] + m[0], start[1] + m[1])
            points.append(start)
        
        pygame.draw.polygon(self.screen, (0, 0, 0), points)

    def frame(self):
        "Frame of animation"

        self.screen.fill((255, 255, 255))

        self.draw_static()

        pygame.display.update()

    def loop(self):
        "Main loop"
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    exit(0)
            self.frame()

Animation().loop()
