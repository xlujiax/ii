#include "ball.hpp"

void ball::draw() const
{
  GLfloat vertices[] = {
    x + radius, y - radius,
    x + radius, y + radius,
    x - radius, y + radius,
    x - radius, y - radius
  };

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);

  glDrawArrays(GL_QUADS, 0, 8);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void ball::animate(const float dtime)
{
  y += dtime * vy;
  x += dtime * vx;

  if(y > bottom_boundary - radius)
  {
    y = bottom_boundary - radius;
    vy *= -1;
  }
  if(y < top_boundary + radius)
  {
    y = top_boundary + radius;
    vy *= -1;
  }
}
