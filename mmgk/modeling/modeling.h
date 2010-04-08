#ifndef MODELING_H
#define MODELING_H

extern int main_menu;
extern int mouse_x;
extern int mouse_y;
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
