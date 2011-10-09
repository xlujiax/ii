#include "ball.hpp"

void ball::draw() const
{
  glBegin(GL_LINE_STRIP);

  glVertex2f(x - radius, y - radius);
  glVertex2f(x + radius, y - radius);
  glVertex2f(x + radius, y + radius);
  glVertex2f(x - radius, y + radius);
  glVertex2f(x - radius, y - radius);
  glEnd();
}
