#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 1000

// struct for the linked list node
typedef struct node_p{
    char *word;  // pointer to dynamically allocate string
    int frequency;  // counter for how many times the word appears
    struct node_p *next;  // pointer to the next node in the list
} node_t;

// prototypes
node_t *insertHead(node_t *, char *);
node_t* findWord(node_t *, char *);
void writeListToFile(node_t *, char *);
void freeList(node_t *);
void toLowercase(char *);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Error, missing parameter.\n");
        printf("Run as: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE *fp;
    char word[MAX_WORD_LENGTH];
    node_t *head = NULL;  // Initialize the head of the linked list
    node_t *foundNode;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error in opening file.\n", argv[1]);
        return EXIT_FAILURE;
    }
    // scan the file
    while (fscanf(fp, "%s", word) != EOF) {
        toLowercase(word); // Convert the word to lowercase for case-insensitive comparison
        // check if word exists in the list
        foundNode = findWord(head, word);
        if (foundNode != NULL) {
            foundNode -> frequency++;  // Increment the frequency if found
        } else {
            // Insert the word at the head of the list if it's not found
            head = insertHead(head, word);
        }
    }
    fclose(fp);
    writeListToFile(head, argv[2]);  // write list in output file
    freeList(head);  // free the list from memory
    return EXIT_SUCCESS;
}

// function to insert a word at the head of the linked list
node_t *insertHead(node_t *head, char *word) {
    // create a new node
    node_t *newNode = (node_t *) malloc(sizeof(node_t));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // allocate memory for the word -> copy that word into the new node
    newNode -> word = (char *) malloc(strlen(word) + 1 * sizeof(char));
    if (newNode -> word == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode -> word, word);  // copies the word into the node
    newNode -> frequency = 1; // indicates that it is the first time we are adding this word
    newNode -> next = head; // insert new node at the head of the list
    return newNode;
}

// function to find a word in the linked list
node_t *findWord(node_t *head, char *word) {
    node_t *current = head;

    // loop the list searching for the word
    while (current != NULL) {
        if (strcmp(current -> word, word) == 0) {
            return current;  // return the node if word is found
        }
        current = current -> next; // move the pointer to the next node
    }
    return NULL;  // returns NULL if word is not found
}

// function to write the linked list in the output file
void writeListToFile(node_t *head, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error in opening file.\n");
        exit(EXIT_FAILURE);
    }
    node_t *current = head;

    // loop the list and write each word and its frequency to the file
    while (current != NULL) {
        fprintf(fp, "%s %d\n", current -> word, current -> frequency);
        current = current -> next;
    }
    fclose(fp);
}

// function to free the linked list
void freeList(node_t *head) {
    node_t *tmp;
    while (head != NULL) {
        tmp = head;
        head = head -> next;
        free(tmp -> word);
        free(tmp);
    }
}

// function to convert string to lowercase
void toLowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);  // Convert each character to lowercase
    }
}
