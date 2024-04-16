#include "../include/edge.h"

struct edge {
    double distance;
    Point* p1;
    Point* p2;
};

int compare_edges(const void* arg1, const void* arg2) {
    Edge* e1 = *(Edge**) arg1;
    Edge* e2 = *(Edge**) arg2;

    if (edge_get_distance(e1) < edge_get_distance(e2)) return -1;
    else if (edge_get_distance(e1) > edge_get_distance(e2)) return 1;
    return 0;
}

Edge* edge_init(Point* p1, Point* p2, double distance) {
    Edge* e = calloc(1, sizeof(Edge));
    e->p1 = p1;
    e->p2 = p2;
    e->distance = distance;

    return e;
}

void edge_destroy(Edge* e) {
    free(e);
}

void edge_print(Edge* e) {
    printf("%s -> %s = %lf\n", point_get_name(e->p1), point_get_name(e->p2), e->distance);
}

//Getters

Point* edge_get_p1(Edge* e) {
    return e->p1;
}
Point* edge_get_p2(Edge* e) {
    return e->p2;
}
double edge_get_distance(Edge* e) {
    return e->distance;
}