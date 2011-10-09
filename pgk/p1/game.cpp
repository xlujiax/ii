#include "game.hpp"

void game::init()
{
  const int paddle_to_border_dist = 20;
  p1.x = 10 + paddle_to_border_dist;
  p1.y = 100;

  p2.x = 630 - paddle_to_border_dist - p2.sizex;
  p2.y = 300;

  board1.x = 10;
  board1.y = 10;
  board1.sizex = 620;
  board1.sizey = 460;

  ball1.x = 200;
  ball1.y = 200;
  ball1.radius = 10;
}

void game::animate(const float delta_time)
{
  p1.animate(delta_time);
  p2.animate(delta_time);
}

void game::draw() const
{
  glColor3f(0.8,0.8,0.2);
  p1.draw();

  glColor3f(0.5,0.5,0.8);
  p2.draw();

  glColor3f(1.0,1.0,1.0);
  board1.draw();
  
  glColor3f(1.0,1.0,1.0);
  ball1.draw();
}

void game::keyup(char k)
{
  switch(k)
  {
    case 'a':
      p1.move_up_end();
      break;
    case 'z':
      p1.move_down_end();
      break;
    case 'k':
      p2.move_up_end();
      break;
    case 'm':
      p2.move_down_end();
      break;
    default:
      break;
  }
}

void game::keydown(char k)
{
  switch(k)
  {
    case 'a':
      p1.move_up();
      break;

    case 'z':
      p1.move_down();
      break;

    case 'k':
      p2.move_up();
      break;

    case 'm':
      p2.move_down();
      break;

    default:
      break;
  }
}
