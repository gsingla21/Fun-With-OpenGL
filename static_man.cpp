#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
void head(int x,int y,int r)
{
float th;
glBegin(GL_LINE_LOOP);
int i=0;
for(i=0;i<360;i++)
{
th=i*3.142/180;
glVertex2f(x+r*cos(th),y+r*sin(th));
}
glEnd();
}
void smile(int x,int y,int r)
{
float th;
glBegin(GL_LINE_LOOP);
int i=0;
for(i=240;i<300;i++)
{
th=i*3.142/180;
glVertex2f(x+r*cos(th),y+r*sin(th));
}
glEnd();
}
void man()
{
head(150,400,50);
head(125,425,5);
head(175,425,5);
glBegin(GL_LINE_LOOP);
glVertex2f(150,412);
glVertex2f(150,388);
glEnd();
smile(150,412,37);
glBegin(GL_LINE_LOOP);
glVertex2f(150,350);
glVertex2f(150,250);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(100,150);
glVertex2f(150,250);

glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(200,150);
glVertex2f(150,250);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(150,325);
glVertex2f(125,300);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(150,325);
glVertex2f(175,300);
glEnd();
}
void display() {
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 0.0, 0.0);
man();
glFlush();
}
void myinit() {
glClearColor(0, 0, 0, 1.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0, 499.0, 0.0, 499.0);
glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(500, 500);
glutInitWindowPosition(0, 0);
glutCreateWindow("MAN");
glutDisplayFunc(display);
myinit();
glutMainLoop();
}
