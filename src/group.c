#include "../include/group.h"

struct group {
    Point** points;
    int point_amt;
    int curr_points;
    int id;
};

int compare_groups(const void* arg1, const void* arg2) {
    Group* g1 = *(Group**) arg1;
    Group* g2 = *(Group**) arg2;

    return (strcmp(point_get_name(g1->points[0]), point_get_name(g2->points[0])));
}

Group* group_init(int group_id, int group_point_amt) {
    Group* g = calloc(1, sizeof(Group));
    g->id = group_id;
    g->curr_points = 0;
    g->point_amt = group_point_amt;
    g->points = calloc(g->point_amt, sizeof(Point*));
}

void group_add_point(Group* group, Point* p) {
    if (group->curr_points >= group->point_amt) return;

    group->points[group->curr_points] = p;
    group->curr_points++;
}

void group_print(Group* group, FILE* output_file) {
    for (int i = 0; i < group->curr_points; i++) {
        if (i != 0) fprintf(output_file, ",");
        fprintf(output_file, "%s", point_get_name(group->points[i]));
    }
}

void group_destroy(Group* group) {
    for (int i = 0; i < group->curr_points; i++) {
        point_destroy(group->points[i]);
    }
    free(group->points);
    free(group);
}

Point** group_get_points(Group* group) {
    return group->points;
}

int group_get_amt(Group* group) {
    return group->point_amt;
}

int group_get_id(Group* group) {
    return group->id;
}