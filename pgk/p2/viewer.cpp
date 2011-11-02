#include "viewer.hpp"

void viewer::init()
{
  model.read_from_file("monkey.obj");
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
  zoom += 0.5;
}

void viewer::mousewheeldown()
{
  zoom -= 0.5;
}

void viewer::mouseup()
{
  pressed = false;
}

void viewer::mousedown(const float x, const float y)
{
  pressed = true;
}

void viewer::mousemotion(const float x, const float y)
{
  if(pressed)
  {

  }
}

void viewer::keydown(const char k)
{
  
}

void viewer::keyup(const char k)
{
  
}
