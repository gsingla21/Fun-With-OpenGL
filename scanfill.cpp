#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#define WINDOW_HEIGHT 500
/*The edge data structure*/
typedef struct tEdge {
int yUpper;
float xIntersect, dxPerScan;
struct tEdge * next;
} Edge;

typedef struct tdcPt {
int x;
int y;
} dcPt;

int cnt;
dcPt pts[60];

/* Inserts edge into list in order of increasing xIntersect field. */
void insertEdge (Edge * list, Edge * edge)
{
	Edge * p, * q = list;
	p = q->next;
	while (p != NULL)
	{
		if (edge->xIntersect < p->xIntersect)
			p = NULL;
		else
		{
			q = p;
			p = p->next;
		}
	}
	edge->next = q->next;
	q->next = edge;
}

/* Store lower-y coordinate and inverse slope for each edge. Adjust
and store upper-y coordinate for edges that are the lower member
of a monotically increasing or decreasing pair of edges */
void makeEdgeRec(dcPt lower, dcPt upper, int yComp, Edge * edge, Edge * edges[])
{
//Edge *q;
	edge->dxPerScan =(float) (upper.x - lower.x) / (upper.y - lower.y);
	edge->xIntersect = lower.x;
	if (upper.y < yComp)
		edge->yUpper = upper.y - 1;
	else
		edge->yUpper = upper.y;
	insertEdge (edges[lower.y], edge);
}

/* For an index, return y-coordinate of next nonhorizontal line */
int yNext (int k, int cnt, dcPt * pts)
{
	int j;
	if ((k+1) > (cnt-1))
		j = 0;
	else
		j = k + 1;
	while (pts[k].y == pts[j].y)
		if ((j+1) > (cnt-1))
			j = 0;
		else
			j++;
	return (pts[j].y);
}
void buildEdgeList (int cnt, dcPt * pts, Edge * edges[])
{
	Edge * edge;
	dcPt v1, v2;
	int i, yPrev = pts[cnt - 2].y;
	v1.x = pts[cnt-1].x; v1.y = pts[cnt-1].y;
	for (i=0; i<cnt; i++) 
	{
		v2 = pts[i];
		if (v1.y != v2.y) 
		{ /* nonhorizontal line */
			edge = (Edge *) malloc (sizeof (Edge));
			if (v1.y < v2.y) /* up-going edge */
				makeEdgeRec (v1, v2, yNext (i, cnt, pts), edge, edges);
			else /* down-going edge */
				makeEdgeRec (v2, v1, yPrev, edge, edges);
		}
		yPrev = v1.y;
		v1 = v2;
	}
}
void buildActiveList (int scan, Edge * active, Edge * edges[])
{
	Edge * p, * q;
	p = edges[scan]->next;
	while (p) {
		q = p->next;
		insertEdge (active, p);
		p = q;
	}
}
void fillScan (int scan, Edge * active)
{
	Edge * p1, * p2;
	int i;
	p1 = active->next;
	while (p1)
	{
		p2 = p1->next;
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_POINTS);
		for (i=p1->xIntersect; i<p2->xIntersect; i++)
			glVertex2i((int) i, scan);
		glEnd();
		p1 = p2->next;
	}
}
void deleteAfter (Edge * q)
{
	Edge * p = q->next;
	q->next = p->next;
	free (p);
}
/* Delete completed edges. Update 'xIntersect' field for others */
void updateActiveList (int scan, Edge * active)
{
	Edge * q = active, * p = active->next;
	while (p)
		if (scan >= p->yUpper)
		{
			p = p->next;
			deleteAfter (q);
		}
		else
		{
			p->xIntersect = p->xIntersect + p->dxPerScan;/*x=x+1/m*/
			q = p;
			p = p->next;
		}
}
void resortActiveList (Edge * active)
{
	Edge * q, * p = active->next;
	active->next = NULL;
	while (p)
	{
		q = p->next;
		insertEdge (active, p);
		p = q;
	}
}
void scanFill (int cnt, dcPt * pts)
{
	Edge * edges[WINDOW_HEIGHT], * active;
	int i, scan;
	for (i=0; i<WINDOW_HEIGHT; i++)
	{
		edges[i] = (Edge *) malloc (sizeof (Edge));
		edges[i]->next = NULL;
	}
	buildEdgeList (cnt, pts, edges);
	active = (Edge *) malloc (sizeof (Edge));
	active->next = NULL;
	for (scan=0; scan<WINDOW_HEIGHT; scan++)
	{
		buildActiveList (scan, active, edges);
		if (active->next)
		{	
			fillScan (scan, active);
			updateActiveList (scan, active);
			resortActiveList (active);
		}
	}
/* Free edge records that have been malloc'ed ... */
	free(active);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<cnt; i++)
	{
		glVertex2i(pts[i].x,pts[i].y);
	}
	glEnd();
	scanFill(cnt,pts);
	glFlush();
}
void myinit()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250,250,-250,250);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
	printf("Enter the no of points: ");
	scanf("%d",&cnt);
	printf("Enter the pts\n");
	for(int i=0;i<cnt; i++)
	{
		printf("x[%d] = ",i+1);
		scanf("%d",&pts[i].x);
		printf("y[%d] = ",i+1);
		scanf("%d",&pts[i].y);
	}
		
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("Scan Line Area Filling Algorithm");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}
