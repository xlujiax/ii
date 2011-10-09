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
