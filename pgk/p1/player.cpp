#include "player.hpp"

player::player()
  : vy(0),
    speed(0.16),
    sizex(20), sizey(100) {}

void player::draw() const
{
  GLfloat vertices[] = {
    x, y,
    x + sizex, y,
    x + sizex, y + sizey,
    x, y + sizey
  };

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);

  glDrawArrays(GL_QUADS, 0, 8);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void player::animate(const float dtime)
{
  y += dtime * vy;

  if(y > bottom_boundary - sizey)
    y = bottom_boundary - sizey;
  if(y < top_boundary)
    y = top_boundary;
}
