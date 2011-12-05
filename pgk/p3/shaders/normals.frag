#version 330
uniform vec3 light;

smooth in vec3 normal;

out vec4 outputColor;

void main()
{
  float d = dot(normal, light);
  outputColor = vec4(d,d,d,d);
}
