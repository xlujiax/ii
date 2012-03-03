"Maciej Pacut, Z3, L2"
import pygame

class Palette:
    def __init__(self):
        self.big_picture = pygame.image.load("PAVE.bmp")
        self.grid_size = 40
        self.partition()
        print len(self.bricks)

    def partition(self):
        full_blocks = [(1, 1), (3, 1), (5, 1), (7, 1),
                       (1, 3), (3, 3), (5, 3), (7, 3), (9, 3),
                       (1, 5), (3, 5), (5, 5), (7, 5), (9, 5),
                       (1, 7), (3, 7), (5, 7)]
        self.bricks = [self.big_picture.subsurface(self.__rect(x, y))
                       for (x, y) in full_blocks]

    def __rect(self, x, y):
        return (x * self.grid_size, y * self.grid_size,
                self.grid_size, self.grid_size)

    def draw(self, surface, pos, rows):
        margin = 3
        x = 0
        y = 0
        for brick in self.bricks:
            brick_pos = (pos[0] + x * (self.grid_size + margin),
                         pos[1] + y * (self.grid_size + margin))
            surface.blit(brick, brick_pos)
            x = x + 1
            if x == rows:
                y = y + 1
                x = 0
            
    
class Editor:
    def __init__(self):
        pygame.init()
        self.palette = Palette()
        self.screen_size = (640, 480)
        self.screen = pygame.display.set_mode(self.screen_size)

    def frame(self):
        "Frame of animation"
        self.screen.fill((255, 255, 255))

        self.palette.draw(self.screen, (10, 10), 2)
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
