#include "obj_format.hpp"

GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

GLuint vboId;                              // ID of VBO

void obj_format::read_from_file(const char* filename)
{
  /* Setup cube vertex data. */
  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

  
  // generate a new VBO and get the associated ID
  glGenBuffersARB(1, &vboId);

  // bind VBO in order to use
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

  const int dataSize = 8 * 3 * sizeof(float);
  // upload data to VBO
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, dataSize, v, GL_STATIC_DRAW_ARB);
}

void obj_format::draw() const
{
  // bind VBOs for vertex array and index array
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);         // for vertex coordinates
  //glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vboId2); // for indices

  // do same as vertex array except pointer
  glEnableClientState(GL_VERTEX_ARRAY);             // activate vertex coords array
  glVertexPointer(3, GL_FLOAT, 0, 0);               // last param is offset, not ptr

  // draw 6 quads using offset of index array
  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, 0);

  glDisableClientState(GL_VERTEX_ARRAY);            // deactivate vertex array

  // bind with 0, so, switch back to normal pointer operation
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

/*
  for (int i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
*/
}
