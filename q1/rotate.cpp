#define PROGRAM_TITLE "Rotate"
#define DISPLAY_INFO "rotate.cpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

const int ROT_STEP = 30;

int Window_ID;
int Window_Width = 600;
int Window_Height = 400;

float p1x, p1y, p1z, p2x, p2y, p2z, cx, cy, cz;
int rotationAngle = ROT_STEP;

static void PrintString(void *font, char *str)
{
   int i,len=strlen(str);

   for(i=0;i < len; i++)
      glutBitmapCharacter(font,*str++);
}

void CallBackRenderScene(void)
{
  char buf[80];

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(cx, cy, cz);
  glRotatef(rotationAngle, p2x - p1x, p2y - p1y, p2z - p1z);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glColor4f(0.0, 0.9, 0.0, 1.0);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    glNormal3f(1.0f, 0.0f, 0.0f);
    glColor4f(0.9, 0.0, 0.0, 1.0);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor4f(0.0, 0.0, 0.9, 1.0);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glColor4f(0.9, 0.9, 0.0, 1.0);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);

    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor4f(0.9, 0.0 ,0.9, 1.0);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f,  -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);

    glNormal3f(0.0f, -1.0f, 0.0f);
    glColor4f(0.0, 0.9, 0.9, 1.0);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f,  -1.0f);
    glVertex3f(1.0f,  -1.0f,  1.0f);
    glVertex3f(-1.0f,  -1.0f, 1.0f);

  glEnd();

  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  glLoadIdentity();
  glOrtho(0,Window_Width,0,Window_Height,-1.0,1.0);
  glColor4f(0.6,1.0,0.6,1.00);
  sprintf(buf,"%s", DISPLAY_INFO);
  glRasterPos2i(2,2);
  PrintString(GLUT_BITMAP_HELVETICA_12, buf);

  glTranslatef(6.0f, Window_Height - 14, 0.0f);

  glPopMatrix();
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

  glutSwapBuffers();
}

void CallBackMouseEvent(int button, int state, int x, int y)
{
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
    rotationAngle = (rotationAngle + ROT_STEP) % 360;
  }
}

void CallBackResizeScene(int Width, int Height)
{
   if (Height == 0)
      Height = 1;

   glViewport(0, 0, Width, Height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

   glMatrixMode(GL_MODELVIEW);

   Window_Width  = Width;
   Window_Height = Height;
}

int init(int Width, int Height) {
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

  glClearDepth(1.0);
  glDepthFunc(GL_LESS);

  glDepthMask(GL_TRUE);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glEnable(GL_DEPTH_TEST);

  glShadeModel(GL_SMOOTH);
  CallBackResizeScene(Width,Height);
}

int main(int argc, char **argv)
{
  if (argc != 10) {
    printf("Incorrect amount of arguments\n");
    return 1;
  }

  p1x = atof(argv[1]);
  p1y = atof(argv[2]);
  p1z = atof(argv[3]);
  p2x = atof(argv[4]);
  p2y = atof(argv[5]);
  p2z = atof(argv[6]);
  cx = atof(argv[7]);
  cy = atof(argv[8]);
  cz = atof(argv[9]);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(Window_Width, Window_Height);
  Window_ID = glutCreateWindow(PROGRAM_TITLE);

  glutDisplayFunc(&CallBackRenderScene);
  glutIdleFunc(&CallBackRenderScene);
  glutReshapeFunc(&CallBackResizeScene);
  glutMouseFunc(&CallBackMouseEvent);

  init(Window_Width, Window_Height);

  printf("\n%s\n\n", PROGRAM_TITLE);

  glutMainLoop();
  return 1;
}
