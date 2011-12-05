#include "viewer.hpp"

std::array<float, 16> viewer::perspective_matrix() const
{
  float fov = 60;
  float aspect = 1;
  float znear = 1;
  float zfar = 100;
  float xymax = znear * tan(fov * 3.1415 / 360.0);
  float ymin = -xymax;
  float xmin = -xymax;

  float width = xymax - xmin;
  float height = xymax - ymin;

  float depth = zfar - znear;
  float q = -(zfar + znear) / depth;
  float qn = -2 * (zfar * znear) / depth;

  float w = 2 * znear / width;
  w = w / aspect;
  float h = 2 * znear / height;

  std::array<float, 16> m;
  m[0]  = w;
  m[1]  = 0;
  m[2]  = 0;
  m[3]  = 0;

  m[4]  = 0;
  m[5]  = h;
  m[6]  = 0;
  m[7]  = 0;

  m[8]  = 0;
  m[9]  = 0;
  m[10] = q;
  m[11] = -1;

  m[12] = 0;
  m[13] = 0;
  m[14] = qn;
  m[15] = 0;
  return m;
}

std::array<float, 16> viewer::translation_matrix() const
{
  std::array<float, 16> m;
  m.fill(0.0f);
  m[0] = 1.0f;
  m[5] = 1.0f;
  m[10] = 1.0f;
  m[15] = 1.0f;
  
  m[12] = offx;
  m[13] = offy;
  m[14] = offz;
  
  return m;
}

std::array<float, 16> viewer::rotation_x_matrix() const
{
  const float c = cosf(rot_x);
  const float s = sinf(rot_x);
  std::array<float, 16> m;
  m.fill(0.0f);
  m[0] = 1.0f;
  m[5] = c; m[6] = s;
  m[9] = -s; m[10] = c;
  m[15] = 1.0f;
  
  return m;
}

std::array<float, 16> viewer::rotation_y_matrix() const
{
  const float c = cosf(rot_y);
  const float s = sinf(rot_y);
  std::array<float, 16> m;
  m.fill(0.0f);
  m[0] = c;
  m[2] = -s;
  m[5] = 1;
  m[8] = s;
  m[10] = c;
  m[15] = 1.0f;
  
  return m;
}

std::array<float, 16> viewer::rotation_z_matrix() const
{
  const float c = cosf(rot_z);
  const float s = sinf(rot_z);
  std::array<float, 16> m;
  m.fill(0.0f);
  m[0] = c;
  m[1] = s;
  m[4] = -s;
  m[5] = c;
  m[10] = 1.0f;
  m[15] = 1.0f;
  
  return m;
}

void viewer::init_program()
{
  offx = 0.35f;
  offy = -0.0f;
  offz = -2.5f;
  rot_x = 0.0f;
  rot_y = 0.0f;
  rot_z = 0.0f;

  mouse_move_x = 0;
  mouse_move_y = 0;
  last_mouse_x = 0;
  last_mouse_y = 0;
  mouse_click = false;

  std::vector<GLuint> shaderList;

  shaderList.push_back(LoadShader(GL_VERTEX_SHADER, "shaders/sh.vert"));
  shaderList.push_back(LoadShader(GL_FRAGMENT_SHADER, "shaders/sh.frag"));

  theProgram = CreateProgram(shaderList);

  perspectiveMatrixUnif = glGetUniformLocation(theProgram, "perspectiveMatrix");
  translationMatrixUnif = glGetUniformLocation(theProgram, "translationMatrix");
  rotationXMatrixUnif = glGetUniformLocation(theProgram, "rotationXMatrix");
  rotationYMatrixUnif = glGetUniformLocation(theProgram, "rotationYMatrix");
  rotationZMatrixUnif = glGetUniformLocation(theProgram, "rotationZMatrix");

  glUseProgram(theProgram);
  glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, &perspective_matrix()[0]);
  glUseProgram(0);
}

void viewer::init_vbo()
{
  glGenBuffers(1, &vertexBufferObject);

  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CW);
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
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(theProgram);
  glUniformMatrix4fv(translationMatrixUnif, 1, GL_FALSE, &translation_matrix()[0]);
  glUniformMatrix4fv(rotationXMatrixUnif, 1, GL_FALSE, &rotation_x_matrix()[0]);
  glUniformMatrix4fv(rotationYMatrixUnif, 1, GL_FALSE, &rotation_y_matrix()[0]);
  glUniformMatrix4fv(rotationZMatrixUnif, 1, GL_FALSE, &rotation_z_matrix()[0]);

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
  if(keydown('w'))
  {
    offx -= cosf(rot_x) * sinf(rot_y) * speed * delta_time;
    offz += cosf(rot_x) * cosf(rot_y) * speed * delta_time;
    offy += sinf(rot_x) * speed * delta_time;
  }
  if(keydown('s'))
  {
    offx += cosf(rot_x) * sinf(rot_y) * speed * delta_time;
    offz -= cosf(rot_x) * cosf(rot_y) * speed * delta_time;
    offy -= sinf(rot_x) * speed * delta_time;
  }

  if(keydown('a'))
  {
    offx += cosf(rot_y) * speed * delta_time;
    offz += sinf(rot_y) * speed * delta_time;
  }
  if(keydown('d'))
  {
    offx -= cosf(rot_y) * speed * delta_time;
    offz -= sinf(rot_y) * speed * delta_time;
  }

  const float rot_speed = 0.0005;
  if(keydown('q')) rot_y -= rot_speed * delta_time;
  if(keydown('e')) rot_y += rot_speed * delta_time;
  if(keydown('z')) rot_x -= rot_speed * delta_time;
  if(keydown('x')) rot_x += rot_speed * delta_time;
  if(keydown('c')) rot_z -= rot_speed * delta_time;
  if(keydown('v')) rot_z += rot_speed * delta_time;

  if(mouse_click)
  {
    const float mouse_rot_speed = 0.001;
    rot_y += mouse_move_x * mouse_rot_speed * delta_time;
    rot_x += mouse_move_y * mouse_rot_speed * delta_time;
  }
}

void viewer::mousemotion(const float x, const float y)
{
  if(mouse_click)
  {
    mouse_move_x = x - last_mouse_x;
    mouse_move_y = y - last_mouse_y;

    const float tolerance = 0.1;
    if(fabs(mouse_move_x) < tolerance)
      mouse_move_x = 0;
    if(fabs(mouse_move_y) < tolerance)
      mouse_move_y = 0;
  }
}

void viewer::mousedown(const float x, const float y)
{
  last_mouse_x = x;
  last_mouse_y = y;
  mouse_click = true;
}

void viewer::mouseup()
{
  mouse_click = false;
}
