#include <stdlib.h>  // library for memory allocation
#include <stdio.h>
#include <string.h>
#include <limits.h>  // provides constant like INT_MAX (maximum value for int)

// structure definition for each element of the matrix
typedef struct {
    char value;  // to store the character position
    int visited;  // flag to check if this part of the snake has been visited
} element_t;

// function prototypes
element_t **malloc2d(int, int); // allocates memory for the 2D array
element_t **free2d(element_t **, int);  // frees the allocated memory of 2D array
int map_read(char*, element_t ***, int *, int *); // reads matrix from file and initializes map, rows & cols
int length_evaluate(element_t **, int, int, int, int);  // evaluates the length of a snake starting from a given head position

// function to allocate a 2D array of elements (matrix)
element_t **malloc2d(int r, int c) {
    int i;
    element_t **mat;

    // allocate memory for the array of row pointers
    mat = (element_t**)malloc(r * sizeof(element_t *));
    if (mat == NULL) {
        fprintf(stderr, "Memory allocation error.\n"):
        exit(EXIT_FAILURE);
    }
    // loop through each row and allocate memory for the columns
    for (i = 0; i < r; i++) {
        mat[i] = (element_t *) malloc(c * sizeof(element_t));
        if (mat[i] == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
    }
    return mat;
}

// function to free the allocated 2D array
element_t **free2d(element_t **mat, int r) {
    int i;

    // loop through each row and free its memory
    for (i = 0; i < r; i++) {
        free(mat[i]);  // free each row
    }
    free(mat);  // free the array of row pointers
    return NULL; // return NULL after freeing
}

// function to read the matrix from the file
int map_read(char *fname, element_t **mapP, int *nr, int *nc) {
    element_t **map;
    FILE * fp;
    int i, j;

    // open file for reading
    fp = fopen(fname, "r");
    if(fp == NULL) {
        fprintf(stderr, "File open error.\n", fname);
        return 0;
    }
    // read the number of rows and columns from the file
    if (fscanf(fp, "%d %d", nr, nc) != 2) {
        fprintf(stderr, "Error in parsing the input file.\n");
        fclose(fp);
        return 0;
    }

    // allocate memory for map
    map = malloc2d(*nr, *nc);
    // loop through the file to read each character into the matrix
    for(i = 0; i < *nr; i++) {

    }
}