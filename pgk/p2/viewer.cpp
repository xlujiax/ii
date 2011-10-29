#include "viewer.hpp"

void viewer::init()
{
  model.read_from_file("figure.obj");
  pressed = false;
}

void viewer::animate(float) {}
void viewer::draw() const
{
  model.draw();
}

void viewer::mouseup()
{
  pressed = false;
}

void viewer::mousedown()
{
  pressed = true;
}

void viewer::mousemotion(const int x, const int y)
{
  if(pressed)
    printf("mouse: (%d, %d)\n", x, y);
}
