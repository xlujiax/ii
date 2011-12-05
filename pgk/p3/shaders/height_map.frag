#version 330

smooth in float height;

out vec4 outputColor;

void main()
{
  float h = height + 0.3;
  outputColor = vec4(h,h,h,h);
}
