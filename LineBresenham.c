/**
 * Programa que dibuja una linea utilizando el algoritmo
 * de Bresenham para el trazado de lineas.
 *
 * Compilacion:
 * gcc LineBresenham.c -o LineBresenham -lGL -lGLU -lglut
 * 
 * Ejecucion:
 * ./LineBresenham
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
 * el algoritmo de Bresenham.
 */
void drawLine(int x1, int y1, int x2, int y2);

/**
 * Dimensiones de la ventana
 */
const int WIDTH = 600, HEIGHT = 600;

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
  glutCreateWindow("Algoritmo de Bresenham");

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
      pero la ventana mide la posicion vertical desde abajo de la ventana,
      por lo tanto la posicion en la ventana es: HEIGHT - y.
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
  int dx = x2 - x1, dy = y2 - y1, x = x1, y = y1;
  int xFactor = 0, yFactor = 0, k, steps, c1, c2, p;
  int xIncrement = dx > 0 ? 1 : -1;
  int yIncrement = dy > 0 ? 1 : -1;

  /*
    Obtiene el valor absoluto de dx & dy, ya que lo que va
    a determinar la direccion es xIncrement & yIncrement.
   */
  dx = abs(dx);
  dy = abs(dy);

  /*
    Cambia el valor de las constantes dependiendo del valor
    de la pendiente, poniendolas en funcion de x o y.
    xFactor & yFactor sirven para saber cual variable se
    incrementara en 1.
   */
  if(dx > dy) {
    steps = dx;
    c1 = 2 * dy - 2 * dx;
    c2 = 2 * dy;
    p = 2 * dy - dx;
    xFactor = 1;
  }
  else {
    steps = dy;
    c1 = 2 * dx - 2 * dy;
    c2 = 2 * dx;
    p = 2 * dx - dy;
    yFactor = 1;
  }
  
  glVertex2i(x, y);

  for(k = 0; k < steps; k++) {
    if(p < 0) {
      x += xIncrement * xFactor;
      y += yIncrement * yFactor;
      p = p + c2;
    }
    else {
      x += xIncrement;
      y += yIncrement;
      p = p + c1;
    }

    glVertex2i(x, y);
  }
}
