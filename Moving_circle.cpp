#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

void circle(int x,int y)
{
float th;
glBegin(GL_LINE_LOOP);
int i=0;
for(i=0;i<360;i++)
{
th=i*3.142/180;
glVertex2f(x+30*cos(th),y+30*sin(th));
}
glEnd();
}

float x_position=-10;
int state=1;
void display() {
glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity();
glColor3f(1.0, 0.0, 0.0);
circle(x_position,0);
glutSwapBuffers(); 
}
void init() {
	glClearColor(0.5f, 0.5f, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
	glMatrixMode(GL_MODELVIEW);
}
void doFrame(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000/60,doFrame,0);
	switch(state)
	{
	case 1:
		if(x_position<250)
			x_position+=2;
		else 
			state=-1;
		break;
	case -1:
		if(x_position>-250)
			x_position-=2;
		else
			state=1;
		break;
	}
}
int main(int argc, char** argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB || GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);  
    glutCreateWindow("Windmill"); 

    init();

    glutDisplayFunc(display);   
    glutTimerFunc(1000,doFrame,0); 

    glutMainLoop(); 
    return 0;
}    
