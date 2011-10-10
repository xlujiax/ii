#include "rect.hpp"

void rect::draw() const
{
  GLfloat vertices[] = {
    pos.x, pos.y,
    pos.x + size.x, pos.y,
    pos.x + size.x, pos.y + size.y,
    pos.x, pos.y + size.y
  };

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);

  glDrawArrays(GL_QUADS, 0, 8);

  glDisableClientState(GL_VERTEX_ARRAY);
}

bool rect::collide(const rect& a, const rect& b)
{
  return false;
}
