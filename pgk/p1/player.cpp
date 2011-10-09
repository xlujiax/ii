#include "player.hpp"

player::player()
  : vx(0), vy(0),
    speed(0.10),
    sizex(20), sizey(100) {}

void player::draw() const
{
  glBegin(GL_POLYGON);
  glVertex2f(x, y);
  glVertex2f(x + sizex, y);
  glVertex2f(x + sizex, y + sizey);
  glVertex2f(x, y + sizey);
  glEnd();
}

void player::animate(const float dtime)
{
  x += dtime * vx;
  y += dtime * vy;
}
