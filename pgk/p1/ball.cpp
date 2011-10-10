#include "ball.hpp"

ball::ball()
{
  color_r = 0.5;
  color_g = 0.5;
  color_b = 1.0;
  filled = true;
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
