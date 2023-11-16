#pragma once
#include "vertex.h"

struct HalfEdge {
	Edge* edge;	//this halfedge belong to which edge
	Loop* loop;	//this halfegde belong to which loop
	Vertex* vertex;	//the begin vertex of halfedge
	HalfEdge* brother;
	HalfEdge* pre;
	HalfEdge* next;

	HalfEdge() :edge(NULL), pre(NULL), next(NULL), brother(NULL), loop(NULL), vertex(NULL) {}
};