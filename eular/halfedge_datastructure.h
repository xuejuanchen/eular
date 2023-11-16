#ifndef _HALFEDGE_STRUCTUR_H
#define _HALFEDGE_STRUCTUR_H

#include <stdlib.h>

struct Solid;
struct Face;
struct Loop;
struct HalfEdge;
struct Vertex;
struct Edge;



struct Vertex {

	int id;	//id of vertex
	double coord[3];	//coordinate of vertex
	Vertex* pre;
	Vertex* next;
	HalfEdge* halfedge;	//this vertex belong to which halfedge

	Vertex(double x, double y, double z) :id(0), next(NULL), pre(NULL), halfedge(NULL) {
		coord[0] = x;
		coord[1] = y;
		coord[2] = z;
	}
};

struct HalfEdge {
	Edge* edge;	//this halfedge belong to which edge
	Loop* loop;	//this halfegde belong to which loop
	Vertex* vertex;	//the begin vertex of halfedge
	HalfEdge* brother;
	HalfEdge* pre;
	HalfEdge* next;

	HalfEdge() :edge(NULL), pre(NULL), next(NULL), brother(NULL), loop(NULL), vertex(NULL) {}
};

struct Edge {
	int id;	//id of edge
	Edge* pre;
	Edge* next;
	HalfEdge* lhe;	//left halfedge
	HalfEdge* rhe;	//right halfedge
	Solid* solid;	//this edge belong to which solid

	Edge() :id(0), pre(NULL), next(NULL), lhe(NULL), rhe(NULL) {}
};

struct Loop {
	int id;	//id of loop
	Loop* pre;
	Loop* next;
	HalfEdge* halfedgelist;	
	Face* face;		//this loop belong to which face

	Loop() :id(0), pre(NULL), next(NULL), halfedgelist(NULL), face(NULL) {}
};

struct Face {
	int id;	//id of face
	Face* next;
	Face* pre;
	Solid* solid;	//this face belong to which solid
	Loop* loopout;
	Loop* loopinlist;

	Face() :id(0), next(NULL), pre(NULL), solid(NULL), loopout(NULL), loopinlist(NULL) {}
};

struct Solid {
	Solid() : vnum(0), fnum(0), lnum(0), ednum(0), facelist(NULL), edgelist(NULL), firstv(NULL), newv(NULL), next(NULL), pre(NULL) {}
	void wirepaint()
	{
		glBegin(GL_LINES);
		Edge* tmp;
		tmp = this->edgelist;
		while (tmp)
		{
			glVertex3f(tmp->lhe->vertex->coord[0], tmp->lhe->vertex->coord[1], tmp->lhe->vertex->coord[2]);	
			glVertex3f(tmp->rhe->vertex->coord[0], tmp->rhe->vertex->coord[1], tmp->rhe->vertex->coord[2]);
			tmp = tmp->next;
			if (tmp == NULL)
			{
				break;
			}
		}
		glEnd();
	}

	void solidpaint()
	{
		Face* tmp;
		Loop* lp;
		GLfloat colors[][3] = { {2.0,0.0,0.0},{0.0,3.0,0.0},{0.0,0.0,7.0},
		{0.0,4.0,4.0},{3.0,0.0,3.0},{2.0,2.0,0.0} };
		int Coptions;
		tmp = this->facelist;
		HalfEdge* he;
		Coptions = 0;
		while (tmp)
		{
			glBegin(GL_POLYGON);
			lp = tmp->loopout;
			he = lp->halfedgelist;
			Coptions = Coptions % 6;
			glColor3fv(colors[Coptions]);
			while (he)
			{
				glVertex3f(he->vertex->coord[0], he->vertex->coord[1], he->vertex->coord[2]);
				he = he->next;
				if (he == lp->halfedgelist)
				{
					break;
				}
			}
			Coptions++;
			glEnd();
			tmp = tmp->next;
			if (tmp == this->facelist)
			{
				break;
			}
		}
	}
	Face* facelist;
	Edge* edgelist;
	Vertex* firstv;
	Vertex* newv;
	Solid* next;
	Solid* pre;
	int fnum;
	int lnum;
	int vnum;
	int ednum;
};

static Solid* solidlist = NULL;
void  AddToSolidList(Solid* s)
{
	if (solidlist == NULL)
	{
		solidlist = s;
	}
	else
	{
		s->next = solidlist;
		s->pre = solidlist->pre;
		solidlist->pre->next = s;
		solidlist->pre = s;
	}
}
#endif


