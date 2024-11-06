#include <stdio.h>
#include <stdlib.h>

// function prototypes
int **initializeMatrix(int );   // n x n matrix for generating the magic square
void magicSquare(int **, int );  // generates a magic square
void writeMatrix(int **, int, char *filename, int magicCst);  // writes the generated matrix into file
void freeMatrix(int **, int);  // frees dynamically allocated memory

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Error: %s <size of magic square (odd)> <output filename>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);  // string -> int
    // check if n is odd
    if (n <= 0 || n % 2 == 0) {
        printf("Error: n must be a positive ODD integer.\n");
        return 1;
    }

    // Calculate the magic constant using the given formula
    int magicCst = n * (n * n + 1) / 2;

    // Allocate memory and initialize the magic square matrix
    int **matrix = initializeMatrix(n);

    // generate square matrix
    magicSquare(matrix, n);

    // write the generated matrix to the specified file
    writeMatrix(matrix, n, argv[2], magicCst);

    // free dynamically allocated memory
    freeMatrix(matrix, n);

    return 0;
}

// initialize an n x n matrix, set all values to 0
int **initializeMatrix(int n) {
    // allocate memory for the row pointers (n rows)
    int **matrix = (int **) malloc(n * sizeof(int *));
    if (matrix == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // allocate memory for each row and initialize values to 0
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *) calloc(n, sizeof(int));
        if (matrix[i] == NULL) {
            printf("Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

// generate a magic square (works for odd n)
void magicSquare(int **matrix, int n) {
    int num = 1;
    int row = 0;
    int col = n/2;

    // Loop through numbers from 1 to n^2 to place each in the matrix
    while (num <= n * n) {
        matrix[row][col] = num;  // place current number in the matrix
        num++;  // increment to the next number

        // calculate next position
        int newRow = (row - 1 + n) % n;
        int newCol = (col + 1) % n;

        // if the calculated position is occupied, move down
        if (matrix[newRow][newCol] != 0) {
            row = (row + 1) % n;  // Move down one row
        } else {
            row = newRow;  // Move to the calculated row
            col = newCol;  // Move to the calculated column
        }
    }
}

// write the generated magic square into file
void writeMatrix(int **matrix, int n, char *filename, int magicCst) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error in opening file.\n", filename);
        exit(EXIT_FAILURE);
    }
    // Write the magic constant to the top of the file
    fprintf(fp, "Magic Constant: %d\n", magicCst);
    // Write the matrix row by row
    for (int i = 0; i < n; i++) {          // Loop over each row
        for (int j = 0; j < n; j++) {      // Loop over each column in the row
            fprintf(fp, "%d ", matrix[i][j]);  // Write the integer value followed by a space
        }
        fprintf(fp, "\n");  // Newline after each row
    }

    fclose(fp);  // Close the file after writing is complete
}

// free dynamically allocated memory
void freeMatrix(int **matrix, int n) {
    // Loop through each row and free the memory for each array of integers
    for (int i = 0; i < n; i++) {
        free(matrix[i]);  // Free each row array
    }

    // Free the array of pointers itself (matrix)
    free(matrix);
}
