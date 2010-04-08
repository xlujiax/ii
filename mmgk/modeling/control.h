#ifndef CONTROL_H
#define CONTROL_H

#include <GL/gl.h>

#include <malloc.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
  float (*pts)[2];
  int n;
} control;

control* control_create(float (*)[2], int);
void control_destroy(control*);

void control_push(control*, float[2]);
int control_erase(control*, float[2]);

void control_write(control*, FILE*);
control* control_read(FILE*);

void control_draw_points(control*);
void control_draw_line(control*);

void control_test();

#endif
