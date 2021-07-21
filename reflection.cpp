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
points reflection_about_xaxis(double x,double y)
{
points r;
r.x=x;
r.y=-y;
return r;
}
points reflection_about_yaxis(double x,double y)
{
points r;
r.x=-x;
r.y=y;
return r;
}
points reflection_about_origin(double x,double y)
{
points r;
r.x=-x;
r.y=-y;
return r;
}
points translation(double x,double y,double tx,double ty)
{
points r;
r.x=x+tx;
r.y=y+ty;
return r;
}

points rotation_about_origin(double x,double y,double theta)
{
points r;
double a,b;
a=cos(theta);
b=sin(theta);
r.x=x*a-y*b;
r.y=x*b+y*a;
return r;
}
//y=m*x+c
points reflection_about_arbitrary_axis(double x,double y,double m,double c)
{
points r;
r=translation(x,y,0,-c);
double theta=atan(m);
r=rotation_about_origin(r.x,r.y,-theta);
r=reflection_about_xaxis(r.x,r.y);
r=rotation_about_origin(r.x,r.y,theta);
r=translation(r.x,r.y,0,c);
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
cout<<"Press 1 for Reflection about x-axis.\n";
cout<<"Press 2 for Reflection about y-axis.\n";
cout<<"Press 3 for Reflection about origin.\n";
cout<<"Press 4 for Reflection about arbitrary line.\n";
cout<<"Press 5 for Show and Exit.\n";
cout<<"Key: ";
int n;
cin>>n;
switch(n)
{
case 1:
{
cout<<"Do you want to do Reflection about x-axis?

(y/n): ";

char u;
cin>>u;
if (u=='y')
{
int n=temp.size();
int i=0;
while(i!=n)
{
temp.push_back(reflection_about_xaxis(temp[0].x,temp[0].y));
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
cout<<"Do you want to do Reflection about y-axis?

(y/n): ";

char u;
cin>>u;
if (u=='y')
{
int n=temp.size();
int i=0;
while(i!=n)
{
temp.push_back(reflection_about_yaxis(temp[0].x,temp[0].y));
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
cout<<"Do you want to do Reflection about origin?

(y/n): ";

char u;
cin>>u;
if (u=='y')
{
int n=temp.size();
int i=0;
while(i!=n)
{
temp.push_back(reflection_about_origin(temp[0].x,temp[0].y))
;

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
cout<<"Do you want to do Reflection about arbitrary

line? (y/n): ";
char u;
cin>>u;
if (u=='y')
{
cout<<"Arbitrary line is like y=m*x+c"<<endl;
cout<<"Enter value of m: ";
cin>>m;
cout<<"Enter value of c: ";
cin>>c;
cout<<"Chosen Line is y="<<m<<"*x + "<<c<<endl;
flag=1;
int n=temp.size();
int i=0;
while(i!=n)
{
temp.push_back(reflection_about_arbitrary_axis(temp[0].x,tem
p[0].y,m,c));

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
if(flag==1)
{
glColor3f(0.0,100.0,100.0);
glBegin(GL_LINE_LOOP);
glVertex2i(-250,m*(-250)+c);
glVertex2i(230,m*230+c);
glEnd();
}
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
glutCreateWindow("Reflection");
glutDisplayFunc(display);
myinit();
glutMainLoop();
}
