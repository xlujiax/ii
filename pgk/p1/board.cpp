#include "board.hpp"

void board::draw() const
{
  GLint vertices[] = {
    x, y,
    x + sizex, y,
    x + sizex, y + sizey,
    x, y + sizey,

    x, y
  };

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_INT, 0, vertices);

  glDrawArrays(GL_LINE_STRIP, 0, 10);

  glDisableClientState(GL_VERTEX_ARRAY);
}
