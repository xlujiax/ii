#include "init.h"

#include "bezier.h"
#include "graph.h"
#include "reduction.h"
#include "samples.h"

const float mouse_size = 20;

float* move_mod_x = 0;
float* move_mod_y = 0;

Graph** graphs = 0;
int num_graphs = 0;

void init()
{
  Bezier* b = sample_bezier_parabola();
  Bezier* left = 0;
  Bezier* right = 0;

  bezier_split(b, 0.5f, &left, &right);
  
  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(left);
  graphs[1] = graph_create(right);
}

void update()
{
}

void draw()
{
  for(int g = 0; g < num_graphs; ++g)
    graph_draw(graphs[g]);

  // mouse
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_STRIP);
  for(float i = 0; i < 2 * 3.1415; i += 0.1)
    glVertex2f(mouse_size * cosf(i) + getMouseX(), mouse_size * sinf(i) + getMouseY());
  glEnd();
}

void key_press(unsigned char key) {}
void mouse_move() {}
void mouse_left_click() {}
void mouse_right_click() {}
