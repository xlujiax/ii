#pragma once

#include "player.hpp"
#include "ball.hpp"
#include "board.hpp"

#include <memory>
#include <array>
#include <algorithm>

struct game
{
  std::shared_ptr<player> player_left;
  std::shared_ptr<player> player_right;

  std::shared_ptr<board> board1;
  
  std::shared_ptr<rect> top_boundary;
  std::shared_ptr<rect> bottom_boundary;
  std::shared_ptr<rect> left_score;
  std::shared_ptr<rect> right_score;
  
  std::shared_ptr<ball> ball1;

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
