#ifndef GROUP_H
#define GROUP_H

#include "point.h"
#include "union_tree.h"

typedef struct group Group;

int compare_groups(const void* arg1, const void* arg2);

Group* group_init(int group_id, int group_point_amt);

void group_add_point(Group* group, Point* p);

void group_print(Group* group, FILE* output_file);

void group_destroy(Group* group);

Point** group_get_points(Group* group);

int group_get_amt(Group* group);

int group_get_id(Group* group);

#endif