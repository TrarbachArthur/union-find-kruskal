#ifndef EDGE_H
#define EDGE_H

#include "point.h"

typedef struct edge Edge;

int compare_edges(const void* arg1, const void* arg2);

Edge* edge_init(Point* p1, Point* p2, double distance);

void edge_destroy(Edge* e);

void edge_print(Edge* e);

//Getters

Point* edge_get_p1(Edge* e);
Point* edge_get_p2(Edge* e);
double edge_get_distance(Edge* e);

#endif