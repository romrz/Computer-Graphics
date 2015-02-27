#include <GL/glut.h>

#define WIDTH 600
#define HEIGHT 600

void init();
void display();
void drawPoint(int x, int y);

int main(int argc, char *argv[])
{

  glutInit(&argc, argv);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow(argv[1]);

  glutDisplayFunc(display);

  init();

  glutMainLoop();

  return 0;
}

void init()
{
  glClearColor(1, 1, 1, 0);
  gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  drawPoint(WIDTH / 2, HEIGHT / 2);

  glFlush();
}


void drawPoint(int x, int y)
{
  glColor3f(1, 0, 0);
  glPointSize(10);

  glBegin(GL_POINTS);
    glVertex2i(x, y);
  glEnd();
}
