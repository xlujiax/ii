#include "ball.hpp"

ball::ball()
{
  color_r = 1.0;
  color_g = 1.0;
  color_b = 1.0;
}

void ball::animate(const float dtime)
{
  pos += vel * dtime;

  if(rect::collide(*this, *top_boundary))
  {
    stick_to_bottom(*top_boundary);
    vel.y *= -1;
  }

  if(rect::collide(*this, *bottom_boundary))
  {
    stick_to_top(*bottom_boundary);
    vel.y *= -1;
  }
}
