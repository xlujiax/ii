"Maciej Pacut, Z3, L2"
import pygame

class Editor:
    "Edytor Jednej Kreski"

    def __init__(self):
        pygame.init()
        self.palette = pygame.image.load("PAVE.bmp")
        self.screen_size = (640, 480)
        self.screen = pygame.display.set_mode(self.screen_size)

    def frame(self):
        "Frame of animation"
        self.screen.blit(self.palette, (0, 0))

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
