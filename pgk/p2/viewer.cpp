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

void viewer::mousemotion(
  const float x, const float y,
  const float xrel, const float yrel
			 )
{
  if(pressed)
    printf("mouse: (%f, %f), d(%f, %f)\n", x, y, xrel, yrel);
}
