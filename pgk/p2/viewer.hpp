#pragma once

#include <cstdio>

#include "obj_format.hpp"

struct viewer
{
  obj_format model;
  
  void init();
  void draw() const;
  void animate(float delta_time);

  bool pressed;
  void mouseup();
  void mousedown();
  void mousemotion(const int x, const int y);
};
