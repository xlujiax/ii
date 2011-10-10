#include "player.hpp"

player::player()
{
  vel.y = 0.0;
  move_speed = 0.0;
}

void player::animate(const float dtime)
{
  pos += vel * dtime;

  if(rect::collide(*this, *top_boundary))
  {
    stick_to_bottom(*top_boundary);
    vel.y = 0;
  }

  if(rect::collide(*this, *bottom_boundary))
  {
    stick_to_top(*bottom_boundary);
    vel.y = 0;
  }
}
