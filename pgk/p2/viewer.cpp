#include "viewer.hpp"

void viewer::init()
{
  model.read_from_file("monkey.obj");
  pressed = false;

  zoom = -4.0;

  arc_ball_radius = 3.0;
}

void viewer::animate(float)
{
}

void viewer::draw() const
{
  glPushMatrix();
    
  glLoadIdentity();
  glMultMatrixf(&last_rot[0]);
  glTranslatef(0.0, 0.0, zoom);
  
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
  last_click = { x, y };
  pressed = true;
}

vec3 viewer::screen_to_arc(const vec2& s) const
{
  assert(-1.0 <= s.x);
  assert(s.x <= 1.0);
  assert(-1.0 <= s.y);
  assert(s.y <= 1.0);
  
  return { -s.x, s.y,
      sqrtf(arc_ball_radius*arc_ball_radius - s.length()) };
}

void viewer::mousemotion(const float x, const float y)
{
  if(pressed)
  {
    const vec2 actual_click = { x, y };
    const vec3 actual_arc = screen_to_arc(actual_click);
    const vec3 last_arc = screen_to_arc(last_click);

    const vec3 axis = vec3::cross(actual_arc, last_arc);
    const float dot = vec3::dot(actual_arc, last_arc);

    quat qrot;
    qrot.x = axis.x;
    qrot.y = axis.y;
    qrot.z = axis.z;
    qrot.w = dot;

    last_rot = multiply_matrices(last_rot, qrot.get_rotation_matrix());
    
    // use last_click
    last_click = { x, y };
  }
}

void viewer::keydown(const char k)
{
  
}

void viewer::keyup(const char k)
{
  
}
