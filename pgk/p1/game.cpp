#include "game.hpp"

void game::place_ball_on_the_left()
{
  ball1.pos.x = board1.pos.x + player_left.size.x;
  ball1.pos.y = board1.pos.y + board1.size.y / 2 - ball1.size.y / 2;
}

void game::place_ball_on_the_right()
{
  ball1.pos.x = board1.pos.x + board1.size.x - player_left.size.x - ball1.size.x;
  ball1.pos.y = board1.pos.y + board1.size.y / 2 - ball1.size.y / 2;
}

void game::reset_paddles()
{
  player_left.pos.x = board1.pos.x;
  player_left.pos.y = board1.pos.y + board1.size.y / 2 - player_left.size.y / 2;
  
  player_right.pos.x = board1.pos.x + board1.size.x - player_right.size.x;
  player_right.pos.y = board1.pos.y + board1.size.y / 2 - player_right.size.y / 2;
}

void game::init()
{
  {
    const float margin = 10.0;
    const float width = 640;
    const float height = 480;
    
    board1.pos.x = margin;
    board1.pos.y = margin;
    board1.size.x = width - 2*margin;
    board1.size.y = height - 2*margin;;
  }

  {
    const float boundary_size = 100;

    {
      top_boundary.pos.x = board1.pos.x;
      top_boundary.pos.y = board1.pos.y - boundary_size;
      top_boundary.size.x = board1.size.x;
      top_boundary.size.y = boundary_size;
    }

    {
      bottom_boundary.pos.x = board1.pos.x;
      bottom_boundary.pos.y = board1.pos.y;
      bottom_boundary.size.x = board1.size.x;
      bottom_boundary.size.y = boundary_size;
    }

    {
      left_score.pos.x = board1.pos.x - boundary_size;
      left_score.pos.y = board1.pos.y;
      left_score.size.x = boundary_size;
      left_score.size.y = board1.size.y;
    }
    
    {
      right_score.pos.x = board1.pos.x + board1.size.x;
      right_score.pos.y = board1.pos.y;
      right_score.size.x = boundary_size;
      right_score.size.y = board1.size.y;
    }
  }

  player_left.size = vec(20, 160);
  player_right.size = vec(20, 160);
  reset_paddles();

  ball1.size = vec(20, 20);
  place_ball_on_the_right();
}

void game::animate(const float delta_time)
{
  //player_left.animate(delta_time);
  //player_right.animate(delta_time);
  //ball1.animate(delta_time);
}

void game::draw() const
{
  board1.draw();
  player_left.draw();
  player_right.draw();
  ball1.draw();
}

void game::keyup(char k)
{
  switch(k)
  {
    case 'a':
      player_left.move_up_end();
      break;
    case 'z':
      player_left.move_down_end();
      break;
    case 'k':
      player_right.move_up_end();
      break;
    case 'm':
      player_right.move_down_end();
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
      player_left.move_up();
      break;

    case 'z':
      player_left.move_down();
      break;

    case 'k':
      player_right.move_up();
      break;

    case 'm':
      player_right.move_down();
      break;

    default:
      break;
  }
}
