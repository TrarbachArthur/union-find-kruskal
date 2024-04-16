#ifndef UTIL_H
#define UTIL_H

#include "point.h"
#include "edge.h"
#include "union_tree.h"
#include "group.h"

int measure_dimensions(FILE* input_file);

int count_points(FILE* input_file);

Edge** generate_graph(int point_amt, Point** points);

void process_MST(UT* ut, Edge** graph, int point_amt, int group_amt);

Group** initialize_groups(UT* ut, int group_amt);

Group** generate_groups(UT* ut, Point** points, int group_amt);

void print_groups(Group** groups, int group_amt, FILE* output_file);

#endif