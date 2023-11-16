#pragma once
#include "vertex.h"

struct Edge {
	int id;	//id of edge
	Edge* pre;
	Edge* next;
	HalfEdge* lhe;	//left halfedge
	HalfEdge* rhe;	//right halfedge
	Solid* solid;	//this edge belong to which solid

	Edge() :id(0), pre(NULL), next(NULL), lhe(NULL), rhe(NULL) {}
};