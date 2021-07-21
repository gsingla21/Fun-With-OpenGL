#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<unistd.h>
void circle(int x,int y, int r)
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
float x=177,y=85;
int kali=1,kali2=0,kali3=0;
float x_pos=80,y_pos=70;
void delay(int)
{
glutPostRedisplay();
glutTimerFunc(1000/60,delay,0);
switch(kali)
{
case 1:
if(x_pos<=165)
x_pos++;
else
kali=-1;
break;
case -1:
if(x_pos>=80)
x_pos--;
kali2=1;
break;

}
switch(kali2)
{
case 1:
if (x<485)
{x++;
y=sqrt((1-(((x-331)*(x-331))/(154*154)))*35*35)+85;}
else
kali3=1;
break;

}
switch(kali3)
{
case 1:
glColor3f (1.0, 0.0, 0.0);
glRasterPos2f(150, 400);
char *s1 = "GOAL";
while(*s1){
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s1++);
}
break;
}
y_pos=-sqrt(2500-(x_pos-120)*(x_pos-120))+100;
}
void display() {
glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity();
glColor3f(1.0, 0.0, 0.0);
circle(120,225,25);
glBegin(GL_LINE_LOOP);
glVertex2f(120,200);
glVertex2f(120,100);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(120,100);
glVertex2f(160,70);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(120,160);
glVertex2f(100,140);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2f(120,160);
glVertex2f(140,140);
glEnd();
circle(x,y,15);
glBegin(GL_LINE_LOOP);
glVertex2f(120,100);
glVertex2f(x_pos,y_pos);
glEnd();

glColor3f(0.0,1.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(0,0);
glVertex2f(500,0);
glVertex2f(500,70);
glVertex2f(0,70);
glEnd();
glutSwapBuffers();
}
void init() {
glClearColor(0.5f, 0.5f, 1, 1);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0, 500, 0, 500);
glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGB || GLUT_DOUBLE);
glutInitWindowSize(500,500);
glutInitWindowPosition(100,100);
glutCreateWindow("Football");
init();
glutDisplayFunc(display);
glutTimerFunc(1000,delay,0);
glutMainLoop();
return 0;
}
