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
points translation(double x,double y,double tx,double ty)
{
points r;
r.x=x+tx;
r.y=y+ty;
return r;
}
points scaling_about_origin(double x,double y,double sx,double sy)
{
points r;
r.x=sx*x;
r.y=sy*y;
return r;
}
points scaling_about_pivot(double x, double y, double xp,double yp,double sx,double sy)
{
points q;
q=translation(x,y,-xp,-yp);
q=scaling_about_origin(q.x,q.y,sx,sy);
q=translation(q.x,q.y,xp,yp);
return q;
}
points rotation_about_origin(double x,double y,double theta)
{
points r;
double a,b;
theta=theta*3.14159/180;
a=cos(theta);

b=sin(theta);
r.x=x*a-y*b;
r.y=x*b+y*a;
return r;
}

points rotation_about_pivot(double x,double y, double xp,double yp,double theta)
{
points q;
q=translation(x,y,-xp,-yp);
q=rotation_about_origin(q.x,q.y,theta);
q=translation(q.x,q.y,xp,yp);
return q;
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
vector<points> z;
vector<points> temp;
vector<points> menu(vector<points> temp)
{
cout<<"Menu: \n";
cout<<"Press 1 for Translation.\n";
cout<<"Press 2 for Scaling about origin.\n";

cout<<"Press 3 for Rotation about origin.\n";
cout<<"Press 4 for Scaling about pivot.\n";
cout<<"Press 5 for Rotation about pivot.\n";
cout<<"Press 6 for Show and Exit.\n";
cout<<"Key: ";
int n;
cin>>n;
switch(n)
{
case 1:
{
cout<<"Do you want to do Translation? (y/n): ";
char u;
cin>>u;
if (u=='y')
{
double tx,ty;
cout<<"Enter Values: \n";
cout<<"x translate: ";
cin>>tx;
cout<<"y translate: ";
cin>>ty;
int n=temp.size();
int i=0;
while(i!=n)
{
temp.push_back(translation(temp[0].x,temp[0].y,tx,ty));
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
cout<<"Do you want to do Scaling? (y/n): ";
char u;
cin>>u;
if (u=='y')
{
double sx,sy;
cout<<"Enter Values: \n";
cout<<"x scale: ";
cin>>sx;
cout<<"y scale: ";
cin>>sy;
int n=temp.size();
int i=0;
while(i!=n)
{
temp.push_back(scaling_about_origin(temp[0].x,temp[0].y,sx,sy));
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
{
cout<<"Do you want to do Rotation about origin? (y/n): ";
char u;
cin>>u;
if (u=='y')
{
double theta;
cout<<"Enter Values: \n";
cout<<"theta: ";
cin>>theta;
int n=temp.size();

int i=0;
while(i!=n)
{
temp.push_back(rotation_about_origin(temp[0].x,temp[0].y,theta));
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
case 4:
{
cout<<"Do you want to do scaling about pivot? (y/n): ";
char u;
cin>>u;
if (u=='y')
{
double sx,sy,xp,yp;
cout<<"Enter Values: \n";
cout<<"x pivot: ";
cin>>xp;
cout<<"y pivot: ";
cin>>yp;
cout<<"x scale: ";
cin>>sx;
cout<<"y scale: ";
cin>>sy;
int n=temp.size();
int i=0;
while(i!=n)
{

temp.push_back(scaling_about_pivot(temp[0].x,temp[0].y,xp,yp,sx,sy));

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
case 5:
{
cout<<"Do you want to do Rotation about Pivot? (y/n): ";
char u;
cin>>u;
if (u=='y')
{
double theta,xp,yp;
cout<<"Enter Values: \n";
cout<<"x pivot: ";
cin>>xp;
cout<<"y pivot: ";
cin>>yp;
cout<<"theta: ";
cin>>theta;
int n=temp.size();
int i=0;
while(i!=n)
{
temp.push_back(rotation_about_pivot(temp[0].x,temp[0].y,xp,yp,theta));
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
case 6:
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
gluOrtho2D(-320.0, 320.0, -240, 240.0);
}

int main(int argc, char** argv) {
allpoints=getpoints();
z=process();
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(640, 480);
glutInitWindowPosition(100, 150);
glutCreateWindow("Rectangle");
glutDisplayFunc(display);
myinit();
glutMainLoop();
}
