#include "player.hpp"

player::player()
{
  vel.y = 0.0;
  move_speed = 0.16;
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

rect player::lower_corner() const
{
  rect lower_corner;
  lower_corner.size = vec(size.x, corner_size);
  lower_corner.pos = pos + vec(0, size.y - lower_corner.size.y);
  return lower_corner;
}

rect player::upper_corner() const
{
  rect upper_corner;
  upper_corner.size = vec(size.x, corner_size);
  upper_corner.pos = pos;
  return upper_corner;
}

rect player::middle() const
{
  rect middle;
  middle.size = vec(size.x, size.y - 2.0 * corner_size);
  middle.pos = pos + vec(0.0, corner_size);
  return middle;
}
