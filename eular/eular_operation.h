#pragma once
#ifndef _EULAROPERATION.H
#include"halfedge_datastructure.h"
#include <vector>
using namespace std;

Solid* mvfs(double point[3]) {
	Solid* s = new Solid();
	Face* f = new Face();
	Loop* lpout = new Loop();
	Vertex* v = new Vertex(point[0], point[1], point[2]);
	v->id = s->vnum;
	f->id = s->fnum;
	lpout->id = s->lnum;
	s->vnum += 1;
	s->fnum += 1;
	s->lnum += 1;
	s->firstv = v;
	s->facelist = f;
	f->loopout = lpout;
	f->solid = s;
	lpout->face = f;
	return s;
}

HalfEdge* mev(Vertex* sv, double point[3], Loop* lp) {
	HalfEdge* half_l = new HalfEdge();
	HalfEdge* half_r = new HalfEdge();
	Edge* edge = new Edge();
	Vertex* ev = new Vertex(point[0], point[1], point[2]);
	Solid* s = lp->face->solid;
	ev->id = s->vnum;
	edge->id = s->ednum;
	s->vnum += 1;
	s->ednum += 1;
	s->newv = ev;
	half_l->vertex = sv;
	half_r->vertex = ev;
	half_l->edge = edge;
	half_r->edge = edge;
	half_l->brother = half_r;
	half_r->brother = half_l;
	edge->lhe = half_l;
	edge->rhe = half_r;
	edge->solid = s;
	half_l->loop = lp;
	half_r->loop = lp;
	sv->next = ev;
	ev->pre = sv;

	if (lp->halfedgelist == NULL) {
		half_l->next = half_r;
		half_r->next = half_l;
		half_l->pre = half_r;
		half_r->pre = half_l;
		lp->halfedgelist = half_l;
	}
	else {
		HalfEdge* half = lp->halfedgelist;
		while (half->next->vertex != sv)
			half = half->next;
		half_r->next = half->next;
		half->next->pre = half_r;
		half->next = half_l;
		half_l->pre = half;
		half_l->next = half_r;
		half_r->pre = half_l;
	}

	Edge* e = s->edgelist;
	if (e == NULL)
		s->edgelist = edge;
	else {
		while (e->next != NULL)
			e = e->next;
		e->next = edge;
		edge->pre = e;
	}
	return half_l;
}

Loop* mef(Vertex* sv, Vertex* ev, Loop* loop) {	
	Solid* solid = loop->face->solid;
	Edge* edge = new Edge();
	HalfEdge* half_l = new HalfEdge();
	HalfEdge* half_r = new HalfEdge();
	Face* face = new Face();
	Loop* newLoop = new Loop();
	edge->id = solid->ednum;
	face->id = solid->fnum;
	newLoop->id = solid->lnum;
	solid->ednum += 1;
	solid->fnum += 1;
	solid->lnum += 1;
	half_l->vertex = sv;
	half_r->vertex = ev;
	half_r->brother = half_l;
	half_r->brother = half_r;
	half_l->edge = edge;
	half_r->edge = edge;
	edge->lhe = half_l;
	edge->rhe = half_r;
	face->solid = solid;
	edge->solid = solid;
	newLoop->face = face;
	sv->next = ev;
	ev->pre = sv;
	HalfEdge* half = loop->halfedgelist;
	HalfEdge* halfa, *halfb;
	while (half->vertex != sv)
		half = half->next;
	halfa = half->pre;
	while (half->vertex != ev)
		half = half->next;
	halfb = half->pre;

	half_r->next = halfa->next;
	halfa->next->pre = half_r;
	halfa->next = half_l;
	half_l->pre = halfa;
	half_l->next = halfb->next;
	halfb->next->pre = half_l;
	halfb->next = half_r;
	half_r->pre = halfb;
	loop->halfedgelist = half_l;
	newLoop->halfedgelist = half_r;
	half_l->loop = loop;
	half_r->loop = newLoop;

	Face* f = solid->facelist;
	if (f == NULL)
		solid->facelist = face;
	else {
		while (f->next != NULL)
			f = f->next;
		f->next = face;
		face->pre = f;
	}

	if (face->loopout == NULL)
		face->loopout = newLoop;
	else {
		Loop* l = face->loopinlist;
		if (l == NULL)
			face->loopinlist = newLoop;
		else {
			while (l->next != NULL)
				l = l->next;
			l->next = newLoop;
			newLoop->pre = l;
		}
	}

	Edge* e = solid->edgelist;
	if (e == NULL)
		solid->edgelist = edge;
	else {
		while (e->next != NULL)
			e = e->next;
		e->next = edge;
		edge->pre = e;
	}
	return newLoop;
}

Loop* kemr(Vertex* sv, Vertex* ev, Loop* loop) {
	HalfEdge* hea, *heb, *he;
	Face* face = loop->face;
	Solid* s = face->solid;
	Loop* loopin = new Loop();
	he = loop->halfedgelist;
	while (he->vertex != sv || he->next->vertex != ev)
		he = he->next;
	hea = he;
	while (he->vertex != ev || he->next->vertex != sv)
		he = he->next;
	heb = he;
	heb->pre->next = hea->next;
	hea->next->pre = heb->pre;
	hea->pre->next = heb->next;
	heb->next->pre = hea->pre;
	loopin->halfedgelist = heb->pre;
	loopin->id = s->lnum;
	loopin->face = face;
	s->lnum += 1;
	Edge* e = hea->edge;
	Loop* l = face->loopinlist;
	if (l == NULL)
		face->loopinlist = loopin;
	else {
		while (l->next != NULL)
			l = l->next;
		l->next = loopin;
		loopin->pre = l;
	}
	e->pre->next = e->next;
	e->next->pre = e->pre;
	delete e;
	delete hea;
	delete heb;
	return loopin;
}

void kfmrh(Face* fa, Face* fb) {
	Loop* loop = fb->loopout;
	Loop* lp = fa->loopinlist;
	if (lp == NULL)
		fa->loopinlist = loop;
	else
	{
		while (lp->next != NULL)
			lp = lp->next;
		lp->next = loop;
		loop->pre = lp;
	}
	fa->solid->fnum -= 1;
	Solid* s = fa->solid;
	Face* face = s->facelist;
	if (face == fb)
		s->facelist = face->next;
	else {
		while (face != fb) {
			face = face->next;
		}
		face->pre->next = face->next;
	}
	delete fb;
}
#endif
