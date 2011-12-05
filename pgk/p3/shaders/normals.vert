#version 330

layout(location = 0) in vec4 position;

uniform mat4 perspectiveMatrix;
uniform mat4 translationMatrix;
uniform mat4 rotationXMatrix;
uniform mat4 rotationYMatrix;
uniform mat4 rotationZMatrix;

out vec4 orig_position;

void main()
{
  orig_position = position;
  
  gl_Position =
    perspectiveMatrix *
    rotationXMatrix *
    rotationYMatrix *
    rotationZMatrix *
    translationMatrix *
    position;
}
