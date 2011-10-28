#pragma once

struct viewer
{
  void init();
  void draw() const;
  void animate(float delta_time);
};
