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
  graphs[0] = graph_create(sample_bezier_sinus(10, 3.1415f));
  graphs[0]->draw_roots = 0;
}

void demo_cosinus()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(sample_bezier_cosinus(10, 3.1415f));
  graphs[0]->draw_roots = 0;
}

void demo_sinus_reduction(int n, int freq)
{
  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(
    bezier_degree_reduction_rec(sample_bezier_sinus(10, freq), 2));
  graphs[1] = graph_create(sample_bezier_sinus(n, freq));
  graphs[1]->color_r = 0.0f;
  graphs[1]->color_g = 0.0f;
  graphs[1]->color_b = 1.0f;
  graphs[1]->draw_roots = 0;
}

void demo_cosinus_reduction(int n, int freq)
{
  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(
    bezier_degree_reduction_rec(sample_bezier_cosinus(10, freq), 2));
  graphs[1] = graph_create(sample_bezier_cosinus(n, freq));
  graphs[1]->color_r = 0.0f;
  graphs[1]->color_g = 0.0f;
  graphs[1]->color_b = 1.0f;
  graphs[1]->draw_roots = 0;
}

void demo_bounds()
{
  const int deg = 10;
  Bezier* original = sample_bezier_cosinus(deg, 7.0f);
  Bezier* reduced_and_raised = bezier_degree_reduction_rec(original, 2);
  bezier_degree_raise(reduced_and_raised, deg);

  float difference = bezier_max_coeff_diff(original, reduced_and_raised);
  Bezier* reduced_up = bezier_degree_reduction_rec(original, 2);
  bezier_inc_coeffs(reduced_up, difference);
  Bezier* reduced_down = bezier_degree_reduction_rec(original, 2);
  bezier_inc_coeffs(reduced_down, -difference);

  num_graphs = 4;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(original);
  graphs[0]->draw_roots = 0;
  graphs[1] = graph_create(reduced_and_raised);
  graphs[1]->draw_roots = 0;
  graphs[1]->color_r = 0.5f;
  graphs[1]->color_g = 0.5f;
  graphs[1]->color_b = 0.5f;

  graphs[2] = graph_create(reduced_up);
  graphs[2]->color_r = 0.5f;
  graphs[2]->color_g = 1.0f;
  graphs[2]->color_b = 0.5f;

  graphs[3] = graph_create(reduced_down);
  graphs[3]->color_r = 0.5f;
  graphs[3]->color_g = 1.0f;
  graphs[3]->color_b = 0.5f;
}

void demo_reduced_and_raised()
{
  const int deg = 10;
  Bezier* original = sample_bezier_cosinus(deg, 7.0f);
  Bezier* reduced_and_raised = bezier_degree_reduction_rec(original, 2);
  bezier_degree_raise(reduced_and_raised, deg);

  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(original);
  graphs[0]->draw_roots = 0;
  graphs[1] = graph_create(reduced_and_raised);
  graphs[1]->draw_roots = 0;
  graphs[1]->color_r = 0.5f;
  graphs[1]->color_g = 0.5f;
  graphs[1]->color_b = 0.5f;
}

void init()
{
  //demo_parabola();
  //demo_parabola_subrange();
  //demo_parabola_two_subranges();
  //demo_parabola_split();
  //demo_sinus();
  //demo_cosinus();

  //demo_sinus_reduction(10, 3.1415f);
  //demo_cosinus_reduction(10, 3.1415f);
  //demo_sinus_reduction(30, 3.1415f);
  //demo_cosinus_reduction(30, 3.1415f);
  
  //demo_sinus_reduction(10, 50.0f);
  //demo_cosinus_reduction(10, 50.0f);
  //demo_sinus_reduction(30, 50.0f);
  //demo_cosinus_reduction(30, 50.0f);

  //demo_reduced_and_raised();
  demo_bounds();
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
