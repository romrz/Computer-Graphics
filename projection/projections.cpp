#include <GL/glut.h>
#include "Matrix.h"
#include <iostream>
#include <cmath>

using namespace std;

void display();
void onMotion(int x, int y);

const int WIDTH = 1200, HEIGHT = 700;

class Cube
{
 private:
  Point vertices[8];
  Point position;
  float size;

  Matrix rotation;

  void calculateVertices()
  {
    vertices[0] = position + Point(-size, -size, size);
    vertices[1] = position + Point(-size, size, size);
    vertices[2] = position + Point(size, size, size);
    vertices[3] = position + Point(size, -size, size);
    vertices[4] = position + Point(-size, -size, 2*size);
    vertices[5] = position + Point(-size, size, 2*size);
    vertices[6] = position + Point(size, size, 2*size);
    vertices[7] = position + Point(size, -size, 2*size);
  }

  void normalize()
  {
    for(int i = 0; i < 8; i++)
      vertices[i].normalize();
  }
  
 public:
  Cube(Point p, float sz)
  {
    position = p;
    size = sz;
    calculateVertices();
    rotation = Matrix(4,4);
    rotate(0, 0);
  }

  void setPosition(Point p)
  {
    position = p;
    calculateVertices();
  }

  void rotate(float x, float y)
  {
    rotation.at(0,0) = cos(x);
    rotation.at(0,1) = -sin(x);
    rotation.at(1,0) = sin(x);
    rotation.at(1,1) = cos(x);
    rotation.at(2,2) = 1;
    rotation.at(3,3) = 1;
  }
  
  Point getPosition()
  {
    return position;
  }
  
  void applyPerspective(Matrix& perspective)
  {
    for(int i = 0; i < 8; i++)
      vertices[i] = perspective * vertices[i];
    normalize();
  }

  void draw()
  {
    for(int i = 0; i < 8; i++)
      vertices[i] = rotation * vertices[i];
    
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 4; i++)
      glVertex2f(vertices[i].x, vertices[i].y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    for(int i = 4; i < 8; i++)
      glVertex2f(vertices[i].x, vertices[i].y);
    glEnd();

    glBegin(GL_LINES);
    for(int i = 0; i < 4; i++){
      glVertex2f(vertices[i].x, vertices[i].y);
      glVertex2f(vertices[i+4].x, vertices[i+4].y);
    }
    glEnd();
  }
};

Cube cube(Point(0, 0, 100), 100);
Matrix p(4, 4);

int rx = 0;

int main(int argc, char *args[])
{
  glutInit(&argc, args);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Projections");

  glutDisplayFunc(display);
  glutMotionFunc(onMotion);
  
  glClearColor(0, 0, 0, 0);

  float r = -WIDTH/2.0f;
  float l = WIDTH/2.0f;
  float t = HEIGHT/2.0f;
  float b = -HEIGHT/2.0f;
  float n = -100;
  float f = -500;

  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      p.at(i, j) = 0;
  
  p.at(0,0) = (2*n)/(r-l);
  p.at(0,2) = (r+l)/(r-l);
  p.at(1,1) = (2*n)/(t-b);
  p.at(1,2) = (t+b)/(t-b);
  p.at(2,2) = -(f+n)/(f-n);
  p.at(2,3) = -(2*f*n)/(f-n);
  p.at(3,2) = -1;
  
  glutMainLoop();
  return 0;
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1, 0, 0);

  cube.rotate(rx,0);
  cube.applyPerspective(p);
  cube.draw();

  glFlush();
}

void onMotion(int x, int y)
{
  /*
  x = -WIDTH/2 + x;
  y = -HEIGHT/2 + y;
  cube.setPosition(Point(x, y, cube.getPosition().z));
  */
  rx = 1;
  glutPostRedisplay();
}
