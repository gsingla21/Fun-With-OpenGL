#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

float xc, yc, rx, ry;

void drawEllipse(float xc, float yc, float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2i((int)xc+x, (int)yc+y);
    glVertex2i((int)xc-x, (int)yc+y);
    glVertex2i((int)xc+x, (int)yc-y);
    glVertex2i((int)xc-x, (int)yc-y);
    glEnd();
}
void ellipseMidpoint(float xc, float yc, float rx, float ry)
{
    float rxSq = rx * rx;
    float rySq = ry * ry;
    float x = 0, y = ry, p;
    float px = 0, py = 2 * rxSq * y;
    drawEllipse(xc, yc, x, y);
    p = rySq - (rxSq * ry) + (0.25 * rxSq);
    while (px < py)
    {
        x++;
        px = px + 2 * rySq;
        if (p < 0)
            p = p + rySq + px;
        else
        {
            y--;
            py = py - 2 * rxSq;
            p = p + rySq + px - py;
        }
        drawEllipse(xc, yc, x, y);
    }
    p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;
    while (y > 0)
    {
        y--;
        py = py - 2 * rxSq;
        if (p > 0)
            p = p + rxSq - py;
        else
        {
            x++;
            px = px + 2 * rySq;
            p = p + rxSq - py + px;
        }
        drawEllipse(xc, yc, x, y);
    }
}
void myInit (void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1.0f, 1.0f, 0.0f);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
}

void myDisplay(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 0.0);
	glPointSize(1.0);
	ellipseMidpoint(xc,yc,rx,ry);
	glFlush ();
}
int main(int argc, char** argv)
{
	printf("Enter the center of ellipse:\n");
	printf("X-Coordinate: ");
	scanf("%f",&xc);
	printf("Y-Coordinate: ");
	scanf("%f",&yc);
	printf("Enter horizontal and vertical axis:\n");
	printf("Horizontal axis: ");
	scanf("%f",&rx);
	printf("Vertical axis: ");
	scanf("%f",&ry);
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Ellipse");
	myInit ();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
