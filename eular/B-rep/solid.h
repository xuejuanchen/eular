#pragma once
#include "vertex.h"
#include "loop.h"
#include "halfedge.h"
#include "edge.h"
#include "face.h"
#include <GL\glut.h>

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
		GLfloat colors[][3] = { {1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},
		{0.0,1.0,1.0},{1.0,0.0,1.0},{1.0,1.0,0.0} };
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