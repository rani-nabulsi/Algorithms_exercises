#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 21  // #max length for each string + null terminator

// function prototypes
// char *** means a pointer to a pointer to a pointer to a character (a 3D array, or a matrix of strings)
char ***read_file(int *Rptr, int *Cptr); // function to read the matrix from a file abd return the matrix + its dimensions
char **merge_matrix(char ***matrix, int R, int C);  // function to merge the rows of the matrix into one sorted array
void print_result(char **array, int dim);  // function to print final result into output file
// frees the 3D array of strings and the final 2D array of strings
void free_memory(char ***matrix, char **array, int R, int C);  // function to free all dynamically allocated memory


int main(void) {
    char ***matrix, **array;  // matrix pointer -> 3D array, array pointer -> 2D array
    int R, C;

    matrix = read_file(&R, &C);  // read the matrix from input and pass addresses
    array = merge_matrix(matrix, R, C);  // merge the sorted rows from the matrix into a single sorted array
    print_result(array, R * C); // print the sorted array to output file
    free_memory(matrix, array, R, C); // free all dynamically allocated memory

    return EXIT_SUCCESS;
}

// function to read matrix from input file
char ***read_file(int *Rptr, int *Cptr) {
    char word[MAX_LEN],  ***mx;  // mx 3D array of strings to be dynamically allocated
    int r, c, i, j;
    FILE *fp;

    printf("Input file name: ");
    scanf("%s", word);  // read file name into buffer

    fp = fopen(word, "r");
    if (fp == NULL) {
        printf("Error opening the input file.\n");
        exit(EXIT_FAILURE);
    }
    // read matrix dimensions (#rows * #cols)
    fscanf(fp, "%d %d", &r, &c);  // read first 2 integers

    // allocate memory for 3D array of strings
    // allocate memory for row of pointers (first)
    mx = (char ***) malloc(r * sizeof(char **)); // each row is a pointer to a 2D array of strings
    if (mx == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    // for each row, allocate memory for C column pointers (each pointing to a string)
    for (i = 0; i < r; i++) {
        mx[i] = (char **) malloc(c * sizeof(char *));  // allocate memory for C strings in each row
        if (mx[i] == NULL) {
            printf("Memory allocation error");
            exit(EXIT_FAILURE);
        }
    }

    // fill the matrix by reading strings from the file
    for (i = 0; i < r; i++) { // outer loop: iterate over each row (i)
        for (j = 0; j < c; j++) { // inner loop: iterate over each column (j)
            fscanf(fp, "%s", word);  // read each string into buffer
            // ensure each row is sorted: compare with the previous string in the row
            if ((j < 0) && (strcmp(mx[i][j - 1], word) > 0)) { // if the previous string is greater -> error
                printf("Error: row %d NOT SORTED.\n", i+1);
                exit(EXIT_FAILURE);
            }
            // copy the string from 'word' into matrix (use strdup to duplicate into allocated memory)
            mx[i][j] = strdup(word);
            if (mx[i][j] == NULL) {
                printf("Memory allocation error");
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(fp);
    // pass the row and column values to main
    *Rptr = r;
    *Cptr = c;
    return mx; // returns 3D array of strings
}

// function to merge the matrix rows into a sorted array
char **merge_matrix(char ***matrix, int R, int C) {
    int i, j, min_indx, *indx;  // min_indx stores the index of the row with the smallest string in each iteration
                                // indx is an array used to track the current position in each row while merging
   char **array, *min_word;   // array is the final sorted array of strings, min_words points to the current smallest string (being merged)

   // allocate memory for the final sorted array + index array (after merging)
   array = (char **) malloc(R * C * sizeof(char *));   // allocate memory for the array of R*C strings
   indx = (int *) calloc(R, sizeof(int));  // allocate + initialize the index array for each row to 0
   if ((array == NULL) || (indx == NULL)) {
       printf("Memory allocation error.\n");
       exit(EXIT_FAILURE);
   }
   // merging process: merge the rows into 1 sorted array
   i = 0;
   // this loop will run until all strings from all rows are merged into final array
   while (i < R * C) { // continues until we have merged R*C strings (tot #strings)
       min_indx = -1;  // reset to -1 before each iteration

       // iterate over each row to find the smallest string among each row
       for (j = 0; j < R; j++) { // j = row index
           if (indx[j] < C) { // check if we haven't exhausted the current row
               // if this is the first valid string we're comparing or the current string is smaller than min_word
               if ((min_indx == -1) || (strcmp(matrix[j][indx[j]], min_word) < 0)) {
                   min_indx = j;  // set min_indx to the current row with the smallest string
                   min_word = matrix[min_indx][indx[min_indx]];  // Set min_word to the smallest string found so far
               }
           }
       }
       // add the smallest string found (min_word) to the final array and increment the corresponding index in that row
       array[i++] = matrix[min_indx][indx[min_indx]++]; // Add the string from matrix[min_indx] at idx[min_indx] to array[i], then increment both i and indx[min_idx]
   }
    free(indx);  // free the index array as we no longer need it
    return array;  // returns the final sorted array
}

// function to print to output file
void print_result(char **array, int dim) {
    char name[MAX_LEN];
    FILE *fp;
    int i;

    printf("Output file name: ");
    scanf("%s", name);

    // open file for writing
    fp = fopen(name, "w");
    if (fp == NULL) {
        printf("Error opening output file.\n");
        exit(EXIT_FAILURE);
    }
    // write the tot #strings (dim) as the first line of the output file
    fprintf(fp, "%d\n", dim);

    // write each string in the array to the file, one string per line
    for (i = 0; i < dim; i++) {
        fprintf(fp, "%s\n", array[i]);
    }
    fclose(fp);
}

// function to free all dynamically allocated memory
void free_memory(char ***matrix, char **array, int R, int C) {
    int i, j;

    // free each string in the 3D array of strings
    for (i = 0; i < R; i++) { // loop over each row
        for (j = 0; j < C; j++) { // loop over each column within each row
            free(matrix[i][j]);  // free each string (allocated by strdup)
        }
        free(matrix[i]);  // free the array of string pointers for each row
    }

    free(matrix);  // free the array of row pointers
    free(array);   // free the final array of sorted strings
}