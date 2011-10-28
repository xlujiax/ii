#include "obj_format.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct vertex
{
  float x, y, z;
  float nx, ny, nz; // normal
  float u, v;       // texture
};

struct vec3
{
  float x, y, z;
};

GLuint vertices_vbo;
GLuint indices_vbo;

GLuint num_vertices;
GLuint num_indices;
vertex* vertices;
GLuint* indices;
std::vector<vertex> nvs; // full vertices
std::vector<GLuint> fs; // faces (consecutive fours)

void obj_format::read_from_file(const char* filename)
{
  std::vector<vec3> vs; // vertices
  std::vector<vec3> ns; // normals

  FILE* model_file = fopen(filename, "r");
  const int line_len = 100;
  char line[line_len];
  while(fgets(line, line_len, model_file) != NULL)
  {
    if(line[0] == 'v' && line[1] == ' ')
    {
      float x,y,z;
      sscanf(line, "v %f %f %f", &x, &y, &z);
      vs.push_back({ x, y, z });
    }
    else if(line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
    {
      float x,y,z;
      sscanf(line, "vn %f %f %f", &x, &y, &z);
      ns.push_back({ x, y, z });
    }
    else if(line[0] == 'f' && line[1] == ' ')
    {
      int v[4];
      int n[4];

      sscanf(line, "f %d//%d %d//%d %d//%d %d//%d",
	&v[0], &n[0],
	&v[1], &n[1],
	&v[2], &n[2],
	&v[3], &n[3]
	     );
      for(int i = 0; i < 4; ++i)
      {
	vertex vx = {
	  vs[v[i] - 1].x, vs[v[i] - 1].y, vs[v[i] - 1].z,
	  ns[n[i] - 1].x, ns[n[i] - 1].y, ns[n[i] - 1].z,
	  0, 0
	};
       
	nvs.push_back(vx);
	fs.push_back(nvs.size() - 1);
      }
    }
  }

  // problem: now we do not share vertices, each one has its own copy in all its calls
  num_vertices = nvs.size();
  vertices = &nvs[0];
  
  num_indices = fs.size();
  indices = &fs[0];

  glGenBuffers(1, &vertices_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
  glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(vertex), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &indices_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

void obj_format::draw() const
{
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(vertex), BUFFER_OFFSET(0));

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, sizeof(vertex), BUFFER_OFFSET(3 * sizeof(float)));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);
  glDrawElements(GL_QUADS, num_indices, GL_UNSIGNED_INT, 0);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
