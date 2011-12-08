#version 330 compatibility
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;
                  
out vec3 normal;
in vec4 orig_position[3];

void main()
{
  vec3 a = normalize(orig_position[0].xyz - orig_position[1].xyz);
  vec3 b = normalize(orig_position[1].xyz - orig_position[2].xyz);
  normal = normalize(cross(a,b));
  for(int i=0; i<3; i++)
  {
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
  }
  EndPrimitive();
}
