"Maciej Pacut, Z3, L2"
import pygame

class Palette:
    def __init__(self):
        self.big_picture = pygame.image.load("PAVE.bmp")
        self.grid_size = 40
        self.partition()

    def partition(self):
        full_blocks = [(1, 1), (3, 1), (5, 1), (7, 1),
                       (1, 3), (3, 3), (5, 3), (7, 3), (9, 3), (11, 3),
                       (1, 5), (3, 5), (5, 5), (7, 5), (9, 5), (11, 5),
                       (1, 7), (3, 7), (5, 7), (7, 7)]
        self.bricks = [self.big_picture.subsurface(self.__rect(x,y))
                       for (x, y) in full_blocks]

    def __rect(self, x, y):
        return (x * self.grid_size, y * self.grid_size,
                self.grid_size, self.grid_size)
    
class Editor:
    def __init__(self):
        pygame.init()
        self.palette = Palette()
        self.screen_size = (640, 480)
        self.screen = pygame.display.set_mode(self.screen_size)

    def frame(self):
        "Frame of animation"
        self.screen.fill((255, 255, 255))
        self.screen.blit(self.palette.bricks[0], (0, 0))
        pygame.display.update()

    def onmousemove(self, pos):
        "MOUSEMOTION event"

    def onmouseclick(self, pos):
        "MOUSEBUTTONDOWN event"

    def onexit(self):
        "QUIT event"

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
