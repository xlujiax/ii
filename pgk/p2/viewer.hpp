#pragma once

#include "obj_format.hpp"

struct viewer
{
  obj_format model;
  
  void init();
  void draw() const;
  void animate(float delta_time);
};
