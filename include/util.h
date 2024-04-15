#ifndef UTIL_H
#define UTIL_H

#include "union_tree.h"
#include "edge.h"

Edge** generate_graph(int point_amt, Point** points);

void process_MST(UT* ut, Edge** graph);

Point** generate_groups(UT* ut, int group_amt);

void print_groups(Point** groups, int group_amt, char* output_file_path);

#endif