// Exercise 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// maximum buffer size for input lines
#define MAX 100

// characters representing different elements in the maze
#define EMPTY ' '    // walkable space (i.e corridor)
#define START '@'   // starting position of the human
#define STOP '#'   // maze exit
#define PATH '$'  // mark for the current path during exploration

// Offsets for moving in 4 directions (up, right, down, left)
const int xOff[4] = {0, 1, 0, -1};  // horizontal changes
const int yOff[4] = {-1, 0, 1, 0};  // vertical changes

// function prototypes
void display(char **maze, int nr);  // display the maze
int move_recur(char **mazeCurr, int stepCurr, char **mazeBest, int stepBest,
               int nr, int nc, int row, int col);  // recursive backtracking function
FILE *util_fopen(char *name, char *mode);  // file opening utility
void *util_malloc(int size);  // memory allocation utility
char *util_strdup(char *src);  // duplicate string with memory allocation


// main program
// reads the maze, initializes data structures, and starts recursive process
int main(int argc, char *argv[]) {
    int r = -1, c = -1, i, j, nr, nc, step;
    char **mazeCurr, **mazeBest;  // current and best maze states
    char line[MAX];   // buffer for reading lines
    FILE *fp;  // file pointer for input file

    if (argc < 2) {
        printf("Error: missing parameter.\n");
        printf("Run as: %s <maze_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // open the maze file
    fp = util_fopen(argv[1], "r");

    // read maze dimensions (# rows & cols)
    fgets(line, MAX, fp);
    sscanf(line, "%d %d", &nr, &nc);

    // allocate memory for the maze arrays
    mazeCurr = (char **) util_malloc(nr * sizeof(char *));
    mazeBest = (char **) util_malloc(nr * sizeof(char *));
    for (i = 0; i < nr; i++) {
        fgets(line, MAX, fp);  // reads line from input file
        mazeCurr[i] = util_strdup(line);   // duplicate into mazeCurr
        mazeBest[i] = util_strdup(line);   // duplicate into mazeBest
        for (j = 0; i < nr; i++) {
            if (mazeCurr[i][j] == START) {  // locate starting position
                mazeCurr[i][j] = ' ';  // replace the starting symbol with space
                r = i;  // records starting row
                c = j;  // records starting col
            }
        }
    }

    // check if starting pos is found
    if (r < 0 || c < 0) {
        printf("Error: no starting position was found!\n");
        exit(EXIT_FAILURE);
    }

    // find the shortest path using recursive function
    step = move_recur(mazeCurr, 0, mazeBest, nr * nc, nr, nc, r, c);

    // display the result based on whether a path was found
    if (step > 0) {
        printf("Solution:\n");
        mazeBest[r][c] = START;  // restore starting position
        display(mazeBest, nr);  // display the maze with the path
    } else {
        printf("NO SOLUTION FOUND!\n");
    }

    // free allocated memory for the maze
    for (r = 0; r < nr; r++) {
        free(mazeCurr[r]);
        free(mazeBest[r]);
    }
    free(mazeCurr);
    free(mazeBest);

    return EXIT_SUCCESS;
}


// recursive function to explore all possible paths in the maze
int move_recur(char **mazeCurr, int stepCurr, char **mazeBest, int stepBest,
               int nr, int nc, int row, int col) {
    int k, r, c;   // loop variables and new position variables

    //Base case: if stepCurr (current steps) is greater than or equal to
    // stepBest (shortest steps found so far), stop exploring further.
    if (stepCurr >= stepBest) {
        return stepBest;  // return the best steps so far without further exploration
    }

    // check if the current cell is the exit point
    if (mazeCurr[row][col] == STOP) {
        if (stepCurr < stepBest) {  // If the current path is better than the best so far
            stepBest = stepCurr;    // Update the best step count
            // copy the current maze state to the best maze
            for (int r = 0; r < nc; r++) {
                for (int c = 0; c < nc; c++) {
                    mazeBest[r][c] = mazeCurr[r][c];   // copy each cell
                }
            }
        }
        return stepBest;   // return the updated best step count
    }

    // check if the current cell is not empty (i.e. not walkable)
    if (mazeCurr[row][col] != EMPTY) {
        return stepBest;   // return the best steps without making changes
    }
}