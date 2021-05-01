//
// Created by galam on 30/04/2021.
//
#include <stdlib.h>
#include "kmeans.h"

typedef enum HasChangedEnum {
    TRUE = 1,
    FALSE = 0
} HasChanged;


void reset_array_double(double * arr, int size) {
    for (int i = 0; i < size; ++i) {
        *(arr + i) = 0;
    }
}

void reset_array_int(int * arr, int size) {
    for (int i = 0; i < size; ++i) {
        *(arr + i) = 0;
    }
}

double* split_points_to_clusters(double* centroids, double* points, int point_size, int k, int points_num) {
    double min_distance, distance;
    int min_centroid;
    double* new_centroids = (double *)calloc(sizeof(double ), point_size * k);
    reset_array_double(new_centroids, point_size * k)
    int* clusters_count = (int *)calloc(sizeof(int), k);
    reset_array_int(clusters_count, k)
    for (int i = 0; i < points_num; ++i) { // iterate points
        min_centroid = 0;
        min_distance = get_distance(centroids, points, 0, i);
        for (int j = 1; j < k; ++j) { // check min distance from all the centroids
            distance = get_distance(centroids, points, (j * point_size), i);
            if (distance < min_distance) {
                min_distance = distance;
                min_centroid = j;
            }
        }
        for (int l = 0; l < point_size; ++l) { // sum points
            *(new_centroids + (j * point_size) + l) += *(points + i + l);
        }
        *(clusters_count + min_centroid) ++; // increase counter
    }
}

HasChanged calculate_new_centroids(double *centroids, double *new_centroids, int* centroids_count, int point_size, int k) {
    HasChanged has_changed = FALSE
    for (int i = 0; i < k; ++i) { // calculate average
        for (int j = 0; j < point_size; ++j) {
            *(new_centroids + (i * point_size) + j) = *(new_centroids + (i * point_size) + j) / *(centroids_count + i);
            if (*(new_centroids + (i * point_size) + j) != *(centroids + (i * point_size) + j)) {
                has_changed = TRUE;
            }
        }
    }
    return has_changed;
}







