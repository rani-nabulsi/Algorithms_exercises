// lab03_ex1
// implementing part A (head insertion)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>   // Character functions (tolower, isalpha, isdigit)

#define WORD_SIZE 100    // const for the maximum size of a word

typedef struct wordS{
    char *word;  // pointer to string
    int freq;   // counts occurrences
    struct wordS *next;  // pointer to the next node in the linked list
} wordT;

// function prototypes
wordT *listCreate(FILE *);
int compareStrings(char *, char *);
wordT *findWord(wordT *, char *);
void cleanWord(char *);
void writeList(wordT *, FILE *);
void cleanUp(wordT *);
wordT *push(wordT *, char *);


int main(int argc, char *argv[]) {
    FILE *fpR, *fpW;
    wordT *headP = NULL;  // head pointer of the linked list (NULL initialization)

    if (argc > 2) {
        fpR = fopen(argv[1], "r");
        fpW = fopen(argv[2], "w");

        if (fpR == NULL || fpW == NULL) {
            printf("Error in opening files.\n");
            return 1;
        }

        // create linked list by reading words from input file
        headP = listCreate(fpR);

        // write the linked list into the output file
        writeList(headP, fpW);

        fclose(fpR);
        fclose(fpW);

        // free up all allocated memory
        cleanUp(headP);
    } else {
        printf("Wrong Parameters.\n");
    }
    return 0;
}

// function to create linked list from the input file
wordT *listCreate(FILE *fp) {
    wordT *headP = NULL, *tmpP;
    char buffer[WORD_SIZE + 3];  // buffer to store each word

    while((fscanf(fp, "%s", buffer)) != EOF) {
        cleanWord(buffer);  // clean the word (remove non-alphanumeric characters)
        tmpP = findWord(headP, buffer);  // search for the word in the list

        // if word is found -> increment frequency
        if (tmpP != NULL) {
            tmpP -> freq++;
        } else {
            // if the word is not found -> insert it into the list
            headP = push(headP, buffer);
        }
    }
    return headP;  // return the head pointer of the list
}

// function to insert a new node at the head of the list
wordT *push(wordT *headP, char *buffer) {
    wordT *newP;

    // allocate memory for new node
    newP = malloc(sizeof(wordT));
    if (newP == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // allocate memory for the word and copy the word into the node
    newP -> word = malloc((strlen(buffer) + 1) * sizeof(char));
    if (newP -> word == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newP -> word, buffer);
    newP -> freq = 1;          // initialize frequency to q
    newP -> next = headP;     // link the new node to the current head
    return newP;
}

// function to clean the word by removing non-alphanumeric characters
void cleanWord(char *word) {
    int i, j, n = strlen(word);
    for (i = 0; word[i] != '\0'; i++) {
        if (!isalpha(word[i]) && !isdigit(word[i])) {
            for (j = i; j < n; j++) {
                word[j] = word[j + 1];  // shift chars left to remove non-alphanumeric chars
            }
        } else {
            i++;  // move to the next character
        }
    }
    for (i = 0; word[i] != '\0'; i++) {
        word[i] = tolower(word[i]);  // convert the word to lowercase
    }
}

// function to write the list (word + frequency) in the output file
void writeList(wordT *headP, FILE *fp) {
    while (headP != NULL) {
        fprintf(fp, "%s %d\n", headP -> word, headP -> freq);   // word & frequency
        headP = headP -> next;    // move to the next node
    }
}

// function to clean up dynamically allocated memory
void cleanUp(wordT *headP) {
    wordT *tmpP;

    while (headP != NULL) {
        tmpP = headP;
        headP = headP -> next;
        free(tmpP -> word);    // free allocated memory for the word
        free(tmpP);           // free the node itself
    }
}