/**
 * Programa que dibuja una circulo utilizando el algoritmo
 * del punto medio para el trazado de circulos.
 *
 * Compilacion:
 * gcc Circle.c -o Circle -lGL -lGLU -lglut -lm
 * 
 * Ejecucion:
 * ./Circle
 *
 * Uso:
 * Da click en cualquier parte de la pantalla y arrastra
 * el mouse para dibujar una circulo.
 *
 * Autor:
 * Romario Ramirez Calderon 1214462c
 *
 */

#include <GL/glut.h>
#include <math.h>

/**
 * Inicia el proceso de renderizado y llama a la funcion
 * que dibuja el circulo.
 */
void display();

/**
 * Establece el punto del centro del circulo cuando
 * el usuario presiona el boton del raton.
 */
void mouseHandler(int button, int state, int x, int y);

/**
 * Establece el radio del circulo a partir del punto recibido
 * cuando el usuario arrastra el raton.
 */
void mouseMotionHandler(int x, int y);

/**
 * Dibuja el circulo con el punto del centro y el radio dados.
 */
void drawCircle(int x, int y, int r);

/**
 * Dimensiones de la ventana
 */
const int WIDTH = 600, HEIGHT = 600;

/**
 * Punto central y radio del circulo
 */
int xc, yc, rc;
  
int main()
{
  int a;
  glutInit(&a, NULL);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Algoritmo del punto medio para circulos");

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
    drawCircle(xc, yc, rc);
  glEnd();

  glFlush();
}

void mouseHandler(int button, int state, int x, int y)
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    xc = x;
    /*
      La funcion recibe la posicion verical medida desde arriba de la ventana
      pero la ventana mide la posicion vertical desde abajo de la ventana,
      por lo tanto la posicion en la ventana es: HEIGHT - y.
     */
    yc = HEIGHT - y;

    rc = 0;
  }

  // Repinta la ventana
  glutPostRedisplay();
}

void mouseMotionHandler(int x, int y)
{
  y = HEIGHT - y;
  // Obtiene el radio a partir de la distancia entre centro
  // y el nuevo punto
  rc = (int) sqrt( (x - xc)*(x - xc) + (y - yc)*(y - yc) );

  // Repinta la ventana
  glutPostRedisplay();
}

void drawCircle(int x0, int y0, int r)
{
  int x = 0, y = r, p = 1 - r;

  // Dibuja los puntos iniciales 
  glVertex2i(x0, y0 + r);
  glVertex2i(x0 + r, y0);
  glVertex2i(x0 - r, y0);
  glVertex2i(x0, y0 - r);

  while(x < y) {
    x++;
    p += p < 0 ? 2*x + 1 : 2*x + 1 - 2*(--y);

    glVertex2i(x0 + x, y0 + y);
    glVertex2i(x0 - x, y0 + y);
    glVertex2i(x0 + x, y0 - y);
    glVertex2i(x0 - x, y0 - y);
    
    glVertex2i(x0 + y, y0 + x);
    glVertex2i(x0 - y, y0 + x);
    glVertex2i(x0 + y, y0 - x);
    glVertex2i(x0 - y, y0 - x);
  }
}
