#include "viewer.hpp"

void viewer::init()
{
  model.read_from_file("figure.obj");
  pressed = false;
}

void viewer::animate(float) {}
void viewer::draw() const
{
  const float zoom = 0.0;
  const float r1 = 0;
  const float r2 = 0;
  const float r3 = 0;
  glPushMatrix();
  glTranslatef(0.0, 0.0, zoom);
  glRotatef(r1, 1.0, 0.0, 0.0);
  glRotatef(r2, 0.0, 1.0, 0.0);
  glRotatef(r3, 0.0, 0.0, 1.0);

  model.draw();
  glPopMatrix();
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
