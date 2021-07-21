/*ellipse(520,200,30,330,90,30);
circle(450,193,3);
line(430,200,450,200);
line(597,185,630,170);
line(597,215,630,227);
line(630,170,630,227);
line(597,200,630,200);
line(597,192,630,187);
line(597,207,630,213);
line(500,190,540,150);
line(530,190,540,150);*/
#include<math.h>
#include<GL/glut.h>
void circle(int x,int y,int r)
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
void ellipse(float cx, float cy, float rx, float ry,
int num_segments)
{
float theta = 2 * 3.1415926/num_segments;
float c = cosf(theta);//precalculate the sine and cosine
float s = sinf(theta);
float t;
float x = 1;//we start at angle = 0
float y = 0;
glBegin(GL_LINE_LOOP);
int ii=0;
for(ii = 0; ii < num_segments; ii++)
{
//apply radius and offset
glVertex2f(x * rx + cx, y * ry + cy);
//output vertex
//apply the rotation matrix
t = x;
x = c * x - s * y;
y = s * t + c * y;
}


glEnd();
}
void display() {
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0, 100.0, 0.0);
ellipse(200,200,90,30,360);
circle(130,210,3);
glBegin(GL_LINE_LOOP);
glVertex2f(110.0, 200.0);
glVertex2f(130.0, 200.0);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(270.0, 215.0);
glVertex2f(310.0, 227.0);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(270.0, 185.0);
glVertex2f(310.0, 170.0);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(297.0, 192.0);
glVertex2f(310.0, 187.0);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(297.0, 208.0);
glVertex2f(310.0, 213.0);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(310.0, 170.0);
glVertex2f(310.0, 227.0);
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


int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(700, 700);
glutInitWindowPosition(5, 5);
glutCreateWindow("FISH");
glutDisplayFunc(display);
myinit();
glutMainLoop();
}
