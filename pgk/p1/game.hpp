#pragma once

#include "timer.hpp"
#include "player.hpp"
#include "ball.hpp"
#include "board.hpp"

struct game
{
  player p1, p2;
  
  board board1;
  ball ball1;

  void init();
  void animate(const float);
  void draw() const;
  void keyup(char);
  void keydown(char);
};
