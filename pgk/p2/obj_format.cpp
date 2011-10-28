#include "obj_format.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct vertex
{
  float x, y, z;
  float nx, ny, nz; // normal
  float u, v;       // texture
};

GLuint vertices_vbo;
GLuint indices_vbo;

GLuint num_vertices;
GLuint num_indices;
vertex* vertices;
GLuint* indices;

void obj_format::read_from_file(const char* filename)
{
  num_vertices = 8;
  vertices = new vertex[num_vertices];
  vertices[0] = { -1, -1, -1, -1, -1, -1 };
  vertices[1] = {  1, -1, -1,  1, -1, -1 };
  vertices[2] = {  1,  1, -1,  1,  1, -1 };
  vertices[3] = { -1,  1, -1, -1,  1, -1 };
  vertices[4] = { -1, -1,  1, -1, -1,  1 };
  vertices[5] = {  1, -1,  1,  1, -1,  1 };
  vertices[6] = {  1,  1,  1,  1,  1,  1 };
  vertices[7] = { -1,  1,  1, -1,  1,  1 };

  num_indices = 6;
  indices = new GLuint[num_indices*4];
  indices[0]  = 0;
  indices[1]  = 1;
  indices[2]  = 2;
  indices[3]  = 3;

  indices[4]  = 4;
  indices[5]  = 5;
  indices[6]  = 6;
  indices[7]  = 7;

  indices[8]  = 0;
  indices[9]  = 1;
  indices[10] = 5;
  indices[11] = 4;

  indices[12] = 0;
  indices[13] = 3;
  indices[14] = 7;
  indices[15] = 4;

  indices[16] = 3;
  indices[17] = 2;
  indices[18] = 6;
  indices[19] = 7;

  indices[20] = 1;
  indices[21] = 2;
  indices[22] = 6;
  indices[23] = 5;

  glGenBuffers(1, &vertices_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(vertex), vertices, GL_STATIC_DRAW);
  delete []vertices;

  glGenBuffers(1, &indices_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * 4 * sizeof(GLuint), indices, GL_STATIC_DRAW);

  delete []indices;
}

void obj_format::draw() const
{
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(vertex), BUFFER_OFFSET(0));

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, sizeof(vertex), BUFFER_OFFSET(3 * sizeof(float)));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);
  glDrawElements(GL_QUADS, num_indices * 4, GL_UNSIGNED_INT, 0);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  assert(glGetError() == GL_NO_ERROR);
}
