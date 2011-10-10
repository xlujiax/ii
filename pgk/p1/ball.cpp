#include "ball.hpp"

ball::ball()
{
  color_r = 1.0;
  color_g = 1.0;
  color_b = 1.0;
}

void ball::animate(const float dtime)
{
  pos += dtime * vel;

  if(rect::collide(*this, top_boundary))
  {
    stick_to_bottom(top_boundary);
    vy *= -1;
  }

  if(rect::collide(*this, bottom_boundary))
  {
    stick_to_top(bottom_boundary);
    vy *= -1;
  }
}
