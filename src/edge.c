#include "../include/edge.h"

int compare_edges(const void* arg1, const void* arg2) {
    Edge e1 = *(Edge*) arg1;
    Edge e2 = *(Edge*) arg2;

    if (edge_get_distance(e1) < edge_get_distance(e2)) return -1;
    else if (edge_get_distance(e1) > edge_get_distance(e2)) return 1;
    return 0;
}

Edge edge_init(Point* p1, Point* p2, double distance) {
    Edge e;
    e.point_id1 = point_get_id(p1);
    e.point_id2 = point_get_id(p2);
    e.distance = distance;

    return e;
}

void edge_destroy(Edge* e) {
    free(e);
}

// Debug only function
void edge_print(Edge* e) {
    printf("%d -> %d = %lf\n", e->point_id1, e->point_id2, e->distance);
}

//Getters

int edge_get_pid1(Edge e) {
    return e.point_id1;
}
int edge_get_pid2(Edge e) {
    return e.point_id2;
}
double edge_get_distance(Edge e) {
    return e.distance;
}

int edge_sizeof() {
    return sizeof(Edge);
}