#include "rect.hpp"

rect::rect()
{
  color_r = 1.0;
  color_g = 1.0;
  color_b = 1.0;
  filled = true;
  visible = true;
}

void rect::draw() const
{
  if(visible)
  {
    glColor3f(color_r, color_g, color_b);
    
    if(filled)
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
    else
    {
      GLfloat vertices[] = {
	pos.x, pos.y,
	pos.x + size.x, pos.y,
	pos.x + size.x, pos.y + size.y,
	pos.x, pos.y + size.y,
	pos.x, pos.y
      };

      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(2, GL_FLOAT, 0, vertices);

      glDrawArrays(GL_LINE_STRIP, 0, 10);

      glDisableClientState(GL_VERTEX_ARRAY);
    }
  }
}

bool rect::collide(const rect& a, const rect& b)
{
  // uproszczony model kolizji nie biorący pod uwagę sytuacji,
  // w której prostokąty kolidują środkami
  //          +-+
  //          | |
  //        +-+-+-+
  //        | | | |
  //        +-+-+-+
  //          | | 
  //          +-+
  
  auto a_corners = a.corners();
  auto b_corners = b.corners();
  return std::any_of(b_corners.begin(), b_corners.end(), [&](const vec& v) {
      return a.point_inside(v);
    })
    ||
    std::any_of(a_corners.begin(), a_corners.end(), [&](const vec& v) {
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

void rect::stick_to_bottom(const rect& r)
{
  pos.y = r.pos.y + r.size.y;
}

void rect::stick_to_top(const rect& r)
{
  pos.y = r.pos.y - size.y
}

void rect::stick_to_left(const rect& r)
{
  pos.x = r.pos.x - size.x;
}

void rect::stick_to_right(const rect& r)
{
  pos.x = r.pos.x + r.size.x;
}
