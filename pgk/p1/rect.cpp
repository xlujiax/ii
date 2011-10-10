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
  std::array<vec, 4> a_corners = a.corners();
  std::array<vec, 4> b_corners = b.corners();
  return std::all_of(b_corners.begin(), b_corners.end(), [&](const vec& v) {
      return a.point_inside(v);
    })
    &&
    std::all_of(a_corners.begin(), a_corners.end(), [&](const vec& v) {
      return b.point_inside(v);
    });
}

bool rect::point_inside(const vec& v) const
{
  return pos.x <= v.x && pos.x + size.x >= v.x &&
    pos.y <= v.y && pos.y + size.y >= v.y;
}
  
std::array<vec, 4> rect::corners() const
{
  return {{ pos,
	pos + vec(0, size.y),
	pos + vec(size.x, 0),
	pos + size }};
}
