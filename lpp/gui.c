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

void demo_parabola()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(sample_bezier_parabola());
}

void demo_parabola_subrange()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(bezier_subrange(sample_bezier_parabola(), 0.3f, 0.7f));
}

void demo_parabola_split()
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

void demo_parabola_two_subranges()
{
  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(bezier_subrange(sample_bezier_parabola(), 0.3f, 0.4f));
  graphs[1] = graph_create(bezier_subrange(sample_bezier_parabola(), 0.5f, 0.7f));
}

void demo_sinus()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(sample_bezier_sinus(10));
  graphs[0]->draw_roots = 0;
}

void demo_cosinus()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(sample_bezier_cosinus(10));
  graphs[0]->draw_roots = 0;
}

void demo_sinus_reduction()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(
    bezier_degree_reduction_rec(sample_bezier_sinus(10), 2));
  //graphs[0]->draw_roots = 0;
}

void demo_cosinus_reduction()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(
    bezier_degree_reduction_rec(sample_bezier_cosinus(10), 2));
  //graphs[0]->draw_roots = 0;
}

void init()
{
  //demo_parabola();
  //demo_parabola_subrange();
  //demo_parabola_two_subranges();
  //demo_parabola_split();
  //demo_sinus();
  //demo_cosinus();
  //demo_sinus_reduction();
  demo_cosinus_reduction();
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
