#include<GL/glut.h>
#include<math.h>
void circle(int x,int y)
{
float th;
glBegin(GL_LINE_LOOP);
int i=0;
for(i=0;i<360;i++)
{
th=i*3.142/180;
glVertex2f(x+10*cos(th),y+10*sin(th));
}
glEnd();
}
void display() {
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0, 100.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(60.0, 80.0);
glVertex2f(150.0, 80.0);
glVertex2f(150.0, 200.0);
glVertex2f(60.0, 200.0);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(95.0, 140.0);
glVertex2f(120.0, 140.0);
glVertex2f(120.0, 80.0);
glVertex2f(95.0, 80.0);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(60.0, 200.0);
glVertex2f(105.0, 300.0);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(150.0, 200.0);
glVertex2f(105.0, 300.0);
glEnd();
glBegin(GL_LINE_LOOP);

glVertex2f(105,300);
glVertex2f(230,300);
glVertex2f(270,200);
glVertex2f(150,200);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(150,80);
glVertex2f(270,80);
glVertex2f(270,200);
glVertex2f(150,200);
glEnd();
circle(105,250);
glFlush();
}
void myinit() {
glClearColor(1.0, 1.0, 0.0, 1.0);
glColor3f(1.0, 0.0, 0.0);
glPointSize(50.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(700, 700);
glutInitWindowPosition(5, 5);
glutCreateWindow("Rectangle");
glutDisplayFunc(display);
myinit();
glutMainLoop();
}
