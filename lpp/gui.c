#include "init.h"

#include "bezier.h"
#include "graph.h"
#include "reduction.h"
#include "quadclip.h"
#include "samples.h"
#include "interval.h"

const float mouse_size = 20;

float* move_mod_x = 0;
float* move_mod_y = 0;

Graph** graphs = 0;
int num_graphs = 0;

Interval** intervals = 0;
int num_intervals = 0;

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

void demo_bounds_with_intervals1()
{
  const int deg = 3;
  Bezier* original = bezier_create(deg);
  original->c[0] = 0.2;
  original->c[1] = 0.1;
  original->c[2] = 0.1;
  original->c[3] = -0.1;
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

  num_intervals = bezier_intervals_between(reduced_up, reduced_down, &intervals);
}

void demo_bounds_with_intervals2()
{
  const int deg = 3;
  Bezier* original = bezier_create(deg);
  original->c[0] = -0.2;
  original->c[1] = 0.1;
  original->c[2] = 0.1;
  original->c[3] = -0.1;
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

  num_intervals = bezier_intervals_between(reduced_up, reduced_down, &intervals);
}


void demo_bounds_with_intervals3()
{
  const int deg = 3;
  Bezier* original = bezier_create(deg);
  original->c[0] = 0.2;
  original->c[1] = -0.1;
  original->c[2] = -0.1;
  original->c[3] = 0.1;
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

  num_intervals = bezier_intervals_between(reduced_up, reduced_down, &intervals);
}


void demo_bounds_with_intervals4()
{
  const int deg = 3;
  Bezier* original = bezier_create(deg);
  original->c[0] = 0.2;
  original->c[1] = 0.1;
  original->c[2] = -0.1;
  original->c[3] = 0.2;
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

  num_intervals = bezier_intervals_between(reduced_up, reduced_down, &intervals);
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

void demo_intervals1()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(sample_bezier_parabola());

  num_intervals = bezier_above(graphs[0]->bezier, &intervals);
}

void demo_intervals2()
{
  Bezier* b = sample_bezier_parabola();
  bezier_inc_coeffs(b, -0.35f);
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  num_intervals = bezier_above(b, &intervals);
}

void demo_intervals3()
{
  Bezier* b = sample_bezier_parabola();
  b->c[2] = -0.1f;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  num_intervals = bezier_above(b, &intervals);
}

void demo_intervals4()
{
  Bezier* b = sample_bezier_parabola();
  bezier_inc_coeffs(b, 0.4f);
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  num_intervals = bezier_above(b, &intervals);
}

void demo_intervals5()
{
  Bezier* b = sample_bezier_parabola();
  bezier_inc_coeffs(b, -0.5f);
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  num_intervals = bezier_above(b, &intervals);
}

void demo_intervals6()
{
  Bezier* b = bezier_create(2);
  b->c[0] = -0.2;
  b->c[1] = 0.4;
  b->c[2] = -0.2;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  num_intervals = bezier_above(b, &intervals);
}

void demo_intervals7()
{
  Bezier* b = bezier_create(2);
  b->c[0] = 0.2;
  b->c[1] = 0.4;
  b->c[2] = -0.2;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  num_intervals = bezier_above(b, &intervals);
}

void demo_quadclip1()
{
  Bezier* b = sample_bezier_sinus(7, 30);
  b->c[0] = 0.1;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);
  graphs[0]->draw_roots = 0;

  num_intervals = bezier_quadclip(b, &intervals, 0.001f);

  printf("Found %d roots\n", num_intervals);
  for(int i = 0; i < num_intervals; ++i)
  {
    printf("[%f %f]\n", intervals[i]->a, intervals[i]->b);
  }
}

void demo_quadclip2()
{
  Bezier* b = sample_bezier_cosinus(7, 30);
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);
  graphs[0]->draw_roots = 0;

  num_intervals = bezier_quadclip(b, &intervals, 0.001f);

  printf("Found %d roots\n", num_intervals);
  for(int i = 0; i < num_intervals; ++i)
  {
    printf("[%f %f]\n", intervals[i]->a, intervals[i]->b);
  }
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
  //demo_bounds();

  //demo_intervals1();
  //demo_intervals2();
  //demo_intervals3();
  //demo_intervals4();
  //demo_intervals5();
  //demo_intervals6();
  //demo_intervals7();

  //demo_bounds_with_intervals1();
  //demo_bounds_with_intervals2();
  //demo_bounds_with_intervals3();
  //demo_bounds_with_intervals4();

  //demo_quadclip1();
  demo_quadclip2();
}

void update()
{
}

void draw()
{
  for(int g = 0; g < num_graphs; ++g)
    graph_draw(graphs[g]);

  glColor3f(1.0f, 0.0f, 0.0f);
  glLineWidth(3.0f);
  glBegin(GL_LINES);
  
  for(int i = 0; i < num_intervals; ++i)
  {
    assert(intervals);
    assert(intervals[i]);
    assert(!interval_empty(intervals[i]));
    glVertex2f(graphs[0]->offset_x + graphs[0]->width * intervals[i]->a, graphs[0]->offset_y);
    glVertex2f(graphs[0]->offset_x + graphs[0]->width * intervals[i]->b, graphs[0]->offset_y);
  }
  glEnd();

  glBegin(GL_POINTS);
  
  for(int i = 0; i < num_intervals; ++i)
  {
    assert(intervals);
    assert(intervals[i]);
    assert(!interval_empty(intervals[i]));
    glVertex2f(graphs[0]->offset_x + graphs[0]->width * intervals[i]->a, graphs[0]->offset_y);
    glVertex2f(graphs[0]->offset_x + graphs[0]->width * intervals[i]->b, graphs[0]->offset_y);
  }
  glEnd();
glLineWidth(1.0f);

  
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
