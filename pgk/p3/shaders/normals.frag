#version 330
uniform vec3 light;

smooth in vec4 normal;

out vec4 outputColor;

void main()
{
  float d = dot(normal.xyz, light);
  outputColor = vec4(d,d,d,d);
}
