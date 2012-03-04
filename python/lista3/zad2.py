"Maciej Pacut, Z2, L3"
import pygame

class Animation:
    "Train"

    def __init__(self):
        pygame.init()
        self.screen_size = (640, 480)
        self.screen = pygame.display.set_mode(self.screen_size)

    def frame(self):
        "Frame of animation"

        self.screen.fill((255, 255, 255))

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
