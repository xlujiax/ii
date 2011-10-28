#include "viewer.hpp"

void viewer::init()
{
  model.read_from_file("NoSuchFile.obj");
}

void viewer::animate(float) {}
void viewer::draw() const
{
  model.draw();
}
