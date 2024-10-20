#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// macro to calculate the total elements of a 2D array (R*C)
#define max(R,C) ((R>C)?R:C)  // macro

// prototypes
char **malloc2d(int, int); // dynamically allocates 2D array of chars
char **free2d(char **, int);  // frees the allocated memory
void find(char *, char **, char **, int, int);  // searches for words in a matrix
int find_all(int, int, char *, char **, char **, int, int);  // helper function to find words

int main(int argc, char *argv[]) {
    char **matrixIn, **matrixOut;  // pointers to store input and output matrices
    char *word;  // pointer to store the word read from the second file
    int i, j, R, C;   // variables to loop + Dimensions
    FILE *fp;

    // check for the correct number of arguments
    if (argc < 4) {
        fprintf(stderr, "Error: Missing parameter.\n");
        fprintf(stderr, "Run as: %s <matrixfile> <wordfile> <outputFile>\n", argv[0]);
        return 1;
    }
    // open first file (matrix input) for reading
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Error in opening file (file= %s).\n", argv[1]);
        return 1;
    }
    // read the matrix dimensions from the file
    if (fscanf(fp, "%d%d%c", &R, &C) == EOF) {
        fprintf(stderr, "Error in reading file.\n");
        return 1;
    }
    // dynamically allocate memory for the input and output matrices
    matrixIn = malloc2d(R, C);
    matrixOut = malloc2d(R, C);
    word = (char *) malloc((max(R,C)+1) * sizeof(char));

    if (word == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    // read the matrix from the file and store it in matrixIn
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            fscanf(fp, "%c", &matrixIn[i][j]);
        }
        fscanf(fp, "%*c");  // skip the "newline" char
    }
    fclose(fp);

    // open the second file (word list) for reading
    fp = fopen(argv[2], "r");
    if (fp == NULL) {
        fprintf(stderr, "Error in opening file (file= %s).\n", argv[2]);
        return 1;
    }
    // read each word from the word file and search for it in the matrix
    while (fscanf(fp, "%s", word) != EOF) {
        find(word, matrixIn, matrixOut, R, C);    // Call the find function to search
    }
    fclose(fp);    // Close the word file

    // Open the output file in write mode
    fp = fopen(argv[3], "w");
    if (fp == NULL) {
        fprintf(stderr, "File open error (file=%s).\n", argv[3]);
        return 1;
    }

    // Write the output matrix (matrixOut) to the output file
    for (i=0; i<R; i++) {
        for (j=0; j<C; j++) {
            fprintf(fp, "%c", matrixOut[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);    // Close the output file

    // free dynamically allocated memory

    return 0;
}

// function to dynamically allocate 2D array
char **malloc2d(int r, int c) {
    int i, j;
    char **mat;  // pointer to a pointer that will hold the 2D matrix

    // allocate memory for row pointers
    mat = (char **)malloc(r * sizeof(char *));
    if (mat == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    // for each row, I allocate memory for columns
    for (i = 0; i < r; i++) {
        mat[i] = (char *)malloc(c * sizeof(char));
        if (mat[i] == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
    }
    // initialize the matrix with empty spaces
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            mat[i][j] = ' ';
        }
    }
    return mat;  // return the direct pointer to the 2D array
}

// function to free dynamically allocated 2D array
char **free2d(char **mat, int r) {
    int i;
    // free each row of the matrix
    for (i = 0; i < r; i++) {
        free(mat[i]);
    }
    // free the array of row pointers
    free(mat);
    return mat;
}

// function to find a word in the input matrix and place it in the output matrix
void find(char *word, char **matrixIn, char **matrixOut, int R, int C) {
    int i, j;
    // iterate over each element in the matrix and try to find the word
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            // if a match is found, copy the word into the output matrix
            if (find_all(i, j, word, matrixIn, matrixOut, R, C)) {
                return;
            }
        }
    }
    return;
}

// helper function to find if a ward existing starting from a given matrix position
int find_all(int row, int col, char *word, char **mIn, char **mOut, int R, int C) {
    char flag; // to indicate if the word is found
    int r, c, i, j;
    int offset[2][8] = {   // Offset array for the 8 possible directions (x and y changes)
            {0, -1, -1, -1, 0, 1, 1, 1},
            {1, 1, 0, -1, -1, -1, 0, 1}
    };
    // loop through all 8 possible directions
    for (i = 0; i < 8; i++) {
        flag = 1;  // set flag to true (initially)
        // check if the word matches in this direction
        for (j = 0; j < strlen(word) && flag; j++) {
            r = row + j * offset[0][i];  // update row based on direction
            c = col + j * offset[1][i];  // update column based on direction
            // check if the indices are out of bounds or the characters don't match
            if (r < 0 || r >= R || c < 0 || c >= C || mIn[r][c] != word[j]) {
                flag = 0;  // not a match -> flag=false
            }
        }
        // if the word is found -> copy it to the output matrix
        if (flag == 1) {
            for (j = 0; j < strlen(word); j++) {
                mOut[row+j*offset[0][i]][col+j*offset[1][i]] = word[j];
            }
            return 1;  // true if the word is found
        }
    }
    return 0;  // false is the word is not found
}