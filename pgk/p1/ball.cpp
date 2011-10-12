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

  if(rect::collide(*this, *left_paddle))
  {
    stick_to_right(*left_paddle);

    if(rect::collide(*this, left_paddle->upper_corner()))
    {
      vel = center() - left_paddle->upper_corner().lower_center();
      normalize_speed();
    }
    else if(rect::collide(*this, left_paddle->lower_corner()))
    {
      vel = center() - left_paddle->lower_corner().upper_center();
      normalize_speed();
    }
    else // srodek paletki
      vel.x *= -1;
  }

  if(rect::collide(*this, *right_paddle))
  {
    stick_to_left(*right_paddle);
    
    if(rect::collide(*this, right_paddle->upper_corner()))
    {
      vel = center() - right_paddle->upper_corner().lower_center();
      normalize_speed();
    }
    else if(rect::collide(*this, right_paddle->lower_corner()))
    {
      vel = center() - right_paddle->lower_corner().upper_center();
      normalize_speed();
    }
    else // srodek paletki
      vel.x *= -1;
  }
}
