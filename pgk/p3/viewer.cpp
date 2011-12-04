#include "viewer.hpp"

void viewer::init_program()
{
  keys.w = keys.s = keys.a = keys.d = false;
  offx = 0.15f;
  offy = 0.15f;
  
  std::vector<GLuint> shaderList;

  shaderList.push_back(LoadShader(GL_VERTEX_SHADER, "shaders/sh.vert"));
  shaderList.push_back(LoadShader(GL_FRAGMENT_SHADER, "shaders/sh.frag"));

  theProgram = CreateProgram(shaderList);

  offsetUniform = glGetUniformLocation(theProgram, "offset");

  perspectiveMatrixUnif = glGetUniformLocation(theProgram, "perspectiveMatrix");

  float fFrustumScale = 1.0f; float fzNear = 0.5f; float fzFar = 3.0f;

  float theMatrix[16];
  memset(theMatrix, 0, sizeof(float) * 16);

  theMatrix[0] = fFrustumScale;
  theMatrix[5] = fFrustumScale;
  theMatrix[10] = (fzFar + fzNear) / (fzNear - fzFar);
  theMatrix[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);
  theMatrix[11] = -1.0f;

  glUseProgram(theProgram);
  glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, theMatrix);
  glUseProgram(0);
}

const float vertexData[] = {
  0.25f,  0.25f, 0.75f, 1.0f,
  0.25f, -0.25f, 0.75f, 1.0f,
  -0.25f,  0.25f, 0.75f, 1.0f,

  0.25f, -0.25f, 0.75f, 1.0f,
  -0.25f, -0.25f, 0.75f, 1.0f,
  -0.25f,  0.25f, 0.75f, 1.0f,

  0.25f,  0.25f, -0.75f, 1.0f,
  -0.25f,  0.25f, -0.75f, 1.0f,
  0.25f, -0.25f, -0.75f, 1.0f,

  0.25f, -0.25f, -0.75f, 1.0f,
  -0.25f,  0.25f, -0.75f, 1.0f,
  -0.25f, -0.25f, -0.75f, 1.0f,

  -0.25f,  0.25f,  0.75f, 1.0f,
  -0.25f, -0.25f,  0.75f, 1.0f,
  -0.25f, -0.25f, -0.75f, 1.0f,

  -0.25f,  0.25f,  0.75f, 1.0f,
  -0.25f, -0.25f, -0.75f, 1.0f,
  -0.25f,  0.25f, -0.75f, 1.0f,

  0.25f,  0.25f,  0.75f, 1.0f,
  0.25f, -0.25f, -0.75f, 1.0f,
  0.25f, -0.25f,  0.75f, 1.0f,

  0.25f,  0.25f,  0.75f, 1.0f,
  0.25f,  0.25f, -0.75f, 1.0f,
  0.25f, -0.25f, -0.75f, 1.0f,

  0.25f,  0.25f, -0.75f, 1.0f,
  0.25f,  0.25f,  0.75f, 1.0f,
  -0.25f,  0.25f,  0.75f, 1.0f,

  0.25f,  0.25f, -0.75f, 1.0f,
  -0.25f,  0.25f,  0.75f, 1.0f,
  -0.25f,  0.25f, -0.75f, 1.0f,

  0.25f, -0.25f, -0.75f, 1.0f,
  -0.25f, -0.25f,  0.75f, 1.0f,
  0.25f, -0.25f,  0.75f, 1.0f,

  0.25f, -0.25f, -0.75f, 1.0f,
  -0.25f, -0.25f, -0.75f, 1.0f,
  -0.25f, -0.25f,  0.75f, 1.0f,




  0.0f, 0.0f, 1.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 1.0f,

  0.0f, 0.0f, 1.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 1.0f,

  0.8f, 0.8f, 0.8f, 1.0f,
  0.8f, 0.8f, 0.8f, 1.0f,
  0.8f, 0.8f, 0.8f, 1.0f,

  0.8f, 0.8f, 0.8f, 1.0f,
  0.8f, 0.8f, 0.8f, 1.0f,
  0.8f, 0.8f, 0.8f, 1.0f,

  0.0f, 1.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 0.0f, 1.0f,

  0.0f, 1.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 0.0f, 1.0f,

  0.5f, 0.5f, 0.0f, 1.0f,
  0.5f, 0.5f, 0.0f, 1.0f,
  0.5f, 0.5f, 0.0f, 1.0f,

  0.5f, 0.5f, 0.0f, 1.0f,
  0.5f, 0.5f, 0.0f, 1.0f,
  0.5f, 0.5f, 0.0f, 1.0f,

  1.0f, 0.0f, 0.0f, 1.0f,
  1.0f, 0.0f, 0.0f, 1.0f,
  1.0f, 0.0f, 0.0f, 1.0f,

  1.0f, 0.0f, 0.0f, 1.0f,
  1.0f, 0.0f, 0.0f, 1.0f,
  1.0f, 0.0f, 0.0f, 1.0f,

  0.0f, 1.0f, 1.0f, 1.0f,
  0.0f, 1.0f, 1.0f, 1.0f,
  0.0f, 1.0f, 1.0f, 1.0f,

  0.0f, 1.0f, 1.0f, 1.0f,
  0.0f, 1.0f, 1.0f, 1.0f,
  0.0f, 1.0f, 1.0f, 1.0f,

};

void viewer::init_vbo()
{
  glGenBuffers(1, &vertexBufferObject);

  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void viewer::init()
{
  init_program();
  init_vbo();

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
}

void viewer::draw() const
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(theProgram);
  glUniform2f(offsetUniform, offx, offy);

  size_t colorData = sizeof(vertexData) / 2;
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorData);

  glDrawArrays(GL_TRIANGLES, 0, 36);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glUseProgram(0);
}

void viewer::update(const float delta_time)
{
  const float speed = 0.001;
  if(keys.w) offy += speed * delta_time;
  if(keys.s) offy -= speed * delta_time;
  if(keys.a) offx -= speed * delta_time;
  if(keys.d) offx += speed * delta_time;
}

void viewer::keydown(const char k)
{
  switch(k)
  {
    case 'w': keys.w = true; break;
    case 's': keys.s = true; break;
    case 'a': keys.a = true; break;
    case 'd': keys.d = true; break;
  }
}

void viewer::keyup(const char k)
{
  switch(k)
  {
    case 'w': keys.w = false; break;
    case 's': keys.s = false; break;
    case 'a': keys.a = false; break;
    case 'd': keys.d = false; break;
  }
}
