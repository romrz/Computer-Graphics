#include <GL/glut.h>

void createWindow(char *title, int width, int height)
{
  int a;
  glutInit(&a, NULL);
  glutInitWindowSize(width, height);
  glutCreateWindow(title);

  glClearColor(1, 1, 1, 0);
  gluOrtho2D(0, width, 0, height);

}
