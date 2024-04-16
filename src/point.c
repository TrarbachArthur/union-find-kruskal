#include "../include/point.h"
#include <math.h>

struct point {
    int id;
    int dimensions;
    char* name;
    double* coordinates;
};

int compare_points(const void* arg1, const void* arg2) {
    Point* p1 = *(Point**) arg1;
    Point* p2 = *(Point**) arg2;

    return strcmp(p1->name, p2->name);
}

Point** read_points(FILE* input_file, int point_amt, int dimensions) {
    int points_read = 0;

    Point** points = calloc(point_amt, sizeof(Point*));

    char* line = NULL;
    size_t line_size = 0;
    while(getline(&line, &line_size, input_file) > 0) {
        if (points_read >= point_amt) break;

        points[points_read] = point_init(line, points_read, dimensions);
        points_read++;
    }

    free(line);

    return points;
}

Point* point_init(char* line, int point_id, int dimensions) {
    Point* p = calloc(1, sizeof(Point));

    p->id = point_id;
    p->dimensions = dimensions;
    p->coordinates = calloc(p->dimensions, sizeof(double));

    char* token = strtok(line, ",");
    p->name = strdup(token);

    int i = 0;
    while(token = strtok(NULL, ",")) {
        if (i > dimensions) break; // Making sure no invalid write happens
        p->coordinates[i] = atof(token);
        i++;
    }

    return p;
}

double point_get_distance(Point* p1, Point* p2) {
    double distance = 0;
    double aux = 0;
    for (int i = 0; i < point_get_dimensions(p1); i++) {
        aux = p1->coordinates[i] - p2->coordinates[i];
        distance += aux * aux;
    }

    return sqrt(distance);
}

void point_destroy(Point* p) {
    if (p) {
        free(p->name);
        free(p->coordinates);
        free(p);
    }
}

void point_print(Point* p) {
    printf("%s\n", p->name);
}

// Getters

char* point_get_name(Point *p) {
    return p->name;
}
int point_get_id(Point *p) {
    return p->id;
}
int point_get_dimensions(Point* p) {
    return p->dimensions;
}