#include <iostream>
#include<vector>
#include <math.h>
#include<stack>
#include <GL/glut.h>
#define BLACK 0
using namespace std;
int boundaryCol[] = {255,255,0}; //color of boundary of
polygon
int fillColor[] = {0,0,255}; //color to be filled inside the
polygon
int window[600][500]={0};
void draw_poly(){
glLineWidth(1);
glPointSize(1);
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(boundaryCol[0],boundaryCol[1],boundaryCol[2]);
//passing the boundaryColor vector as the color for our polygon
glBegin(GL_LINE_LOOP);
glVertex2i(100,100);
glVertex2i(100,200);
glVertex2i(200,200);
glVertex2i(200,100);
glEnd();
glFlush();
}
void draw_dot(int x, int y)
{
glColor3f(fillColor[0],fillColor[1], fillColor[2]);
glBegin(GL_POINTS);
glVertex2f(x, y);
glEnd();
glFlush();
}
class pixel_data{
public:
int x, y;
char direction;
public:
pixel_data(int x_val, int y_val, char d_val):
x(x_val), y(y_val), direction(d_val){}
pixel_data():x(0), y(0), direction(0){}
void set(int x_val, int y_val, int d_val){
x = x_val, y = y_val, direction = d_val;
}

};
stack<pixel_data> stk;
bool valid(int x_curr,int y_curr)
{
unsigned char current_pixel_color[3];
unsigned int red_val, green_val, blue_val;
glReadPixels(x_curr, y_curr, 1, 1, GL_RGB, GL_UNSIGNED_BYTE,
current_pixel_color);
red_val = current_pixel_color[0];
green_val = current_pixel_color[1];
blue_val = current_pixel_color[2];
if( !((red_val == boundaryCol[0]) && (green_val ==
boundaryCol[1]) && (blue_val == boundaryCol[2])) &&
!((red_val == fillColor[0]) && (green_val == fillColor[1]) &&
(blue_val == fillColor[2]))&&
(x_curr<=195 && x_curr>=105) && (y_curr<=195 &&
y_curr>=105))

return true;
return false;
}
void boundary_fill_non_recursive(int x, int y, int fc[3], int bc[3]){
/* Order of traversing the neighbouring pixels:
* Up (U), Down (D), Left (L), Right (R).
* Let us use 'S' top denote staring pixel - a special case.
*/
x=150;
y=150;
draw_dot(x, y);
float old_color[4];
glGetFloatv(GL_CURRENT_COLOR, old_color);
glColor3f(fc[0], fc[1], fc[2]);
window[x][y]=1;
/* Init stack. */
//if (valid(x-1,y)==true && window[x-1][y]==0)
stk.push(pixel_data(x - 1, y, 'R'));
//if (valid(x+1,y)==true && window[x+1][y]==0)
stk.push(pixel_data(x + 1, y, 'L'));
//if (valid(x,y-1)==true && window[x][y-1]==0)
stk.push(pixel_data(x, y - 1, 'D'));
//if (valid(x,y+10)==true && window[x][y+10]==0)
stk.push(pixel_data(x, y + 1, 'U'));
stk.push(pixel_data(x+1, y + 1, 'n'));
stk.push(pixel_data(x-1, y+1, 'k'));


stk.push(pixel_data(x+1, y - 1, 'm'));
stk.push(pixel_data(x - 1,y-1, 'j'));

while(stk.empty()==false)
{
/* Get the top element of stack. */
pixel_data curr_pixel_data = stk.top();
int x_curr = curr_pixel_data.x;
int y_curr = curr_pixel_data.y;
int d_curr = curr_pixel_data.direction;
stk.pop();
//int n = stk.size();
//curr_pixel_data = stk[n-1];
if(valid(x_curr,y_curr) && window[x_curr][y_curr]==0)
{ draw_dot(x_curr, y_curr);
window[x_curr][y_curr]=1;
cout<<"stack: "<<curr_pixel_data.x<<" "<<curr_pixel_data.y<<"
"<<curr_pixel_data.direction<<" "<<stk.size()<<"\n";

stk.push(pixel_data(x_curr, y_curr + 1, 'U'));
stk.push(pixel_data(x_curr, y_curr - 1, 'D'));
stk.push(pixel_data(x_curr + 1, y_curr, 'L'));
stk.push(pixel_data(x_curr - 1, y_curr, 'R'));
stk.push(pixel_data(x_curr+1, y_curr + 1, 'n'));
stk.push(pixel_data(x_curr-1, y_curr+1, 'k'));
stk.push(pixel_data(x_curr - 1, y_curr-1, 'j'));
stk.push(pixel_data(x_curr+1, y_curr - 1, 'm'));
}

}
/* Restore the orignial color. */
glColor3f(old_color[0], old_color[1], old_color[2]);
return;
}
void init(){
glClearColor (0, 0, 0, 0);
/* Clearing color. */
glColor3f(1.0f, 0.0f, 0.0f);
/* Drawing color. */
glPointSize(1.0);
/* Setting the dot size. */
glMatrixMode(GL_PROJECTION);
glLoadIdentity();


gluOrtho2D(0, 600, 0, 500);
}

void mouse(int btn,int state,int x,int y){
y = 500-y;
x = x;
window[x][y]=1;
if(btn==GLUT_LEFT_BUTTON)
{
if(state==GLUT_DOWN)
{
//glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,intCol);
boundary_fill_non_recursive(x,y,fillColor,boundaryCol);
}
}
}
int main(int argc, char** argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(600,500);
glutInitWindowPosition(200,200);
glutCreateWindow("Boundary Fill 8 connected");
init();
glutDisplayFunc(draw_poly);
glutMouseFunc(mouse);
//process();
glutMainLoop();
return 0;
}
