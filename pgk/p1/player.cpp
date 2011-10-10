#include "player.hpp"

player::player()
{
  vy = 0.0;
  speed = 0.0;
}

void player::animate(const float dtime)
{
  pos.y += dtime * vy;

  if(rect::collide(*this, top_boundary))
  {
    stick_to_bottom(top_boundary);
    vy = 0;
  }

  if(rect::collide(*this, bottom_boundary))
  {
    stick_to_top(bottom_boundary);
    vy = 0;
  }
}
