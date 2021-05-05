#include <stdio.h>;
#include <stdlib.h>;
#include <assert.h>;
#include <kmeans.h>; //TODO: why is this here? Commenting out derives several errors in code


typedef enum HasChangedEnum {
    TRUE = 1,
    FALSE = 0
} HasChanged;


/*** Function Declaration ***/

int get_num_points(FILE *fptr);
int get_num_coordinates(FILE *fptr);
void get_points_from_file (int numPoints, int numCoordinates, FILE *fptr, double *points);
void reset_array_double(double * arr, int size);
void reset_array_int(int * arr, int size);
double* split_points_to_clusters(double* centroids, double* points, int point_size, int k, int points_num);
HasChanged calculate_new_centroids(double *centroids, double *new_centroids, int* centroids_count, int point_size, int k);
double get_distance (double *points, int startIndex1, int startIndex2, int numCoordinates);


/*** Main Function ***/

int main(int argc, char **argv) { 
    //argc = number of parameters (including program name), **argv = string array of parameters. Reference: https://stackoverflow.com/questions/29584898/c-getting-input-from-cmd
    //TODO: make sure how input is actually formatted
    assert (argc == 3 || argc = 4);
    int k, max_iter;
    char *filename;
    int numPoints, numCoordinates;

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

    FILE *fptr;
    fptr = fopen(filename,"r");
    if (fptr != NULL) {
        numPoints = get_num_points(fptr);
        numCoordinates = get_num_coordinates(fptr);
    }

    double *points = malloc(sizeof *points * numPoints * numCoordinates); //TODO: probably not the best way to allocate memory for 2D-array. Reference: https://stackoverflow.com/questions/9381711/how-to-declare-a-variable-size-2d-array-in-c
    get_points_from_file(numPoints, numCoordinates, fptr, points);

    fclose(fptr);

    // initiate the centroids to be the first k points
    double *centroids = malloc(sizeof *centroids k * numPoints);
    for (int i=0; i<k; i++) {
        for (int j=0; j< numCoordinates; j++) {
            centroids[i*numCoordinates + j] = points[i*numCoordinates + j] 
        }
    }

    while (max_iter > 0) {
        split_points_to_clusters (centroids, points, numCoordinates, k, numPoints);
        if (calculate_new_centroids(centroids, , , k == FALSE)) { //TODO: what should "new_centroids" and "controid_count" parameters be? 
            max_iter = 0; //breaks the loop
        } 
        max_iter -= 1;
    }

    //print final centroids
    for (int i=0; i<k; i++) {
        int j = 0;
        while (j < numCoordinates -1) {
            printf ("%lf," , centroids[i*numCoordinates + j]);
            j++;
        }
        printf ("%lf/n" , centroids[i*numCoordinates + j]) //print last coordinate
    }

    return 0;

}


/*** Function Implementation ***/

int get_num_points(FILE *fptr) {
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

int get_num_coordinates(FILE *fptr) {
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

void get_points_from_file (int numPoints, int numCoordinates, FILE *fptr, double *points) {
    for (int pointIndex=0; pointIndex<numPoints; pointIndex++) {
        for (int coordinateIndex=0; coordinateIndex<numCoordinates; coordinateIndex++) {
            fscanf(fptr , "%lf,\n", points[pointIndex * numCoordinates + coordinateIndex]); //Reference: https://stackoverflow.com/questions/43286609/how-to-use-fscanf-to-read-doubles-in-c 
            //TODO: make sure this fscanf format actually catches all of our doubles
        }
    }
    
}


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

    //TODO: what about return value?
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



double get_distance (double *points, int startIndex1, int startIndex2, int numCoordinates) { //TODO: adjust parameter to the function use in split_points_to_clusters
    double distance = 0;
    for (int i=0; i<numCoordinates; i++) {
        distance += pow(points[startIndex1 + i] - points[startIndex2 + i], 2);
    }
    return distance;
}


