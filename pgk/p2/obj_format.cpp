#include "obj_format.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct vertex
{
  float x, y, z;
  float nx, ny, nz; // normal
};

GLuint vertices_vbo;
GLuint indices_vbo;

GLuint num_vertices;
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

  indices = new GLuint[6*4];
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

  glGenBuffersARB(1, &vertices_vbo);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertices_vbo);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, 8 * sizeof(vertex), vertices, GL_STATIC_DRAW_ARB);
  delete []vertices;

  glGenBuffersARB(1, &indices_vbo);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, indices_vbo);
  glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 6 * 4 * sizeof(GLuint), indices, GL_STATIC_DRAW_ARB);
  delete []indices;
}

void obj_format::draw() const
{
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertices_vbo);
  glEnableClientState(GL_INDEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(vertex), BUFFER_OFFSET(0));
  glNormalPointer(3, sizeof(vertex), BUFFER_OFFSET(3 * sizeof(float)));

  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, indices_vbo);
  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, 0);

  glDisableClientState(GL_INDEX_ARRAY);

  // bind with 0, so, switch back to normal pointer operation
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
}
