#pragma once
#include "vertex.h"

struct Loop {
	int id;	//id of loop
	Loop* pre;
	Loop* next;
	HalfEdge* halfedgelist;
	Face* face;		//this loop belong to which face

	Loop() :id(0), pre(NULL), next(NULL), halfedgelist(NULL), face(NULL) {}
};