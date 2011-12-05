#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 theColor;

uniform vec3 offset;
uniform mat4 perspectiveMatrix;
uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;

void main()
{
  vec4 cameraPos = position;

  gl_Position =
    perspectiveMatrix *
    translationMatrix *
    rotationMatrix *
    cameraPos;
  
  theColor = color;
}
