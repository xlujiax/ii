#include "obj_format.hpp"

GLuint vboId1;
GLuint vboId2;
GLuint vCount;
GLfloat* vertices;
GLuint* indices;

void obj_format::read_from_file(const char* filename)
{
  vCount = 8;
  vertices = new GLfloat[vCount*3];
  vertices[0] = -1;
  vertices[1] = -1;
  vertices[2] = -1;
  
  vertices[3] =  1;
  vertices[4] = -1;
  vertices[5] = -1;
  
  vertices[6] =  1;
  vertices[7] =  1;
  vertices[8] = -1;
  
  vertices[9] = -1;
  vertices[10] =  1;
  vertices[11] = -1;
  
  vertices[12] = -1;
  vertices[13] = -1;
  vertices[14] =  1;
  
  vertices[15] =  1;
  vertices[16] = -1;
  vertices[17] =  1;
  
  vertices[18] =  1;
  vertices[19] =  1;
  vertices[20] =  1;
  
  vertices[21] = -1;
  vertices[22] =  1;
  vertices[23] =  1;

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

  glGenBuffersARB(1, &vboId1);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId1);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, 8 * 3 * sizeof(float), vertices, GL_STATIC_DRAW_ARB);
  delete []vertices;

  glGenBuffersARB(1, &vboId1);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vboId1);
  glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 6 * 4 * sizeof(GLuint), indices, GL_STATIC_DRAW_ARB);
  delete []indices;
}

void obj_format::draw() const
{
  printf("step0\n");

  // bind VBOs for vertex array and index array
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId1);         // for vertex coordinates
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vboId2); // for indices

  printf("step2\n");
  // do same as vertex array except pointer
  glEnableClientState(GL_INDEX_ARRAY);             // activate vertex coords array
  glVertexPointer(3, GL_FLOAT, 0, 0);               // last param is offset, not ptr

  printf("step3\n");
  // draw 6 quads using offset of index array
  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, 0);

  printf("step4\n");
  glDisableClientState(GL_VERTEX_ARRAY);            // deactivate vertex array

  printf("step5\n");
  // bind with 0, so, switch back to normal pointer operation
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
  printf("step6\n");
}
