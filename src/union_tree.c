#include "../include/union_tree.h"

struct union_tree {
    int* tree;
    int* sizes;
    int size;
};

UT* UT_init(int size) {
    UT* ut = calloc(1, sizeof(UT));
    ut->tree = calloc(size, sizeof(int));
    ut->sizes = calloc(size, sizeof(int));
    ut->size = size;

    // Initializing values for union find
    for (int i = 0; i < size; i++) {
        ut->tree[i] = i;
        ut->sizes[i] = 1;
    }

    return ut;
}

void UT_union(UT* ut, Point* p1, Point* p2) {
    int i = UT_find(ut, p1);
    int j = UT_find(ut, p2);

    if (i == j) return;

    if (ut->sizes[i] < ut->sizes[j]) {
        ut->tree[i] = j;
        ut->sizes[j] += ut->sizes[i];
    } else {
        ut->tree[j] = i;
        ut->sizes[i] += ut->sizes[j];
    }
}

int UT_find(UT* ut, Point* p) {
    int id = point_get_id(p);

    while (id != ut->tree[id]) {
        ut->tree[id] = ut->tree[ut->tree[id]];
        id = ut->tree[id];
    }

    return id;
}

int UT_find_by_id(UT* ut, int id) {
    while (id != ut->tree[id]) {
        ut->tree[id] = ut->tree[ut->tree[id]];
        id = ut->tree[id];
    }

    return id;
}

void UT_destroy(UT* ut) {
    free(ut->sizes);
    free(ut->tree);
    free(ut);
}

int* UT_get_tree(UT* ut) {
    return ut->tree;
}

int UT_get_size(UT* ut) {
    return ut->size;
}