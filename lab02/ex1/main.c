// VERSION A (1D array)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;  // pointer to hold dynamically allocated string
} string_t;

// function prototypes
void insertionSort(string_t *string, int n);
string_t *readStrings(FILE *FIN, int *n_str);
void writeStrings(FILE *FOUT, string_t *string, int n);
void freeStrings(string_t *string, int n);

// function to read strings from input file
string_t *readStrings(FILE *FIN, int *n_str) {
    int n, i; // #strings & loop counter
    char buffer[100];
    string_t *string;

    fscanf(FIN, "%d", &n);  // read number of strings from the first line
    *n_str = n;
    string = (string_t *)malloc(n * sizeof(string_t));
    if (string == NULL) {  // handle memory allocation failure
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    // Loop to read each string from the input file
    for (i = 0; i < n; i++) {
        fscanf(FIN, "%s", buffer);  // read the string into the buffer
        string[i].str = (char *)malloc((strlen(buffer) + 1) * sizeof(char));  // dynamically allocate memory for the string
        if (string[i].str == NULL) {  // handle memory allocation failure
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        strcpy(string[i].str, buffer);  // copy the string into the struct
    }

    return string;  // return the array of structs
}

// Function to perform insertion sort on array of structs
void insertionSort(string_t *string, int n) {
    int i, j;  // loop counters
    string_t key;  // temporary struct to hold the key string during sorting

    // Insertion sort algorithm
    for (i = 1; i < n; i++) {
        key = string[i];  // take the current string as key
        j = i - 1;

        // Shift elements greater than key to the right
        while (j >= 0 && strcmp(string[j].str, key.str) > 0) {
            string[j + 1] = string[j];
            j--;
        }

        string[j + 1] = key;  // place the key in its correct position
    }
}
// Function to write sorted strings to output file
void write_strings(FILE *FOUT, string_t *string, int n) {
    int i;  // loop counter
    fprintf(FOUT, "%d\n", n);  // write the number of strings

    // Loop to write each string
    for (i = 0; i < n; i++) {
        fprintf(FOUT, "%s\n", string[i].str);  // write the string
    }
}

// Function to free allocated memory
void freeStrings(string_t *string, int n) {
    int i;  // loop counter

    // Free each dynamically allocated string
    for (i = 0; i < n; i++) {
        free(string[i].str);  // free the string inside each struct
    }
    free(string);
}

// main function
int main(int argc, char *argv[]) {
    FILE *FIN, *FOUT;
    string_t *string;  // dynamic array of structs
    int n;  // #strings

    if (argc != 3) {
        fprintf(stderr, "error.\n", argv[0]);
        return EXIT_FAILURE;
    }
    FIN = fopen(argv[1], "r");
    if (FIN == NULL) {
        fprintf(stderr, "Error in opening input file\n");
        return EXIT_FAILURE;
    }
    string = readStrings(FIN, &n);
    fclose(FIN);

    insertionSort(string, n);

    FOUT = fopen(argv[2], "w");
    if (FOUT == NULL) {
        fprintf(stderr, "Error in opening output file\n");
        return EXIT_FAILURE;
    }
    writeStrings(FOUT, string, n);
    fclose(FOUT);

    freeStrings(string, n);
    return EXIT_SUCCESS;
}

