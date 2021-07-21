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
double z;
};
points translation(double x,double y,double z,double tx,double ty,double tz)
{
points r;
r.x=x+tx;
r.y=y+ty;
r.z=z+ty;

return r;
}

points scaling_about_origin(double x,double y,double z,double sx,double sy,double sz)
{
points r;
r.x=sx*x;
r.y=sy*y;
r.z=sz*z;

return r;
}

points scaling_about_pivot(double x, double y, double z, double xp,double yp,double zp,double sx,double sy,double sz)
{
points q;
q=translation(x,y,z,-xp,-yp,-zp);
q=scaling_about_origin(q.x,q.y,q.z,sx,sy,sz);
q=translation(q.x,q.y,q.z,xp,yp,zp);
return q;
}

points rotation_about_zaxis(double x,double y,double z,double theta)
{
points r;
double a,b;
theta=theta*3.14159/180;
a=cos(theta);
b=sin(theta);
r.x=x*a-y*b;
r.y=x*b+y*a;
r.z=z;
return r;
}
points rotation_about_xaxis(double x,double y,double z,double theta)
{
points r;
double a,b;
theta=theta*3.14159/180;
a=cos(theta);
b=sin(theta);
r.x=x;
r.y=y*a-z*b;
r.z=y*b+z*a;
return r;
}
points rotation_about_yaxis(double x,double y,double z,double theta)
{
points r;
double a,b;
theta=theta*3.14159/180;
a=cos(theta);
b=sin(theta);
r.x=z*b+x*a;
r.y=y;
r.z=z*a-x*b;
return r;
}

points rotation_about_arbitrary(double x,double y,double z,double a,double b, double c, double xp,double yp,double zp,double theta)
{
points q;
q=translation(x,y,z,-xp,-yp,-zp);
double d=sqrt(b*b+c*c);
double alpha=asin(b/d);
q=rotation_about_xaxis(q.x,q.y,q.z,alpha);
double L=sqrt(a*a+b*b+c*c);
double beta=asin(-a/L);
q=rotation_about_yaxis(q.x,q.y,q.z,beta);
q=rotation_about_zaxis(q.x,q.y,q.z,theta);

q=rotation_about_yaxis(q.x,q.y,q.z,-beta);
q=rotation_about_xaxis(q.x,q.y,q.z,-alpha);
q=translation(q.x,q.y,q.z,xp,yp,zp);

return q;
}

vector<vector<points> > allpoints;

vector<vector<points> > getpoints()
{
int m,n;
cout<<"Enter number of Faces: ";
cin>>n;
cout<<"Enter number of Points in each face: ";
cin>>m;
cout<<"Enter Points: \n";
vector<points> kal1;
vector<vector<points> > kal2;
int i,j;
for(i=0;i<n;i++)
{
cout<<"Face: "<<i+1<<endl;
for(j=0;j<m;j++)
{
	double x,y,z;
	cout<<"x"<<j<<": ";
	cin>>x;
	cout<<"y"<<j<<": ";
	cin>>y;
	cout<<"z"<<j<<": ";
	cin>>z;
	points alpha;
	alpha.x=x;
	alpha.y=y;
	alpha.z=z;
	kal1.push_back(alpha);
}
kal2.push_back(kal1);
kal1.clear();
}
return kal2;
}

vector<vector<points> > g;
vector<vector<points> > temp;
vector<vector<points> > menu(vector<vector<points> > temp)
{
cout<<"Menu: \n";
cout<<"Press 1 for Translation.\n";
cout<<"Press 2 for Scaling about origin.\n";
cout<<"Press 3 for Rotation about x-axis.\n";
cout<<"Press 4 for Rotation about y-axis.\n";
cout<<"Press 5 for Rotation about z-axis.\n";
cout<<"Press 6 for Scaling about pivot.\n";
cout<<"Press 7 for Rotation about pivot.\n";
cout<<"Press 8 for Show and Exit.\n";
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
		double tx,ty,tz;
		cout<<"Enter Values: \n";
		cout<<"x translate: ";
		cin>>tx;
		cout<<"y translate: ";
		cin>>ty;
		cout<<"z translate: ";
		cin>>tz;

		int n=temp.size();
		int m=temp[0].size();
		int i=0,j=0;
		while(i!=n)
		{
		for(j=0;j<m;j++)
		{
		temp[i].push_back(translation(temp[i][0].x,temp[i][0].y,temp[i][0].z,tx,ty,tz));
		temp[i].erase(temp[i].begin());
		}
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
		cout<<"Do you want to do Scaling about origin? (y/n): ";
		char u;
		cin>>u;
		if (u=='y') 
		{
		double sx,sy,sz;
		cout<<"Enter Values: \n";
		cout<<"x scale: ";
		cin>>sx;
		cout<<"y scale: ";
		cin>>sy;
		cout<<"z scale: ";
		cin>>sz;

		int n=temp.size();
		int m=temp[0].size();
		int i=0,j=0;
		while(i!=n)
		{		
		for(j=0;j<m;j++)
		{
		temp[i].push_back(scaling_about_origin(temp[i][0].x,temp[i][0].y,temp[i][0].z,sx,sy,sz));
		temp[i].erase(temp[i].begin());
		}
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
		cout<<"Do you want to do Rotation about xaxis? (y/n): ";
		char u;
		cin>>u;
		if (u=='y') 
		{
		double theta;
		cout<<"Enter Values: \n";
		cout<<"theta: ";
		cin>>theta;		
		
		int n=temp.size();
		int m=temp[0].size();
		int i=0,j=0;
		while(i!=n)
		{
		for(j=0;j<m;j++)
		{
		temp[i].push_back(rotation_about_xaxis(temp[i][0].x,temp[i][0].y,temp[i][0].z,theta));
		temp[i].erase(temp[i].begin());
		}
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
		cout<<"Do you want to do Rotation about yaxis? (y/n): ";
		char u;
		cin>>u;
		if (u=='y') 
		{
		double theta;
		cout<<"Enter Values: \n";
		cout<<"theta: ";
		cin>>theta;		
		
		int n=temp.size();
		int m=temp[0].size();
		int i=0,j=0;
		while(i!=n)
		{
		for(j=0;j<m;j++)
		{
		temp[i].push_back(rotation_about_yaxis(temp[i][0].x,temp[i][0].y,temp[i][0].z,theta));
		temp[i].erase(temp[i].begin());
		}
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
		cout<<"Do you want to do Rotation about zaxis? (y/n): ";
		char u;
		cin>>u;
		if (u=='y') 
		{
		double theta;
		cout<<"Enter Values: \n";
		cout<<"theta: ";
		cin>>theta;		
		
		int n=temp.size();
		int m=temp[0].size();
		int i=0,j=0;
		while(i!=n)
		{
		for(j=0;j<m;j++)
		{
		temp[i].push_back(rotation_about_zaxis(temp[i][0].x,temp[i][0].y,temp[i][0].z,theta));
		temp[i].erase(temp[i].begin());
		}
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
	{		
		cout<<"Do you want to do scaling about pivot? (y/n): ";
		char u;
		cin>>u;
		if (u=='y') 
		{
		double sx,sy,sz,xp,yp,zp;
		cout<<"Enter Values: \n";
		cout<<"x pivot: ";
		cin>>xp;
		cout<<"y pivot: ";
		cin>>yp;
		cout<<"z pivot: ";
		cin>>zp;
		cout<<"x scale: ";
		cin>>sx;			
		cout<<"y scale: ";
		cin>>sy;
		cout<<"z scale: ";
		cin>>sz;
		
		int n=temp.size();
		int m=temp[0].size();
		int i=0,j=0;
		while(i!=n)
		{
		for(j=0;j<m;j++)
		{
		temp[i].push_back(scaling_about_pivot(temp[i][0].x,temp[i][0].y,temp[i][0].z,xp,yp,zp,sx,sy,sz));
		temp[i].erase(temp[i].begin());
		}
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
case 7:
	{
		cout<<"Do you want to do Rotation about Arbitrary? (y/n): ";
		char u;
		cin>>u;
		if (u=='y') 
		{
		double theta,xp,yp,zp,a,b,c;
		cout<<"Enter Values: \n";
		cout<<"Enter parameter of ai + bj + ck: \n";
		cout<<"a pivot: ";
		cin>>a;		
		cout<<"b pivot: ";
		cin>>b;
		cout<<"c pivot: ";
		cin>>c;
		cout<<"x pivot: ";
		cin>>xp;
		cout<<"y pivot: ";
		cin>>yp;
		cout<<"z pivot: ";
		cin>>zp;
		cout<<"theta: ";
		cin>>theta;
		
		int n=temp.size();
		int m=temp[0].size();
		int i=0,j=0;
		while(i!=n)
		{
		for(j=0;j<m;j++)
		{
		temp[i].push_back(rotation_about_arbitrary(temp[i][0].x,temp[i][0].y,temp[i][0].z,a,b,c,xp,yp,zp,theta));
		temp[i].erase(temp[i].begin());
		}
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
case 8:
	break;
default:
	{
		cout<<"Invalid Input";
		temp=menu(temp);	
	}
}
return temp;
}

vector<vector<points> > process()	
{
temp=allpoints;
temp=menu(temp);

return temp;
}

void display() {
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0, 0.0, 0.0);

glBegin(GL_LINE_LOOP);
glVertex3i(-320,0,0);
glVertex3i(320,0,0);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3i(0,-240,0);
glVertex3i(0,240,0);
glEnd();

glBegin(GL_LINE_LOOP);
glVertex3i(0,0,-320);
glVertex3i(0,0,320);
glEnd();

glColor3f(0.0, 100.0, 0.0);

int i=0,j=0;
for(i=0;i<allpoints.size();i++)
{
glBegin(GL_LINE_LOOP);
for(j=0;j<allpoints[0].size();j++)
{
glVertex3i(allpoints[i][j].x,allpoints[i][j].y,allpoints[i][j].z);
}
glEnd();
}

i=0,j=0;
for(i=0;i<g.size();i++)
{
glColor3f(100.0, 100.0, 0.0);
glBegin(GL_LINE_LOOP);
for(j=0;j<g[0].size();j++)
{
glVertex3i(g[i][j].x,g[i][j].y,g[i][j].z);
}
glEnd();
}

glFlush();
}

void myinit() {
glClearColor(1.0, 1.0, 1.0, 0.0);
glColor3f(0.0, 0.0, 0.0);
glPointSize(4.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glOrtho(-320.0, 320.0, -240, 240.0,-320,320);

gluLookAt(100, 100, 100, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv) {

allpoints=getpoints();
g=process();
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(640, 480);
glutInitWindowPosition(100, 150);

glutCreateWindow("3D Transformations");
glutDisplayFunc(display);
myinit();

glutMainLoop();

}
