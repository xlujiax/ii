#pragma once

#include "player.hpp"
#include "ball.hpp"
#include "board.hpp"

#include <memory>
#include <array>
#include <algorithm>

struct game
{
  player player_left;
  player player_right;

  board board1;
  
  rect top_boundary;
  rect bottom_boundary;
  rect left_score;
  rect right_score;
  
  ball ball1;

  void init();
  void animate(const float);
  void draw() const;
  void keyup(char);
  void keydown(char);
private:
  void place_ball_on_the_left();
  void place_ball_on_the_right();
  void reset_paddles();
};
