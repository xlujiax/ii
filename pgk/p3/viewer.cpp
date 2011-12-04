#include "viewer.hpp"

void viewer::init_program()
{
  std::vector<GLuint> shaderList;

  shaderList.push_back(LoadShader(GL_VERTEX_SHADER, "shaders/sh.vert"));
  shaderList.push_back(LoadShader(GL_FRAGMENT_SHADER, "shaders/sh.frag"));

  theProgram = CreateProgram(shaderList);

  offsetUniform = glGetUniformLocation(theProgram, "offset");
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
  glUniform2f(offsetUniform, 0.5f, 0.25f);

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

void viewer::update(const float delta_time) {}
