#ifndef UNION_TREE
#define UNION_TREE

#include "point.h"

typedef struct union_tree UT;

UT* UT_init(int size);

void UT_union(UT* ut, Point* p1, Point* p2);

int UT_find(UT* ut, Point* p);

void UT_destroy(UT* ut);

#endif