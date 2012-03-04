"Maciej Pacut, Z2, L3"
import pygame
import random

# http://www.pygame.org/pcr/fpstimer/index.php
class FpsClock:
    def __init__(self):
        self.frame_duration = 0.000
        self.this_frame_time = 0
        self.last_frame_time = 0
        return
    
    def tick(self):
        "Call this every frame"
        self.this_frame_time = self.get_current_time()
        self.frame_duration = (self.this_frame_time - self.last_frame_time) / 1000.000
        self.last_frame_time = self.this_frame_time
        return

    def get_frame_duration(self):
        "Returns the length of the previous frame, in seconds"
        return self.frame_duration

    def get_current_time(self):
        "Used internally. Returns current time in ms."
        return pygame.time.get_ticks()

    def begin(self):
        "Starts/restarts the timer. Call just before your main loop."
        self.last_frame_time = self.get_current_time()
        return

class Particle:
    def __init__(self, pos, r, vel, time_to_death):
        self.pos = pos
        self.r = r
        self.vel = vel
        self.time_to_death = time_to_death
    def draw(self, surface):
        pygame.draw.circle(surface, (128, 128, 128), (int(self.pos[0]), int(self.pos[1])), int(self.r), 1)
    def animate(self, deltatime):
        self.time_to_death = self.time_to_death - deltatime
        diff = 0.1
        self.pos = (self.pos[0] + random.uniform(-diff, diff) + deltatime * self.vel[0],
                    self.pos[1] + random.uniform(-diff, diff) + deltatime * self.vel[1])
    def dead(self):
        return self.time_to_death < 0

class ParticleSystem:
    def __init__(self, rect):
        self.rect = rect
        self.particles = []
        self.emmit_every = 3
        self.time_to_emmit = 0
        
    def draw(self, surface):
        for p in self.particles:
            p.draw(surface)
            
    def animate(self, deltatime):
        self.time_to_emmit -= deltatime
        if self.time_to_emmit < 0.0:
            self.emmit()
            self.time_to_emmit = self.emmit_every
        for p in self.particles:
            p.animate(deltatime)
        self.particles = [p for p in self.particles if not p.dead()]

    def emmit(self):
        pos = (random.uniform(self.rect[0], self.rect[2]),
               random.uniform(self.rect[1], self.rect[3]))
        vel = (random.uniform(-100, 100), random.uniform(0, -100))
        self.particles.append(Particle(pos, random.uniform(10, 20), vel, 1000))
        

class Animation:
    "Train"

    def __init__(self):
        pygame.init()
        self.screen_size = (640, 480)
        self.screen = pygame.display.set_mode(self.screen_size)
        self.timer = FpsClock()
        self.timer.begin()
        self.particles = ParticleSystem((40, 40, 40, 40))

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
        self.particles.draw(self.screen)
        
        deltatime = self.timer.get_frame_duration()
        self.particles.animate(deltatime)

        self.timer.tick()

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
