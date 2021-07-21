#include<GL/glut.h>
void display() {
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0, 100.0, 0.0);
glBegin(GL_LINES);
glVertex2f(10.0, 10.0);
glVertex2f(50.0, 10.0);
glVertex2f(50.0, 10.0);
glVertex2f(50.0, 50.0);
glVertex2f(50.0, 50.0);
glVertex2f(10.0, 50.0);
glVertex2f(10.0, 50.0);
glVertex2f(10.0, 10.0);
glEnd();
glFlush();
}
void myinit() {
glClearColor(1.0, 1.0, 0.0, 1.0);
glColor3f(1.0, 0.0, 0.0);
glPointSize(50.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}
void main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(700, 700);
glutInitWindowPosition(5, 5);
glutCreateWindow("Points");
glutDisplayFunc(display);
myinit();
glutMainLoop();
}
