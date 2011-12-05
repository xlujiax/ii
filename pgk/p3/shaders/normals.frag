#version 330
uniform vec3 dir_lights[25];
uniform int num_lights;

smooth in vec3 normal;

out vec4 outputColor;

void main()
{
  float r = 0;
  float g = 0;
  float b = 0;
  for(int i = 0; i < min(num_lights, 25); ++i)
  {
    float d = dot(normalize(dir_lights[i]), normal);
    if(d > 0)
    {
      r += d;
      g += d;
      b += d;
    }
  }
  outputColor = vec4(r,g,b,1);
}
