#pragma once
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