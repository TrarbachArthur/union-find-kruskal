#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/point.h"
#include "../include/edge.h"
#include "../include/util.h"

int main(int argc, char const *argv[])
{
    if (argc < 4) {
        printf("Use the correct template!\n");
        return 1;
    }

    const char* input_file_path = argv[1];
    int group_amt = atoi(argv[2]);
    const char* output_file_path = argv[3];

    FILE* input_file = fopen(input_file_path, "r");

    if (input_file == NULL) {
        printf("Unable to open input file!\n");
        exit(1);
    }

    int dimensions = measure_dimensions(input_file);
    int point_amt = count_points(input_file);

    clock_t read_start = clock();
    Point** points = read_points(input_file, point_amt, dimensions);
    clock_t read_end = clock();

    fclose(input_file); // Closing input file (useless from now on)

    clock_t calc_distance_start = clock();
    Edge* graph = generate_graph(point_amt, points);
    clock_t calc_distance_end = clock();


    clock_t sort_edges_start = clock();
    // Amount of edges = Lower diagonal of the distances matrix
    int edge_amt = (point_amt * (point_amt-1)) / 2; // N*(N-1)/2
    qsort(graph, edge_amt, edge_sizeof(), compare_edges);
    clock_t sort_edges_end = clock();


    clock_t mst_start = clock();
    UT* ut = UT_init(point_amt);
    process_MST(ut, graph, point_amt, group_amt);
    clock_t mst_end = clock();

    // graph is useless from now on
    // Makes a little more memory available
    free(graph);

    clock_t grouping_start = clock();
    // Generating and sorting groups
    Group** groups = generate_groups(ut, points, group_amt);
    clock_t grouping_end = clock();


    FILE* output_file = fopen(output_file_path, "w");

    if (output_file == NULL) {
        printf("Unable to open output file!\n");
        exit(1);
    }

    clock_t print_start = clock();
    print_groups(groups, group_amt, output_file);
    clock_t print_end = clock();

    double read_time = ((double)read_end - read_start)/CLOCKS_PER_SEC;
    double distance_time = ((double)calc_distance_end - calc_distance_start)/CLOCKS_PER_SEC;
    double sort_time = ((double)sort_edges_end - sort_edges_start)/CLOCKS_PER_SEC;
    double mst_time = ((double)mst_end - mst_start)/CLOCKS_PER_SEC;
    double grouping_time = ((double)grouping_end - grouping_start)/CLOCKS_PER_SEC;
    double print_time = ((double)print_end - print_start)/CLOCKS_PER_SEC;

    printf("Tempo de leitura dos dados: %lf\n", read_time);
    printf("Tempo de calculo das distancias: %lf\n", distance_time);
    printf("Tempo de ordenacao das distancias: %lf\n", sort_time);
    printf("Tempo de obtencao da mst: %lf\n", mst_time);
    printf("Tempo de identificacao dos grupos: %lf\n", grouping_time);
    printf("Tempo de escrita do arquivo de saida: %lf\n", print_time);

    // Freeing memory up
    fclose(output_file);

    UT_destroy(ut); 

    for (int i = 0; i < group_amt; i++) {
        group_destroy(groups[i]);
    }
    free(groups);
    // Freeing groups takes care of freeing all the Point*
    free(points);

    return 0;
}