#include <stdio.h>;
#include <stdlib.h>;
#include <assert.h>;
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


int getNumPoints(FILE *fptr) {
    int countPoints = 1;
    char ch;
    while (ch = fgetc(fptr) != EOF) {
        if (ch == '\n') {
            countPoints++;
        }
    }
    rewind(fptr);
    return countPoints;
}

int getNumCoordinates(FILE *fptr) {
    int countCoordinates = 1;
    char ch;
    while (ch = fgetc(fptr) != '\n') {
        if (ch == ',') {
            countCoordinates++;
        }
    }
    rewind(fptr);
    return countCoordinates;
}

void getPointsFromFile (int numPoints, int numCoordinates, FILE *fptr, double *points) {
    for (int pointIndex=0; pointIndex<numPoints; pointIndex++) {
        for (int coordinateIndex=0; coordinateIndex<numCoordinates; coordinateIndex++) {
            fscanf(fptr , "%lf,\n", points[pointIndex * numPoints]); //Reference: https://stackoverflow.com/questions/43286609/how-to-use-fscanf-to-read-doubles-in-c 
            //TODO: make sure this fscanf format actually catches all of our doubles
        }
    }
    
}



double *get_points (char *filename) {
    FILE *fptr;
    fptr = fopen(filename,"r");
    if (fptr != NULL) {
        int numPoints = getNumPoints(fptr);
        int numCoordinates = getNumCoordinates(fptr);

    //Allocate memory for 2D-array
    double *points = malloc(sizeof *points * numPoints * numCoordinates); //TODO: probably not the best way to allocate memory for 2D-array. Reference: https://stackoverflow.com/questions/9381711/how-to-declare-a-variable-size-2d-array-in-c
    
    //Fill array with parsed values from files
    getPointsFromFile(numPoints , numCoordinates , fptr , points);

    }

    fclose(fptr);
    
}

double getDistance (double *points, int startIndex1, int startIndex2, int numCoordinates) { //TODO: make sure we send  numCoordinates as parameters in main
    double distance = 0;
    for (int i=0; i<numCoordinates; i++) {
        distance += pow(points[startIndex1 + i] - points[startIndex2 + i], 2);
    }
    return distance;
}

int main(int argc, char **argv) { //argc = number of parameters (including program name), **argv = string array of parameters. Reference: https://stackoverflow.com/questions/29584898/c-getting-input-from-cmd
    //TODO: make sure how input is actually formatted
    assert (argc == 3 || argc = 4);
    int k, max_iter;
    char *filename;
    if (argc == 3) { //max_iter not passed as argument
        assert (atoi(argv[0] > 0));
        k = atoi(argv[0]);
        max_iter = 200;
        filename = argv[2];
    }
    else { //argc == 4
        assert (atoi(argv[1] > 0 && atoi(argv[2] > 0)); 
        k = atoi(argv[0]);
        max_iter = atoi(argv[1]);
        filename = argv[4];
    }

    //TODO: refactor getNumPoints & getNumCoordinates so they are called from main, FILE should also be created in main
    int numPoints = getNumPoints();
    int numCoordinates = getNumCoordinates();

    double *points = get_points(filename);
    double **centroids = malloc(k*numPoints);
    for (int i=0; i<k; i++) {
        
    }


    double *points = get_points("input_1.txt");
    printf("points[%d]" , 0);
}