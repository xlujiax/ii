#include "timer.hpp"

void timer::init()
{
  old_time = SDL_GetTicks();
}

float timer::delta_time()
{
  int new_time = SDL_GetTicks();
  int dtime = new_time - old_time;
  old_time = new_time;
  return static_cast<float>(dtime);
}
