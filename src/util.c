#include "../include/util.h"

int measure_dimensions(FILE* input_file) {
    int dimensions = 0;
    char* line = NULL;
    size_t line_size = 0;

    getline(&line, &line_size, input_file);

    char* token = strtok(line, ",");
    // Ignoring the point name
    while (token = strtok(NULL, ",")) {
        dimensions++;
    }

    free(line); // freeing line alocatted by getline
    fseek(input_file, 0, SEEK_SET); // Reset file pointer to start of file

    return dimensions;
}

int count_points(FILE* input_file) {
    int point_amt = 0;
    char* line = NULL;
    size_t line_size = 0;

    while (getline(&line, &line_size, input_file) > 0) {
        point_amt++;
    }

    free(line); // freeing line alocatted by getline
    fseek(input_file, 0, SEEK_SET); // Reset file pointer to start of file

    return point_amt;
}

Edge** generate_graph(int point_amt, Point** points) {
    int graph_size = point_amt * (point_amt-1) / 2; // n*(n-1)/2 possible edges to the MST
    
    Edge** graph = calloc(graph_size, sizeof(Edge*));

    int idx = 0;
    for (int i = 0; i < point_amt-1 ; i++) {
        for (int j = i+1; j < point_amt; j++) {
            graph[idx] = edge_init(points[i], points[j], point_get_distance(points[i], points[j]));
            idx++;
        }
    }

    return graph;
}

void process_MST(UT* ut, Edge** graph, int point_amt, int group_amt) {
    Point *p1, *p2;
    int graph_size = point_amt * (point_amt-1) / 2;
    int totalConnections =  point_amt - group_amt;
    int currConnections = 0;

    if (totalConnections == 0) return;

    for (int i = 0; i < graph_size; i++) {
        p1 = edge_get_p1(graph[i]);
        p2 = edge_get_p2(graph[i]);

        if (UT_find(ut, p1) != UT_find(ut, p2)) {
            UT_union(ut, p1, p2);
            currConnections++;
        }

        if (currConnections == totalConnections) break;
    }
}

Group** initialize_groups(UT* ut, int group_amt) {
    Group** groups = calloc(group_amt, sizeof(Group*));

    int root;
    int group_point_amt;
    int idx = 0;

    for (int i = 0; i < UT_get_size(ut) && idx < group_amt; i++) {
        group_point_amt = 0;
        root = UT_find_by_id(ut, i);
        int found = 0;

        // Checking if root hasnt already been found
        for (int j = 0; j < idx; j++) {
            if (group_get_id(groups[j]) == root) {
                found = 1;
            }
        }
        if (found) continue;
        else group_point_amt++;
        

        // Searching for other points containing the same root
        for(int j = i+1; j < UT_get_size(ut); j++){
            if (UT_find_by_id(ut, j) == root){
                group_point_amt++;
            }
        }

        // Initiliazing group with correct size and root
        groups[idx] = group_init(root, group_point_amt);
        idx++;
    }

    return groups;
}

Group** generate_groups(UT* ut, Point** points, int group_amt) {

    Group** groups = initialize_groups(ut, group_amt);

    for(int i = 0; i < UT_get_size(ut); i++) {
        for (int j = 0; j < group_amt; j++) {
            if (UT_find(ut, points[i]) == group_get_id(groups[j])) {
                group_add_point(groups[j], points[i]);
            }
        }
    }

    // Sorting points lexicographically in each group
    for (int i = 0; i < group_amt; i++) {
        qsort(group_get_points(groups[i]), group_get_amt(groups[i]), sizeof(Point*), compare_points);
    }

    // Sorting groups
    qsort(groups, group_amt, sizeof(Group*), compare_groups);

    return groups;
}

void print_groups(Group** groups, int group_amt, FILE* output_file) {
    for (int i = 0; i < group_amt; i++) {
        group_print(groups[i], output_file);
        fprintf(output_file, "\n");
    }
}