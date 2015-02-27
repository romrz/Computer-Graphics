#include "window.h"

#define WIDTH 600
#define HEIGHT 600

void display();
void drawPoint(int x, int y);

int main()
{
  createWindow("Draw a Point", WIDTH, HEIGHT);
  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1, 0, 0);
  glPointSize(10);

  glBegin(GL_POINTS);
    drawPoint(WIDTH / 2, HEIGHT / 2);
  glEnd();
  
  glFlush();
}


void drawPoint(int x, int y)
{
    glVertex2i(x, y);
}
