/**
 * Programa que dibuja una linea utilizando el algoritmo
 * DDA para el trazado de lineas.
 *
 * Compilacion:
 * gcc LineDDA.c -o LineDDA -lGL -lGLU -lglut
 * 
 * Ejecucion:
 * ./LineDDA
 *
 * Uso:
 * Da click en cualquier parte de la pantalla y arrastra
 * el mouse para dibujar una linea, suelta el boton del mouse
 * para crear la linea deseada.
 *
 * Autor:
 * Romario Ramirez Calderon 1214462c
 *
 */

#include <GL/glut.h>
#include <math.h>

/**
 * Dimensiones de la ventana
 */
#define WIDTH 600
#define HEIGHT 600

/**
 * Inicia el proceso de renderizado y llama a la funcion
 * que dibuja la linea.
 */
void display();

/**
 * Establece los puntos iniciales de la linea en el
 * punto en el que el usuario presiona el boton del raton.
 */
void mouseHandler(int button, int state, int x, int y);

/**
 * Establece los puntos finales mientras el usuario
 * arrastra el raton para que la linea se dibuje.
 */
void mouseMotionHandler(int x, int y);

/**
 * Dibuja una linea entre los puntos dados utilizando
 * el algoritmo DDA.
 */
void drawLine(int x1, int y1, int x2, int y2);

/**
 * Puntos entre los que se dibujara la linea.
 */
int xi, yi, xf, yf;
  
int main()
{
  int a;
  glutInit(&a, NULL);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Algoritmo DDA");

  glutDisplayFunc(display);
  glutMouseFunc(mouseHandler);
  glutMotionFunc(mouseMotionHandler);
  
  glClearColor(1, 1, 1, 0);
  glViewport(0, 0, WIDTH, HEIGHT);

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
    drawLine(xi, yi, xf, yf);
  glEnd();

  glFlush();
}

void mouseHandler(int button, int state, int x, int y)
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    xi = xf = x;
    /*
      La funcion recibe la posicion verical medida desde arriba de la ventana
      pero la ventana mide la posicion vertical desde abajo de la ventana, por lo
      tanto la posicion en la ventana es: HEIGHT - y.
     */
    yi = yf = HEIGHT - y;
  }

  // Repinta la ventana
  glutPostRedisplay();
}

void mouseMotionHandler(int x, int y)
{
  xf = x;
  yf = HEIGHT - y;

  // Repinta la ventana
  glutPostRedisplay();
}

void drawLine(int x1, int y1, int x2, int y2)
{
  int dx = x2 - x1, dy = y2 - y1, steps, k;
  float xIncrement, yIncrement, x = x1, y = y1;

  if(fabs(dx) > fabs(dy))
    steps = fabs(dx);
  else
    steps = fabs(dy);

  xIncrement = (float) dx / (float) steps;
  yIncrement = (float) dy / (float) steps;

  glVertex2i(x, y);

  for(k = 0; k < steps; k++) {
    x += xIncrement;
    y += yIncrement;

    glVertex2i(x, y);
  }
}
