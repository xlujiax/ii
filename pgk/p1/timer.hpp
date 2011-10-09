#pragma once

#include <SDL.h>

struct timer
{
  int old_time;
  void init();
  float delta_time(); // in miliseconds
};
