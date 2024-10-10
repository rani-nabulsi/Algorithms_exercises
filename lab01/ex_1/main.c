/*
Exercise 01 (A and B)
---------------------

In Exercise 01 of Laboratory 00
given a list of words (stored in a file), it is required
to print out the number of times each word appears in a
text (stored in a second file).

Extend this program with dynamic allocation, i.e.
dynamically allocate an array of structures to store
the list of words read from file and their absolute
frequency.

The number of words stored in the second file is specified
on the first row of the file itself, for example:

3
watch
words
become

Write two versions of this program:

- Version A
Define the C structure as

typedef struct {
    char word[MAX_WORD_LENGTH+1];
    int occurrences;
} index_t;

- Version B
Define the C structure as

typedef struct {
    char *word;
    int occurrences;
} index_t;
*/

#include <stdlib.h>  // library for memory allocation
#include <stdio.h>
#include <string.h>
#include <ctype.h>  // Library for character operations

// Constants
#define MAX_WORD_LENGTH   20  // Maximum length for a word
#define MAX_WORD_NUMBER  100 // Maximum number of words to be stored in the index
#define MAX_LINE_LENGTH  100  // Maximum length for a line in the text file

/* structure declaration */
typedef struct {
    char word[MAX_WORD_LENGTH+1];  // Array to store a word (length + 1 for null terminator)
    int occurrences;  // int to store number of times the word appears in the text file
} index_t;

/* function prototypes */
void read_words(char *, index_t [], int *); // Reads words from the file and initializes the index array
void read_text(char *, index_t [], int); // Reads the text file and counts word occurrences based on the index
void display_index(index_t [], int); // Displays the index showing each word and its number of occurrences
int compare(char *, char *); // Compares two words in a case-insensitive manner

// main program
int main(int argc, char *argv[])
{
    index_t index[MAX_WORD_NUMBER];  // array of structures to hold the words and their occurrences count
    int n;  // variable to store number words read from file

    if (argc < 3) { // program name, 2 text files, 3 total
        printf("Error: missing parameter.\n"); // error message
        printf("Run as: %s <text_file> <word_file>\n", argv[0]); // Show the correct usage
        return EXIT_FAILURE;
    }

    read_words(argv[2], index, &n); // Call the function to read the words from the word file
    read_text(argv[1], index, n); // Call the function to read the text file and count occurrences of each word
    display_index(index, n); // Call the function to display the final results (word occurrences)

    return EXIT_SUCCESS;
}

/*
 *  read the words file; return the index array
 */
void read_words(char *name, index_t index[], int *num_ptr)  // name is the word file, index[] holds the words, num ptr is a pointer to store number of words
{
    FILE *fp; // file pointer
    int i;  // loop counter for reading words

    fp = fopen(name, "r");
    if (fp == NULL) {
        printf("Error opening file %s.\n", name);
        exit(EXIT_FAILURE);
    }

    i = 0; // initialize word counter to 0
    // read words from the file until EOF or max words limit is reached
    while (i<MAX_WORD_NUMBER && fscanf(fp, "%s", index[i].word)!=EOF) {
        index[i].occurrences = 0;  // initialize occurrence count for each word = 0
        i++; // increment
    }
    *num_ptr = i;  // Store the number of words read in the variable pointed by num_ptr and its address gets passed to the main

    fclose(fp);
    return;
}

/*
 *  read the text file; complete the index infos
 */
void read_text(char *name, index_t index[], int n) // n is the word count
{
    char word[MAX_LINE_LENGTH+1];  // stores each word from the text file
    int i, j;  // loop counters
    FILE *fp;  // file pointer to handle the text file
    fp = fopen(name, "r");
    if (fp == NULL) {
        printf("Error opening file %s.\n", name);
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%s", word) != EOF) {
        /* look for the word in the index */
        for (j=0; j<n; j++) {
            if (compare(word, index[j].word) == 1) { // if the words match (case-insensitive comparison)
                /* found an occurrence for a word */
                index[j].occurrences++;  // increment occurrence count for the word
            }
        }
    }

    fclose(fp);
}

/*
 *  output the index contents
 */
void display_index(index_t index[], int n) // index holds the words and their occurrence counts, n is the word count
{
    int i; // loop counter
    // loop through the word index and print each word with its occurrence count
    for (i=0; i<n; i++) {
        printf("%s - %d occurrence(s)\n", index[i].word, index[i].occurrences); // print the word and its count
    }
}

/*
 *  case insensitive comparison between two strings
 *  return 1 if the strings are equal, 0 otherwise
 */
int compare(char *str1, char *str2) // in the parameter the 2 strings to compare
{
    int i; // loop counter
    // first check if the strings are of the same length
    if (strlen(str1) != strlen(str2)) {
        return 0; // different lengths -> unequal strings
    }
    // comprare each character in the strings
    for (i=0; i<strlen(str1); i++) {
        if (tolower(str1[i]) != tolower(str2[i])) { // compare in lowercase for case-insensitivity
            return 0; // if any character is different -> unequal strings
        }
    }

    return 1;  // if all the chars are the same -> equal strings
}

/*
 1) read words: function reads words from a file and stores them in an array,
 initializing their occurrence count to 0, sets up the list of words you
 want to track in the text
 2) read_text: function reads a text file and checks how many times each word
 from the word list appears. counts occurrences of words in the texts and
 updates array
 3) display_index: function prints out each word from the list along
 with how many times it appeared in the text
 4) compare: function compares two words in a case-insensitive way
 treating uppercase and lowercase letters the same
 */