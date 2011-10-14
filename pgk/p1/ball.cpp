#include "ball.hpp"

ball::ball()
{
  color_r = 0.5;
  color_g = 0.5;
  color_b = 1.0;
  filled = true;
  speed = 0.24;
}

void ball::normalize_speed()
{
  vel = vel.normal();
  vel = vel * speed;
}

void ball::handle_collision_with_player(const player& paddle)
{
  if(rect::collide(*this, paddle.middle()))
  {
    vel.x *= -1;
  }
  else if(rect::collide(*this, paddle.upper_corner()))
  {
    vel = center() - paddle.upper_corner().middle_of(edge::bottom);
    normalize_speed();
  }
  else if(rect::collide(*this, paddle.lower_corner()))
  {
    vel = center() - paddle.lower_corner().middle_of(edge::top);
    normalize_speed();
  }
}

void ball::animate(const float dtime)
{
  pos += vel * dtime;

  if(rect::collide(*this, *top_boundary))
  {
    stick_to(edge::bottom, *top_boundary);
    vel.y *= -1;
  }

  if(rect::collide(*this, *bottom_boundary))
  {
    stick_to(edge::top, *bottom_boundary);
    vel.y *= -1;
  }

  if(rect::collide(*this, *left_paddle))
  {
    stick_to(edge::right, *left_paddle);
    handle_collision_with_player(*left_paddle);
  }

  if(rect::collide(*this, *right_paddle))
  {
    stick_to(edge::left, *right_paddle);
    handle_collision_with_player(*right_paddle);
  }
}
