#include<GL/glut.h>
#include<cmath>
#include<iostream>
#include<vector>
using namespace std;
class points
{
public:
double x;
double y;
};
points shear_about_xaxis(double x,double y,double shx)
{
points r;
r.x=x+shx*y;
r.y=y;
return r;
}
points shear_about_yaxis(double x,double y,double shy)
{
points r;
r.x=x;
r.y=y+shy*x;
return r;
}
vector<points> allpoints;
vector<points> getpoints()
{
int n;
cout<<"Enter number of Points: ";
cin>>n;
cout<<"Enter Points: \n";
vector<points> z;
for(int i=1;i<=n;i++)
{
double x,y;
cout<<"x"<<i<<": ";
cin>>x;
cout<<"y"<<i<<": ";
cin>>y;
points alpha;
alpha.x=x;
alpha.y=y;
z.push_back(alpha);


}
return z;
}
int flag=0;
double m,c;
vector<points> z;
vector<points> temp;
vector<points> menu(vector<points> temp)
{
cout<<"Menu: \n";
cout<<"Press 1 for Shear about x-axis.\n";
cout<<"Press 2 for Shear about y-axis.\n";
cout<<"Press 3 for Show and Exit.\n";
cout<<"Key: ";
int n;
cin>>n;
switch(n)
{
case 1:
{
cout<<"Do you want to do Shear about x-axis? (y/n): ";
char u;
cin>>u;
if (u=='y')
{
double shx;
cout<<"Shearing parameter towards X direction: ";
cin>>shx;
int n=temp.size();
int i=0;
while(i!=n)
{
temp.push_back(shear_about_xaxis(temp[0].x,temp[0].y,shx));
temp.erase(temp.begin());
i++;
}
glFlush();
cout<<"Do you want to do Show and exit? (y/n): ";
cin>>u;
if (u=='y')
break;
else
{temp=menu(temp);
break;}
}

else
{temp=menu(temp);
break;}
}
case 2:
{
cout<<"Do you want to do Shear about y-axis? (y/n): ";
char u;
cin>>u;
if (u=='y')
{
double shy;
cout<<"Shearing parameter towards Y direction: ";
cin>>shy;
int n=temp.size();
int i=0;
while(i!=n)
{
temp.push_back(shear_about_yaxis(temp[0].x,temp[0].y,shy));
temp.erase(temp.begin());
i++;
}
glFlush();
cout<<"Do you want to do Show and exit? (y/n): ";
cin>>u;
if (u=='y')
break;
{temp=menu(temp);
break;}
}
else
{temp=menu(temp);
break;}
}
case 3:
break;
default:
{
cout<<"Invalid Input";
temp=menu(temp);
}
}
return temp;
}
vector<points> process()
{

temp=allpoints;
temp=menu(temp);
return temp;
}
void display() {
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2i(-320,0);
glVertex2i(320,0);
glEnd();
glBegin(GL_LINE_LOOP);
glVertex2i(0,-240);
glVertex2i(0,240);
glEnd();
glColor3f(0.0, 100.0, 0.0);
glBegin(GL_LINE_LOOP);
for(int i=0;i<allpoints.size();i++)
{
glVertex2i(allpoints[i].x,allpoints[i].y);
}
glEnd();
glColor3f(100.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
for(int i=0;i<z.size();i++)
{
glVertex2i(z[i].x,z[i].y);
}
glEnd();
glFlush();
}
void myinit() {
glClearColor(1.0, 1.0, 1.0, 0.0);
glColor3f(0.0, 0.0, 0.0);
glPointSize(4.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-500.0, 500.0, -500, 500.0);
}
int main(int argc, char** argv) {
allpoints=getpoints();
z=process();


glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(1000, 1000);
glutInitWindowPosition(100, 150);
glutCreateWindow("SHEARING");
glutDisplayFunc(display);
myinit();
glutMainLoop();
}
