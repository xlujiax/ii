"Maciej Pacut, Z3, L2"
import pygame

class Brick:
    def __init__(self, img, pos):
        self.pos = pos
        self.img = img

    def draw(self, surface):
        surface.blit(self.img, self.pos)
        # if any corner inside active_rect
        # draw small rect

class Playground:
    def __init__(self, rect):
        self.rect = rect
    def draw(self, surface):
        pygame.draw.rect(surface, (0, 0, 0), self.rect, 3)

class Grab:
    def __init__(self, mouse_pos, brick):
        self.brick = brick
        self.delta = (brick.pos[0] - mouse_pos[0],
                      brick.pos[1] - mouse_pos[1])

    def draw(self, surface, mouse_pos):
        "Takes actual mouse_pos"
        self.brick.pos = (self.delta[0] + mouse_pos[0],
                          self.delta[1] + mouse_pos[1])
        self.brick.draw(surface)

class Palette:
    def __init__(self, pos, rows):
        self.big_picture = pygame.image.load("PAVE.bmp")
        self.grid_size = 40
        self.margin = 3
        self.pos = pos
        self.rows = rows
        self.partition()

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

    def draw(self, surface):
        x = 0
        y = 0
        for brick in self.bricks:
            brick_pos = (self.pos[0] + x * (self.grid_size + self.margin),
                         self.pos[1] + y * (self.grid_size + self.margin))
            surface.blit(brick, brick_pos)
            x = x + 1
            if x == self.rows:
                y = y + 1
                x = 0
    def grab_brick(self, mouse_pos):
        x = 0
        y = 0
        for brick_surface in self.bricks:
            brick_pos = (self.pos[0] + x * (self.grid_size + self.margin),
                         self.pos[1] + y * (self.grid_size + self.margin))
            collision_rect = (brick_pos[0], brick_pos[1],
                              self.grid_size, self.grid_size)
            if pygame.Rect(collision_rect).collidepoint(mouse_pos):
                return Brick(brick_surface, brick_pos)
            x = x + 1
            if x == self.rows:
                y = y + 1
                x = 0
        return None

class Editor:
    def __init__(self):
        pygame.init()
        self.palette = Palette((10, 10), 2)
        self.screen_size = (640, 480)
        self.screen = pygame.display.set_mode(self.screen_size)
        self.grab = None
        self.mouse_pos = (0, 0)

    def frame(self):
        "Frame of animation"
        self.screen.fill((255, 255, 255))

        self.palette.draw(self.screen)

        if self.grab != None:
            self.grab.draw(self.screen, self.mouse_pos)
            
        pygame.display.update()

    def onmousemove(self, pos):
        "MOUSEMOTION event"
        self.mouse_pos = pos

    def onmousedown(self, pos):
        "MOUSEBUTTONDOWN event"
        brick = self.palette.grab_brick(pos)
        if brick != None:
            self.grab = Grab(pos, brick)

    def onmouseup(self, pos):
        "MOUSEBUTTONUP event"

    def loop(self):
        "Main loop"
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    exit(0)
                elif event.type == pygame.MOUSEMOTION:
                    self.onmousemove(event.pos)
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    self.onmousedown(event.pos)
                elif event.type == pygame.MOUSEBUTTONUP:
                    self.onmouseup(event.pos)
            self.frame()

Editor().loop()
