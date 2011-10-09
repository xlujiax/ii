#include "board.hpp"

void board::draw() const
{
  glBegin(GL_LINE_STRIP);
  glVertex2f(x, y);
  glVertex2f(x + sizex, y);

  glVertex2f(x + sizex, y + sizey);
  glVertex2f(x, y + sizey);
  glVertex2f(x, y);
  glEnd();
}
