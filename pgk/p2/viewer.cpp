#include "viewer.hpp"

void viewer::init()
{
  model.read_from_file("figure.obj");
  pressed = false;

  zoom = -4.0;
  r1 = 50.0;
  r2 = -30.0;
  r3 = 11.0;
}

void viewer::animate(float)
{
}

void viewer::draw() const
{
  glPushMatrix();
  glTranslatef(0.0, 0.0, zoom);
  glRotatef(r1, 1.0, 0.0, 0.0);
  glRotatef(r2, 0.0, 1.0, 0.0);
  glRotatef(r3, 0.0, 0.0, 1.0);

  model.draw();
  glPopMatrix();
}

void viewer::mousewheelup()
{
  zoom += 0.1;
}

void viewer::mousewheeldown()
{
  zoom -= 0.1;
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
  {
    r2 += 0.5 * xrel;
    r1 += 0.5 * yrel;

    printf("mouse: (%f, %f), d(%f, %f)\n", x, y, xrel, yrel);
  }
}

void viewer::keydown(const char k)
{
  
}

void viewer::keyup(const char k)
{
  
}
