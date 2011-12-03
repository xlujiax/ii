#pragma once

#include <SDL.h>

struct timer
{
  void init();
  float delta_time(); // in miliseconds
private:
  int old_time;
};
