#include "game.hpp"

void game::place_ball_on_the_left()
{
  ball1.pos.x = board1.pos.x + player_left.size.x;
  ball1.pos.y = board1.pos.y + board1.size.y / 2 - ball1.size.y / 2;

  ball1.vel.x = 2;
  ball1.vel.y = 1;
  ball1.normalize_speed();
}

void game::place_ball_on_the_right()
{
  ball1.pos.x = board1.pos.x + board1.size.x - player_left.size.x - ball1.size.x;
  ball1.pos.y = board1.pos.y + board1.size.y / 2 - ball1.size.y / 2;

  ball1.vel.x = -2;
  ball1.vel.y = 1;
  ball1.normalize_speed();
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
    
    board1.pos = vec(margin, margin);
    board1.size = vec(width - 2*margin);
  }

  {
    const float boundary_size = 100;

    top_boundary.pos = vec(board1.pos.x, board1.pos.y - boundary_size);
    top_boundary.size = vec(board1.size.x, boundary_size);

    bottom_boundary.pos = vec(board1.pos.x, board1.pos.y + board1.size.y);
    bottom_boundary.size = vec(board1.size.x, boundary_size);

    left_score.pos = vec(board1.pos.x - boundary_size, board1.pos.y);
    left_score.size = vec(boundary_size, board1.size.y);

    right_score.pos = vec(board1.pos.x + board1.size.x, board1.pos.y);
    right_score.size = vec(boundary_size, board1.size.y);
  }

  {
    player_left.size = vec(20, 160);
    player_left.corner_size = 20;
    player_left.top_boundary = &top_boundary;
    player_left.bottom_boundary = &bottom_boundary;
    
    player_right.size = vec(20, 160);
    player_right.corner_size = 20;
    player_right.top_boundary = &top_boundary;
    player_right.bottom_boundary = &bottom_boundary;
    
    reset_paddles();
  }

  {
    ball1.size = vec(20, 20);
    ball1.top_boundary = &top_boundary;
    ball1.bottom_boundary = &bottom_boundary;
    ball1.left_paddle = &player_left;
    ball1.right_paddle = &player_right;
    place_ball_on_the_right();
  }
}

void game::animate(const float delta_time)
{
  player_left.animate(delta_time);
  player_right.animate(delta_time);
  ball1.animate(delta_time);

  if(rect::collide(ball1, left_score))
  {
    reset_paddles();
    place_ball_on_the_left();
  }
  
  if(rect::collide(ball1, right_score))
  {
    reset_paddles();
    place_ball_on_the_right();
  }
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
