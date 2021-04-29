#include <stdio.h>;
#include <stdlib.h>;
#include <assert.h>;



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
    for (int i=0; i<numPoints; i++) {
        fscanf(fptr , "%lf,%lf,%lf\n", points[i * numPoints] , points[i * numPoints + 1] , points[i * numPoints + 2]); //Reference: https://stackoverflow.com/questions/43286609/how-to-use-fscanf-to-read-doubles-in-c 
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

int main() {
    double *points = get_points("input_1.txt");
    printf("points[%d]" , 0);
}

// int getMaxLenCoordinate (FILE *fptr) {
//     int maxLen = 0, currentLen = 0;
//     char ch;
//     while (ch == fgetch(fptr) != EOF) {
//         if (ch == ',' || ch == '\n') { //End of coordinate
//           if (currentLen > maxLen) {
//               maxLen = currentLen;
//           }
//           currentLen = 0;  
//         }
//         else {
//             currentLen++;
//         }
//     }

//     if (currentLen>maxLen) {
//         maxLen = currentLen;
//     }

//     return maxLen;



// double charArrayToDouble (char[] coordinate) { // make sure if it's working with the '\0' at the end
//     double output;
//     sscanf (coordinate, "%lf",&output);
//     return output;
// }



// double getPointsFromFile[][] (double[][] *output, FILE *fptr) {
//     char ch;
//     char[] coordinate[getMaxLenCoordinate(fptr)];
//     double[][] point[sizeof(output[0])];
//     int coordinateIndex = 0, pointIndex = 0, outputIndex = 0;
//     while (ch == fgetch(fptr) != EOF) { //iterate through entire file
//         if (ch == '\n') {
//             coordinate[coordinateIndex] = '\0';
//             point[pointIndex] = charArrayToDouble(coordinate);
//             coordinateIndex = 0;
//             pointIndex = 0;
//             output[outputIndex++] = point;
//         }
//         if (ch == ',') {
//             coordinate[coordinateIndex] = '\0';
//             point[pointIndex++] = charArrayToDouble(coordinate);
//             coordinateIndex = 0;
//         }
//         else {
//             coordinate[coordinateIndex++] = ch;
//         }
//     }
//     coordinate[coordinateIndex] = '\0';
//     point[pointIndex] = charArrayToDouble(coordinate);
//     output[outputIndex++] = point;
//     return output;

// }

