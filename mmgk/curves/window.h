#include <GL/glut.h>

class Window
{
public:
  int width, height;

  Window(int w, int h, int argc, char** argv);
  void setKeyboardFunc(void (*func)(unsigned char key,
                                   int x, int y));
  void setMainFunc(void (*func)(void));
  void mainLoop();
};
