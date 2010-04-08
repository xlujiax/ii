#ifndef MODELING_H
#define MODELING_H

#include <GL/glut.h>
#include <stdio.h>

#include "ncs.h"
#include "control.h"

extern int main_menu;
extern float mouse_x;
extern float mouse_y;
extern int window_width;
extern int window_height;

void create();
void destroy();
void frame();
void mouse_click(int, int, int, int);
void mouse_motion(int, int);
void mouse_passive_motion(int, int);
void open_menu(int);
void create_menu();

#endif
