#pragma once
#include "vertex.h"

struct Face {
	int id;	//id of face
	Face* next;
	Face* pre;
	Solid* solid;	//this face belong to which solid
	Loop* loopout;
	Loop* loopinlist;

	Face() :id(0), next(NULL), pre(NULL), solid(NULL), loopout(NULL), loopinlist(NULL) {}
};