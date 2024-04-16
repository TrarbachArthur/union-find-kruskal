#ifndef EDGE_H
#define EDGE_H

#include "point.h"

typedef struct edge {
    double distance;
    int point_id1;
    int point_id2;
} Edge;

int compare_edges(const void* arg1, const void* arg2);

Edge edge_init(Point* p1, Point* p2, double distance);

void edge_destroy(Edge* e);

void edge_print(Edge* e);

//Getters

int edge_get_pid1(Edge e);
int edge_get_pid2(Edge e);
double edge_get_distance(Edge e);

int edge_sizeof();

#endif