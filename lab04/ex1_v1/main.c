// lab 05v1
// magic square nxn matrix: m = n(n^2 + 1)/ 2
// number from 1 -> n^2 is used only once

#include <stdio.h>
#include <stdlib.h>

// function prototypes
void *my_calloc(int q, int size);   // Allocates memory and checks for errors
void print_matrix(FILE *output, int **mat, int n);  // prints generated matrix to output file
int magic(int **mat, int *u, int n, int lev);   // recursive function to generate the magic square
int check_matrix(int **mat, int n);   // checks if the matrix is a magic square

int main(int argc, char **argv) {
    int i, n;  // loop variable + size of magic square (n x n)
    int **square;  // pointer to the 2D matrix for the magic square
    int *used;   // array to track which numbers (1 -> n^2) are used

    if (argc != 3) {
        fprintf(stderr, "Not enough parameters");
        exit(-1);
    }

    // parse the size of the magic square from command-line
    n = atoi(argv[1]);   // convert first argument (string) to integer

    // allocate memory for the 'used' array to track used numbers
    used = (int *)my_calloc(n * n, sizeof(int));

    // allocate memory for the 2D matrix (square)
    square = (int **)my_calloc(n, sizeof(int *));  // allocate memory for rows
    for (i = 0; i < n; i++) {
        square[i] = (int *)my_calloc(n, sizeof(int));   // allocate memory for columns in each row
    }

    // generate the magic square using backtracking
    if (magic(square, used, n, 0) == 1) {
        FILE *out = fopen(argv[2], "w");
        print_matrix(out, square, n);  // print magic square to file
        fclose(out);
    }

    // free allocated memory
    for (i = 0; i < n; i++) {
        free(square[i]);   // free memory for each row
    }
    free(square);    // free memory for thr matrix
    free(used);     // free memory for the 'used' array

    return 0;
}


// function to allocate memory and handle errors
void *my_calloc(int q, int size) {
    void *mem = calloc(q, size);   // allocate 'q * size' bytes of memory
    if (mem == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(-1);
    }
    return mem;     // returns the allocated mem
}

// function to print matrix to output file
void print_matrix(FILE *output, int **mat, int n) {
    for (int x = 0; x < n; x++) {  // loop through rows
        for (int y = 0; y < n; y++) {  // loop through columns
            fprintf(output, "%2d ", mat[x][y]);  // print each number (with spacing)
        }
        fprintf(output, "\n");
    }
}


// function to check if the matrix is a magic square
int check_matrix(int **mat, int n) {
    int sum = -1; // Stores the magic constant (sum of rows/columns/diagonals)

    // Check all rows
    for (int x = 0; x < n; x++) {
        int parz = 0; // Partial sum of the current row
        for (int y = 0; y < n; y++) {
            parz += mat[x][y]; // Add each element in the row
        }
        if (sum == -1) // If this is the first row, set the magic constant
            sum = parz;
        if (parz != sum) // If the row sum is not equal to the magic constant, return 0
            return 0;
    }

    // Check all columns
    for (int y = 0; y < n; y++) {
        int parz = 0; // Partial sum of the current column
        for (int x = 0; x < n; x++) {
            parz += mat[x][y]; // Add each element in the column
        }
        if (parz != sum) // If the column sum is not equal to the magic constant, return 0
            return 0;
    }

    // Check both diagonals
    int parz1 = 0; // Sum of the main diagonal
    int parz2 = 0; // Sum of the secondary diagonal
    for (int x = 0; x < n; x++) {
        parz1 += mat[x][x];         // Main diagonal
        parz2 += mat[n - 1 - x][x]; // Secondary diagonal
    }
    if (parz1 != sum || parz2 != sum) // If diagonal sums are not equal to the magic constant
        return 0;

    return 1; // If all checks pass, return 1
}


// recursive function to generate the magic square
int magic(int **mat, int *u, int n, int lev) {
    static int count = 0;    // tracks the number of recursive calls
    count++;

    if (lev == n * n) {  // base case: akk cells are filled
        if (check_matrix(mat, n) == 1) {  // check if the matrix is a valid magic square
            printf("Magic! (count: %d)\n", count);
            print_matrix(stdout, mat, n);  // print the magic square to output file
            return 1;  // success
        }
        return 0;  // fail
    }

    int x, y;
    // compute row and column from the level
    x = lev / n;  // row index
    y = lev % n;  // col index

    // trying to place each number (1 -> n^2) in the current cell
    for (int i = 0; i < n * n; i++) {
        if (u[i] == 0) {  // Check if the number is unused
            u[i] = 1; // Mark the number as used
            mat[x][y] = i + 1; // Place the number in the matrix

            // Recursive call to the next level
            if (magic(mat, u, n, lev + 1) == 1) {
                return 1; // Return success if a solution is found
            }

            // Backtracking: undo changes
            mat[x][y] = 0; // Remove the number from the cell
            u[i] = 0; // Mark the number as unused
        }
    }

    return 0; // Return failure if no solution is found
}

