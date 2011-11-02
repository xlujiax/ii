#pragma once

#include <cstdio>

#include "obj_format.hpp"

struct viewer
{
  float zoom;
  float r1;
  float r2;
  float r3;

  obj_format model;
  
  void init();
  void draw() const;
  void animate(float delta_time);

  void keyup(const char);
  void keydown(const char);
  
  bool pressed;
  void mouseup();
  void mousedown(const float x, const float y);

  void mousewheelup();
  void mousewheeldown();

  void mousemotion(const float x, const float y);
};
