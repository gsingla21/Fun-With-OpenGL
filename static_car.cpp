#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
void wheel(int x,int y)
{
float th;
glBegin(GL_LINE_LOOP);
int i=0;
for(i=180;i<360;i++)
{
th=i*3.142/180;
glVertex2f(x+30*cos(th),y+30*sin(th));
}
glEnd();
}
void car()
{
//Bottom
glBegin(GL_LINE_LOOP);
glVertex2f(50,100);
glVertex2f(130,160);
glVertex2f(450,160);
glVertex2f(450,100);
glEnd();
//top
glBegin(GL_LINE_LOOP);
glVertex2f(150,160);
glVertex2f(200,200);
glVertex2f(400,200);
glVertex2f(450,160);
glEnd();
wheel(200,100);
wheel(360,100);
}
void display() {
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 0.0, 0.0);
car();
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
glutCreateWindow("CAR");
glutDisplayFunc(display);
myinit();
glutMainLoop();
}
