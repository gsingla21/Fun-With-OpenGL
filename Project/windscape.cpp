#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
const double PI = 3.141592654;
int flag=0;
int frameNumber = 0;
int p,q,r=1;
int traffic_regulator=1;
int running=0,xx;
void myMouse(int button,int state,int x,int y)
{
if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
{
traffic_regulator=0;
p=1;
q=0;
r=0;
}
if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
{
traffic_regulator=0;
p=0;
q=1;
r=0;
}
if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP)
{
traffic_regulator=1;
p=0;
q=0;
r=1;
}
glutPostRedisplay();
}
void signal()
{
//stand
glColor3f(0.1,0.2,0.1);
glBegin(GL_POLYGON);
glVertex2f(4.5,0.5);
glVertex2f(4.5,0.7);
glVertex2f(5,0.7);
glVertex2f(5,0.5);

glEnd();
//pole
glBegin(GL_POLYGON);
glVertex2f(4.65,0.55);
glVertex2f(4.65,2);
glVertex2f(4.85,2);
glVertex2f(4.85,0.55);
glEnd();
//red
glColor3f(p,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(4.7,1.8);
glVertex2f(4.8,1.8);
glVertex2f(4.8,1.75);
glVertex2f(4.7,1.75);
glEnd();
//yellow
glColor3f(q,q,0.0);
glBegin(GL_POLYGON);
glVertex2f(4.7,1.725);
glVertex2f(4.8,1.725);
glVertex2f(4.8,1.675);
glVertex2f(4.7,1.675);
glEnd();
//green
glColor3f(0.0,r,0.0);
glBegin(GL_POLYGON);
glVertex2f(4.7,1.65);
glVertex2f(4.8,1.65);
glVertex2f(4.8,1.6);
glVertex2f(4.7,1.6);
glEnd();
}
/*
* Draw a 32-sided regular polygon as an approximation for a circular disk.
* (This is necessary since OpenGL has no commands for drawing ovals, circles,
* or curves.) The disk is centered at (0,0) with a radius given by the
* parameter.
*/
void drawDisk(double radius) {
int d;
glBegin(GL_POLYGON);
for (d = 0; d < 32; d++) {
double angle = 2*PI/32 * d;
glVertex2d( radius*cos(angle), radius*sin(angle));
}
glEnd();
}

/*
* Draw a wheel, centered at (0,0) and with radius 1. The wheel has 15 spokes
* that rotate in a clockwise direction as the animation proceeds.
*/
void drawWheel() {
int i;
glColor3f(0,0,0);
drawDisk(1.2);
glColor3f(0.75f, 0.75f, 0.75f);
drawDisk(0.8);
glColor3f(0,0,0);
drawDisk(0.2);
if(traffic_regulator==0 && xx>3 && xx<4.5)
glRotatef(0,0,0,1);
else
glRotatef(running*20,0,0,1);
glBegin(GL_LINES);
for (i = 0; i < 4; i++) {
glVertex2f(0,0);
glVertex2d(cos(i*2*PI/4), sin(i*2*PI/4));
}
glEnd();
}
/*
* Draw a car consisting of a rectangular body and two wheels. The wheels
* are drawn by the drawWheel() method; a different translation is applied to each
* wheel to move them into position under the body. The body of the car
* is a red rectangle with corner at (0,-2.5), width 5, and height 2. The
* center of the bottom of the rectangle is at (0,0).
*/
void drawcar() {
glPushMatrix();
glTranslatef(-1.5f, -0.1f, 0);
glScalef(0.8f,0.8f,1);
drawWheel();
glPopMatrix();
glPushMatrix();
glTranslatef(1.5f, -0.1f, 0);
glScalef(0.8f,0.8f,1);
drawWheel();
glPopMatrix();
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
glVertex2f(-3.5f,0);
glVertex2f(4.0f,0);
glVertex2f(4.0f,0.75f);
glVertex2f(3.0f,2);

glVertex2f(-3.0f,2);
glVertex2f(-3.5f,1.7);
glEnd();
glColor3f(0,0,0);
glBegin(GL_POLYGON);
glVertex2f(2.3f,1.8);
glVertex2f(2.3f,0.9);
glVertex2f(0.3f,0.9f);
glVertex2f(0.3f,1.8);
glEnd();
glColor3f(0,0,0);
glBegin(GL_POLYGON);
glVertex2f(-0.5f,1.8);
glVertex2f(-0.5f,0.9);
glVertex2f(-2.5f,0.9f);
glVertex2f(-2.5f,1.8);
glEnd();
glColor3f(0,0,0);
glBegin(GL_POLYGON);
glVertex2f(4.0f,0.75f);
glVertex2f(-3.5f,0.75f);
glEnd();
}
/*
* Draw a sun with radius 0.5 centered at (0,0). There are also 13 rays which
* extend outside from the sun for another 0.25 units.
*/

void drawSun() {
int i;
glColor3f(1,1,0);
for (i = 0; i < 13; i++) { // Draw 13 rays, with different rotations.
glRotatef( 360 / 13, 0, 0, 1 ); // Note that the rotations accumulate!
glBegin(GL_LINES);
glVertex2f(0, 0);
glVertex2f(0.75f, 0);
glEnd();
}
drawDisk(0.5);
glColor3f(0,0,0);
}


/*
* Draw a windmill, consisting of a pole and three vanes. The pole extends from the
* point (0,0) to (0,3). The vanes radiate out from (0,3). A rotation that depends
* on the frame number is applied to the whole set of vanes, which causes the windmill
* to rotate as the animation proceeds. Note that this method changes the current
* transform in the GL context gl! The caller of this subroutine should take care
* to save and restore the original transform, if necessary.
*/
void drawWindmill() {
int i;
glColor3f(0.8f, 0.8f, 0.9f);
glBegin(GL_POLYGON);
glVertex2f(-0.05f, 0);
glVertex2f(0.05f, 0);
glVertex2f(0.05f, 3);
glVertex2f(-0.05f, 3);
glEnd();
glTranslatef(0, 3, 0);
int temp;
glRotated(frameNumber * (180.0/46), 0, 0, 1);
glColor3f(0.4f, 0.4f, 0.8f);
for (i = 0; i < 3; i++) {
glRotated(120, 0, 0, 1); // Note: These rotations accumulate.
glBegin(GL_POLYGON);
glVertex2f(0,0);
glVertex2f(0.5f, 0.1f);
glVertex2f(1.5f,0);
glVertex2f(0.5f, -0.1f);
glEnd();
}
}
/*
* This function is called when the image needs to be redrawn.
* It is installed by main() as the GLUT display function.
* It draws the current frame of the animation.
*/

void display() {
glClear(GL_COLOR_BUFFER_BIT); // Fills the scene with blue.
glLoadIdentity();
/* Draw three green triangles to form a ridge of hills in the background */
glColor3f(0, 0.6f, 0.0f);
glBegin(GL_POLYGON);
glVertex2f(-3,-1);
glVertex2f(1.5f,1.65f);
glVertex2f(5,-1);
glEnd();
glBegin(GL_POLYGON);
glVertex2f(-3,-1);
glVertex2f(3,2.1f);
glVertex2f(7,-1);
glEnd();
glBegin(GL_POLYGON);
glVertex2f(0,-1);
glVertex2f(6,1.2f);
glVertex2f(20,-1);
glEnd();
signal();
/* Draw a bluish-gray rectangle to represent the road. */
glColor3f(0.4f, 0.4f, 0.5f);
glBegin(GL_POLYGON);
glVertex2f(0,-0.4f);
glVertex2f(7,-0.4f);
glVertex2f(7,0.4f);
glVertex2f(0,0.4f);
glEnd();
/* Draw a white line to represent the stripe down the middle
* of the road. */
glLineWidth(6); // Set the line width to be 6 pixels.
glColor3f(1,1,1);
glBegin(GL_LINES);
glVertex2f(0,0);
glVertex2f(7,0);
glEnd();
glLineWidth(1); // Reset the line width to be 1 pixel.
/* Draw the sun. The drawSun method draws the sun centered at (0,0). A 2D
translation

* is applied to move the center of the sun to (5,3.3). A rotation makes it rotate*/
glPushMatrix();
glTranslated(5.8,3,0);
glRotated(-frameNumber*0.7,0,0,1);
drawSun();
glPopMatrix();
/* Draw three windmills. The drawWindmill method draws the windmill with its
base
* at (0,0), and the top of the pole at (0,3). Each windmill is first scaled to change
* its size and then translated to move its base to a different paint. In the animation,
* the vanes of the windmill rotate. That rotation is done with a transform inside the
* drawWindmill method. */
glPushMatrix();
glTranslated(0.75,1,0);
glScaled(0.6,0.6,1);
drawWindmill();
glPopMatrix();
glPushMatrix();
glTranslated(2.2,1.6,0);
glScaled(0.4,0.4,1);
drawWindmill();
glPopMatrix();
glPushMatrix();
glTranslated(3.7,0.8,0);
glScaled(0.7,0.7,1);
drawWindmill();
glPopMatrix();
//zebra crossing
glColor3f(1,1,1);
glBegin(GL_POLYGON);
glVertex2f(4.5,0.35);
glVertex2f(5,0.35);
glVertex2f(5,0.15);
glVertex2f(4.5,0.15);
glEnd();
glColor3f(1,1,1);
glBegin(GL_POLYGON);
glVertex2f(4.5,0.1);
glVertex2f(5,0.1);
glVertex2f(5,-0.1);
glVertex2f(4.5,-0.1);

glEnd();
glColor3f(1,1,1);
glBegin(GL_POLYGON);
glVertex2f(4.5,-0.15);
glVertex2f(5,-0.15);
glVertex2f(5,-0.35);
glVertex2f(4.5,-0.35);
glEnd();
/* Draw the car. The drawcar method draws the car with the center of its base at
* (0,0). The body of the car is 5 units long and 2 units high. A scale is first
* applied to the car to make its size more reasonable for the picture. Then a
* translation is applied to move the car horizontally. The amount of the translation
* depends on the frame number, which makes the car move from left to right across
* the screen as the animation progresses. The car animation repeats every 300
* frames. At the beginning of the animation, the car is off the left edge of the
* screen. */
if(traffic_regulator==0)
{
if(xx>3 && xx<4.5)
{
glPushMatrix();
glTranslated(3, 0, 0);
glScaled(0.3,0.3,1);
drawcar();
glPopMatrix();
}
else
{
xx=-3 + 13*((running++) % 300) / 300.0;
glPushMatrix();
glTranslated(xx, 0, 0);
glScaled(0.3,0.3,1);
drawcar();
glPopMatrix();
}
}
else
{
xx=-3 + 13*((running++) % 300) / 300.0;
glPushMatrix();
glTranslated(xx, 0, 0);
glScaled(0.3,0.3,1);
drawcar();
glPopMatrix();
}

glutSwapBuffers();
} // end display
/*
* This function is set as the glutTimerFunc to drive the animation
*/
void doFrame(int v) {
frameNumber++;
glutPostRedisplay();
glutTimerFunc(30,doFrame,0);
}
/*
* This method is called from main() to initialize OpenGL.
*/
void init() {
glClearColor(0.5f, 0.5f, 1, 1);
// The next three lines set up the coordinates system.
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0, 7, -1, 4, -1, 1);
glMatrixMode(GL_MODELVIEW);
}
void *currentfont;
void setFont(void *font)
{
currentfont=font;
}
void drawstring(float x,float y,float z,char *string)
{
char *c;
glRasterPos3f(x,y,z);
for(c=string;*c!='\0';c++)
{ glColor3f(0.0,0.0,0.0);
glutBitmapCharacter(currentfont,*c);
}
}

void frontscreen(void)
{
setFont(GLUT_BITMAP_9_BY_15);
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1,0,0);
drawstring(1.5,3.5,0.0,"THAPAR INSTITUTE OF ENGINEERING AND TECHNOLOGY
");
drawstring(1.8,3.3,0.0,"DEPARTMENT OF COMPUTER ENGINEERING");
glColor3f(1,0,0);
setFont(GLUT_BITMAP_TIMES_ROMAN_24);
drawstring(3.0,2.8,0.0,"ti");
glColor3f(1,0,0);
setFont(GLUT_BITMAP_9_BY_15);
drawstring(2.6,2.3,0.0,"A Mini Project on:");
glColor3f(1,0,0);
setFont(GLUT_BITMAP_TIMES_ROMAN_24);
drawstring(1.3,2.0,0.0,"Graphical Representation of A Windscape");
glColor3f(0,0,0);
setFont(GLUT_BITMAP_9_BY_15);
drawstring(0.5,0.0,0.0,"By:");
glColor3f(0,0,0);
setFont(GLUT_BITMAP_9_BY_15);
drawstring(0.5,-0.3,0.0,"GOURISH SINGLA (101803698)");
glColor3f(0,0,0);
setFont(GLUT_BITMAP_9_BY_15);
drawstring(0.5,-0.6,0.0,"ETASHA AGGARWAL (101803325)");
glColor3f(0,0,0);
setFont(GLUT_BITMAP_9_BY_15);
drawstring(0.5,-0.9,0.0,"RAFIROSE KHAN SHAH (101983019)");
glColor3f(0,0,0);
setFont(GLUT_BITMAP_9_BY_15);
drawstring(5.0,0.0,0.0,"To:");
glColor3f(0,0,0);
setFont(GLUT_BITMAP_9_BY_15);
drawstring(5.0,-0.3,0.0,"Ms. KUDRATDEEP AULAKH");
drawstring(2.5,1,0.0,"PRESS ENTER TO START");
glFlush();
}

void mydisplay(void)
{
glClear(GL_COLOR_BUFFER_BIT);
if(flag==0)
frontscreen();
if(flag==1)
display();
glutSwapBuffers();
}
void myKeyboard( unsigned char key, int x, int y )
{
switch(key)
{
case 13:
if(flag==0) //Ascii of 'enter' key is 13
{
flag=1;
mydisplay();
}
break;
default:break;
}
}
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE);
glutInitWindowSize(700,500);
glutInitWindowPosition(100,100);
glutCreateWindow("CoE-15 Project");
init();
glutDisplayFunc(mydisplay);
glutTimerFunc(200,doFrame,0);
glutKeyboardFunc(myKeyboard);
glutMouseFunc(myMouse);
glutMainLoop();
return 0;
}
