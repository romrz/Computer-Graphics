/**
 * Programa que dibuja una elipse utilizando el algoritmo
 * del punto medio para el trazado de elipses.
 *
 * Compilacion:
 * gcc Ellipse.c -o Ellipse -lGL -lGLU -lglut -lm
 * 
 * Ejecucion:
 * ./Ellipse
 *
 * Uso:
 * Da click en cualquier parte de la pantalla y arrastra
 * el mouse para dibujar una elipse.
 *
 * Autor:
 * Romario Ramirez Calderon 1214462c
 *
 */

#include <GL/glut.h>
#include <math.h>

/**
 * Inicia el proceso de renderizado y llama a la funcion
 * que dibuja la elipse.
 */
void display();

/**
 * Establece el punto del centro de la elipse cuando
 * el usuario presiona el boton del raton.
 */
void mouseHandler(int button, int state, int x, int y);

/**
 * Establece el radio x & y a partir del punto recibido
 * cuando el usuario arrastra el raton.
 */
void mouseMotionHandler(int x, int y);

/**
 * Dibuja la elipse
 */
void drawEllipse(int x, int y, int rx, int ry);

/**
 * Dimensiones de la ventana
 */
const int WIDTH = 600, HEIGHT = 600;

/**
 * Punto central y radio del circulo
 */
int X, Y, RX, RY;
  
int main()
{
  int a;
  glutInit(&a, NULL);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Algoritmo del punto medio para elipses");

  glutDisplayFunc(display);
  glutMouseFunc(mouseHandler);
  glutMotionFunc(mouseMotionHandler);
  
  glClearColor(1, 1, 1, 0);

  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0, WIDTH, 0, HEIGHT);

  glutMainLoop();

  return 0;
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1, 0, 0);

  glBegin(GL_POINTS);
    drawEllipse(X, Y, RX, RY);
  glEnd();

  glFlush();
}

void mouseHandler(int button, int state, int x, int y)
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    X = x;
    Y = HEIGHT - y;
    RX = RY = 0;
  }

  // Repinta la ventana
  glutPostRedisplay();
}

void mouseMotionHandler(int x, int y)
{
  y = HEIGHT - y;
  // Obtiene los radios x & y
  RX = abs(x - X);
  RY = abs(y - Y);

  // Repinta la ventana
  glutPostRedisplay();
}

void drawEllipse(int x0, int y0, int rx, int ry)
{
  /**
   * Se utiliza el tipo de dato long ya que hay problemas con int
   * cuando la elipse es grande
   */
  long x = 0, y = ry;
  long rx2 = rx * rx, ry2 = ry * ry;
  long twoRx2 = 2 * rx2, twoRy2 = 2 * ry2;
  long p = round(ry2 - rx2 * ry + rx2 * 0.25);

  // Dibuja los puntos iniciales
  glVertex2i(x0, y0 + ry);
  glVertex2i(x0, y0 - ry);
  
  while(twoRy2 * x < twoRx2 * y) {
    x++;
    
    if(p < 0)
      p += twoRy2 * x + ry2;
    else
      p += twoRy2 * x + ry2 - twoRx2 * (--y);

    glVertex2i(x0 + x, y0 + y);
    glVertex2i(x0 - x, y0 + y);
    glVertex2i(x0 + x, y0 - y);
    glVertex2i(x0 - x, y0 - y);
  }
  
  p = round(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2);

  while(y > 0) {
    y--;
    
    if(p > 0)
      p += -twoRx2 * y + rx2;
    else
      p += twoRy2 * (++x) - twoRx2 * y + rx2;

    glVertex2i(x0 + x, y0 + y);
    glVertex2i(x0 - x, y0 + y);
    glVertex2i(x0 + x, y0 - y);
    glVertex2i(x0 - x, y0 - y);
  }
}
