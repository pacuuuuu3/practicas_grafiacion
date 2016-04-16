/* p5-menu.c
   Pop-up menu and bitmap character are examined.
*/
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

double sizeOfTeapot = 1.0;
static double angulo = 0.0; /* El ángulo para rotar la tetera */

void myIdle(void);

void myKeyboard (unsigned char key, int x, int y) {
  switch(key){
  case 's':
    angulo += 5;
    break;
  case 'd':
    angulo -= 5;
    break;
  case 27:
    exit(0);
    break;
  default:
    break;
  }
  myIdle();
}

void myInit (char *progname) {
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow(progname);
  glClearColor(0.0, 0.0, 0.0, 1.0);
}


void myReshape (int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(0.0, 0.0, -5.0); // move teapot
  
  
}

void getValueFromMenu(int value)
{
  switch(value){
  case 1:
    sizeOfTeapot = 0.5;
    break;
  case 2:
    sizeOfTeapot = 1.0;
  case 3:
    sizeOfTeapot = 2.0;
  default:
    break;
  }
}

void mySetMenu()
{
  glutCreateMenu(getValueFromMenu);
  glutAddMenuEntry("x 0.5", 1);
  glutAddMenuEntry("x 1.0", 2);
  glutAddMenuEntry("x 2.0", 3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void myDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glRotated(angulo, 0, 1, 0);
  glTranslated(0.0, 0.0, 0.0);
  glColor3d(0.93, 0.64, 0.68);
  glutWireTeapot(sizeOfTeapot);
  glPopMatrix();
  glutSwapBuffers();  
}

void myIdle(void)
{
  angulo = fmod(angulo, 360);
  glutPostRedisplay();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  myInit(argv[0]);
  mySetMenu();
  glutKeyboardFunc(myKeyboard);
  glutIdleFunc(myIdle);
  glutReshapeFunc(myReshape);
  glutDisplayFunc(myDisplay);
  glutMainLoop();
  return 0;
}
