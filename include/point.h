#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct point Point;

int compare_points(const void* arg1, const void* arg2);

Point** read_points(FILE* input_file, int point_amt, int dimensions);

Point*  point_init(char* line, int point_id, int dimensions);

double point_get_distance(Point* p1, Point* p2);

void point_destroy(Point* p);

void point_print(Point* p);

// Getters

char* point_get_name(Point *p);
int point_get_id(Point *p);
int point_get_dimensions(Point* p);


#endif