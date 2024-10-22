#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define C 100+2  // maximum string length (100) + '2' for \n and null terminator

//struct to store strings dynamically
typedef struct string_s {
    char *str;  // pointer to string
} string_t;

// prototypes
string_t *readInput(char *, int *);  // reads the input file and stores strings
void sortDMat(string_t *, int);  // sorts the strings alphabetically
void writeOutput(char *, string_t *, int);  // writes the sorted string in output file


int main(int argc, char *argv[]) {
    string_t *v;  // pointer to an array of structures that hold the strings
    int i, num;

    // check if the number of command line arguments is correct
    if (argc < 3) {
        printf("Error missing parameter.\n");
        printf("Run as: %s <input_file> <output_file>\n", argv[0]); // Prompt user for correct usage
        return EXIT_FAILURE;
    }
    // read input file + store strings in a dynamic array
    v = readInput(argv[1], &num);  // argv[1] is the input file, &num gets the #strings

    // sort array of strings
    sortDMat(v, num);   // sort the strings alphabetically

    // write the sorted strings to the output file
    writeOutput(argv[2], v, num);  // argv[2] is the output file

    // free dynamically allocated memory for each string
    for (i = 0; i < num; i++) {
        free(v[i].str);  // free each dynamically allocated string
    }
    // free array of structures
    free(v);  // free the entire structure array
    return EXIT_SUCCESS;
}

/*
function to read the input file
We pass the file name to open the file, and the pointer num_ptr allows us
to update the number of strings (n) directly in the calling function
*/
string_t *readInput(char *name, int *num_ptr) {
    char word[C];  // array to temporarily store each string that is being read
    string_t *v;  // pointer to an array of structs to hold the strings
    int n, i;
    FILE *fp;

    fp = fopen(name, "r");
    if (fp == NULL) {
        printf("Error in opening the file.\n", name);
        exit(EXIT_FAILURE);
    }
    *num_ptr = n;  // store the number of strings in the variable pointer by num_ptr

    // allocate memory for 'n' structures, each containing a dynamically allocated string
    v = (string_t *)malloc(n * sizeof(string_t));  // allocate array of structs
    if (v == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    // loop through the file to read each string
    i = 0;
    while(fscanf(fp, "%s", word)  && i < n) { // read each string from the file until 'n' strings are read
        // allocate memory for each string
        v[i].str = (char *)malloc((strlen(word)+1) * sizeof(char));
        if (v[i].str == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        // copy the string from 'word' which was held temporarily into the dynamically allocated space
        strcpy(v[i].str, word);
        i++;
    }
    fclose(fp);
    return v;
}

// function to sort the strings in alphabetical order (using insertion sort)
void sortDMat(string_t *v, int num) {
    int i, j;
    char *ptr;  // temporary pointer to store the string being inserted

    // start insertion sort from second element (index 1)
    for (i = 1; i < num; i++) {
        ptr = v[i].str;  // store the string at index 'i' in the temporary pointer
        j = 1;  // initialize j to the current index
        // shift elements to the right if they are greater than ptr
        while (--j >= 0 && strcmp(ptr, v[j].str) < 0) {
            v[j + 1].str = v[j].str;  // shift the string at index j to j+1
        }
        v[j+1].str = ptr;  // insert the string 'ptr' at the current position
    }
    return;
}

// function to write the sorted strings to output file
void writeOutput(char *name, string_t *v, int num) {
    FILE *fp;
    int i;

    fp = fopen(name, "w");
    if (fp == NULL) {
        printf("Error in opening file.\n");
        exit(EXIT_FAILURE);
    }
    // write the number of strings to the output
    fprintf(fp, "%d\n", num);
    // loop through the array of structs and write each string to the output file
    for (i = 0; i < num; i++) {
        fprintf(fp, "%s\n", v[i].str);
    }
    fclose(fp);
    return;
}