#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct point Point;

Point** read_points(char* input_file_name);

Point*  point_init(char* line, int dimensions, int point_id);

double point_get_distance(Point* p1, Point* p2);

void point_destroy(Point* p);

void point_print(Point* p);

// Getters

char* point_get_name(Point *p);
int point_get_id(Point *p);
int point_get_dimensions(Point* p);


#endif