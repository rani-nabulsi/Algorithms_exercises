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
        fprintf(stderr, "Memory allocation error.\n");
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
int map_read(char *fname, element_t ***mapP, int *nr, int *nc) {
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
        for (j = 0; j < *nc; j++) {
            // reach each character and assign it to the map
            if (fscanf(fp, " %c", &map[i][j].value) == EOF) {
                fprintf(stderr, "Error while parsing the input file.\n");
                fclose(fp);
                return 0;
            }
            // initialize each cell as unvisited
            map[i][j].visited = 0;
        }
    }
    fclose(fp);  // close file after reading
    *mapP = map;  // set the pointer to the map
    return 1;
}

// function to evaluate length of snake
int length_evaluate(element_t **map, int nr, int nc, int r, int c) {
    int end = 0, length = 1;  // initialize length of snake to 1 (count of head)
    int found, r_new, c_new, i, j;

    // mark the head of the snake as visited
    map[r][c].visited = 1;

    // while the snake's head is visited
    while (!end) {
        found = 0; // reset found flag to search for the next body part
        // check the 8 surrounding cells for a snake body part (*)
        for (i = r - 1; i <= r + 1 && found == 0; i++) {
            for(j = c - 1; j <= c + 1 && found == 0; j++) {
                if (i >= 0 && i < nr && j >= 0 && j < nc) { // ensure we're inside the boundaries
                    if (map[i][j].value == '*' && map[i][j].visited == 0) { // the part is found and unvisited
                        found = 1;  // mark found
                        r_new = i;  // update new row and column for next iteration
                        c_new = j;
                    }
                }
            }
        }
        // if a part was found, continue with the next part
        if (found) {
            length++;  // increment snake length
            r = r_new;  // move to new position
            c = c_new;
            map[r][c].visited = 1;  // mark the new part as visited
        } else {
            end = 1;  // if no part was found, end the loop
        }
    }
    return length;  // return the length of the snake
}

int main(int argc, char *argv[]) {
    element_t **map;   // pointer to store the 2D map
    int nSnake = 0;   // variable to store number of snaked found
    int minLen = INT_MAX;  // variable to track the minimum length of any snake
    int maxLen = 0;  // variable to track the maximum length of any snake
    int nr, nc, i, j, length;  // variables for: number of rows, columns, iterations for loops

    // check if the file name is provided on the command line
    if (argc < 2) {
        printf("Error: Missing input fil.\n");
        return 1;
    }
    // call map_read to read the matrix and get the number of rows and cols
    if (!map_read(argv[1], &map, &nr, &nc)) {
        return 1;
    }
    // loop through each cell in the matrix
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            // if the cell contains a '+' (snake head) and hasn't been visited
            if (map[i][j].value == '+' && map[i][j].visited == 0) {
                nSnake++;  // increment snake counter
                // call length_evaluate to find the length of the snake, starting from its head
                length = length_evaluate(map, nr, nc, i, j);
                // update the minimum length if the current snake is shorter
                if (length < minLen) {
                    minLen = length;
                }
                // update the maximum length if the current snake is longer
                if (length > maxLen) {
                    maxLen = length;
                }
            }
        }
    }
    // free the dynamically allocated memory for the map
    free2d(map, nr);
    // output the final results: number of snakes, min, and max length
    printf("Snake number = %d\n", nSnake);  // print the number of snakes
    printf("Min length = %d\n", minLen);  // print the min snake length
    printf("Max length = %d\n", maxLen);  // print the max snake length

    return 0;
}