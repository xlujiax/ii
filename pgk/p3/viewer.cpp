#include "viewer.hpp"

void viewer::init_program()
{
  std::vector<GLuint> shaderList;

  shaderList.push_back(LoadShader(GL_VERTEX_SHADER, "shaders/sh.vert"));
  shaderList.push_back(LoadShader(GL_FRAGMENT_SHADER, "shaders/sh.frag"));

  theProgram = CreateProgram(shaderList);
}

const float vertexPositions[] = {
  0.75f, 0.75f, 0.0f, 1.0f,
  0.75f, -0.75f, 0.0f, 1.0f,
  -0.75f, -0.75f, 0.0f, 1.0f,
};

void viewer::init_vbo()
{
  glGenBuffers(1, &positionBufferObject);

  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
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

  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);
  glUseProgram(0);
}

void viewer::update(const float delta_time) {}
