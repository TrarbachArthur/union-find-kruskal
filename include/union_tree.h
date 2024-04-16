#ifndef UNION_TREE
#define UNION_TREE

#include "point.h"

typedef struct union_tree UT;

UT* UT_init(int size);

void UT_union(UT* ut, Point* p1, Point* p2);

int UT_find(UT* ut, Point* p);

int UT_find_by_id(UT* ut, int id);

void UT_destroy(UT* ut);

int* UT_get_tree(UT* ut);

int UT_get_size(UT* ut);

#endif