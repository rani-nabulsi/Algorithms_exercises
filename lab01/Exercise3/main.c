/*
plan to solve:
 1) reading the file, store data in struct
 2) use loop to continuously ask for a command based on the user's input
 3) implementation of functions: write separate functions for listing all cyclists
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // used for memory allocation

// define maximum constant for cyclist name (30 chars +1 for string terminator)
#define MAX 31

// define a struct to store the cyclist info read from the file
typedef struct {
    char *name;  // pointer to hold the dynamically allocated name
    int id;
    int laps;
    float *times;  // pointer to an array holding the dynamically allocated lap times
    float avg;
} cyclist_t;

// function prototypes
cyclist_t *read_file(int *, int *);  // function to read input file
void printList(cyclist_t *, int);  // function to print all cyclists
void printDetails(cyclist_t *, int);  // function to print details of a specific cyclist
void printBest(cyclist_t *, int);  // function to print the cyclist with the best avg lap time


/*
 read_file: this function reads the input file, parses cyclists data, calculates their avg lap time
 parameters:
 num_ptr - pointer to store the number of cyclists
 best - pointer to store the index of the cyclist with the best avg
 */
cyclist_t *read_file(int *num_ptr, int *best) {
    cyclist_t *team; // pointer to hold the array of cyclist structs
    char name[MAX];  // temporary variable to hold the name during the reading of file
    float best_avg = -1; // variable to track the best (smallest) avg lap time
    int i, j;
    FILE *fp;

    fprintf(stdout, "Input file name: ");
    scanf("%s", name);
    fp = fopen(name, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error in opening file.\n");
        exit(EXIT_FAILURE);
    }

    // reading the number of cyclists from the file
    fscanf(fp, "%d", num_ptr);

    // allocating memory for array of cyclists based on the number of cyclists
    team = (cyclist_t *) malloc((*num_ptr) * sizeof(cyclist_t));
    if (team == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // loop through each cyclist and read their data
    for (i = 0; i < *num_ptr; i++) {
        // reading the cyclist's name, ID, number of laps
        fscanf(fp, "%s %d %d", name, &team[i].id, &team[i].laps);
        team[i].name = strdup(name);  // duplicate the cyclist's name into dynamically allocated memory
        team[i].times = (float *) malloc(team[i].laps * sizeof(float));  // allocating memory for lap times
        if (team[i].name == NULL || team[i].times == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        team[i].avg = 0;  // initialize avg lap time to 0

        // loop through and read each lap time, adding it to the avg
        for (j = 0; j < team[i].laps; j++) {
            fscanf(fp, "%f", &team[i].times[j]);
            team[i].avg += team[i].times[j];  // add lap time to total
        }

        // calculate the avg lap time by dividing the total #laps
        team[i].avg /= team[i].laps;
        // check if this cyclist has the best (smallest) avg time
        if (best_avg < 0 || team[i].avg <= best_avg) {
            best_avg = team[i].avg;  // update best avg
            *best = i;  // update the index of the best cyclist
        }
    }
    fclose(fp);
    return team;  // return the array of cyclists
}

/*
 printLists - prints the number of cyclists and their info
 */
void printLists(cyclist_t *team, int num) {
    int i;

    fprintf(stdout, "Number of cyclists: %d\n", num);  // print total #cyclists
    for (i = 0; i < num; i++) { // loop through each cyclist
        fprintf(stdout, "Name: %s\n", team[i].name);
        fprintf(stdout, "ID: %d\n", team[i].id);
        fprintf(stdout, "Laps: %d\n", team[i].laps);
    }
}

/*
 printDetails - prints detailed info (ID lap times) for a specific cyclist (identified by name)
 */
void printDetails(cyclist_t *team, int num) {
    int i, j, found = 0;  // loop counters and flag to track if cyclist is found
    char name[MAX];  // variable that stores the name of the cyclist that's being looped

    scanf("%s", name);
    for (i = 0; i < num && !found; i++) { // loop through cyclists array until desired index is found
        if (strcmp(name, team[i].name) == 0) { // compare the input name with the cyclist's name
            fprintf(stdout, " Id   : %d\n", team[i].id);
            fprintf(stdout, " Laps : %d\n", team[i].laps);
            fprintf(stdout, " Times: ");
            for (j=0; j<team[i].laps; j++) {  // Loop through each lap time and print it
                fprintf(stdout, "%.2f ", team[i].times[j]);
            }
            fprintf(stdout, "\n");
            found = 1;  // Set the found flag to indicate the cyclist was found
        }
    }
    if (!found) {  // If no matching cyclist was found, print an error message
        fprintf(stdout, "Cyclist not found.\n");
    }
}
/*
 printBest - prints the details of the cyclist with the best avg lap time
 */
void printBest(cyclist_t *team, int best) {
    int j;
    fprintf(stdout, " Best cyclist: %s\n", team[best].name);
    fprintf(stdout, " Id   : %d\n", team[best].id);
    fprintf(stdout, " Laps : %d\n", team[best].laps);
    fprintf(stdout, " Times: ");
    for (j=0; j<team[best].laps; j++) {  // Loop through each lap time and print it
        fprintf(stdout, "%.2f ", team[best].times[j]);
    }
    fprintf(stdout, "\n Average time: %.2f\n", team[best].avg);  // Print the cyclist's average lap time
}

/*
 * Main function - The program starts execution here.
 */
int main(void) {
    char cmd[MAX];   // Array to store the command entered by the user
    int i, num, best;  // num: total number of cyclists; best: index of the cyclist with the best average lap time
    cyclist_t *team = read_file(&num, &best);  // Call to read the file and store the cyclists' data

    // Menu loop: This loop continues asking for commands until "stop" is entered.
    do {
        // Displaying the available commands for the user
        fprintf(stdout, "\nAvailable commands:\n");
        fprintf(stdout, "list           - list all the cyclists' data\n");
        fprintf(stdout, "details <name> - show the details of a single cyclist\n");
        fprintf(stdout, "best           - show the details of the best cyclist\n");
        fprintf(stdout, "stop           - quit the program\n\n");

        // Asking for the command input from the user
        fprintf(stdout, "Command? ");
        scanf("%s", cmd);  // Reading the command into the `cmd` variable

        // Checking the command and calling the appropriate function
        if (strcmp(cmd, "list") == 0) {
            printList(team, num);  // Print details of all cyclists
        } else if (strcmp(cmd, "details") == 0) {
            printDetails(team, num);  // Print details of a specific cyclist
        } else if (strcmp(cmd, "best") == 0) {
            printBest(team, best);  // Print details of the cyclist with the best average lap time
        } else if (strcmp(cmd, "stop") != 0) {
            fprintf(stderr, "Invalid command\n");  // Error message for invalid commands
        }
    } while (strcmp(cmd, "stop") != 0);  // Loop continues until "stop" is entered

    // Freeing dynamically allocated memory for each cyclist before exiting
    for(i=0; i<num; i++) {
        free(team[i].name);
        free(team[i].times);
    }
    free(team);  // Freeing the array of cyclist structures

    fprintf(stdout, "End of program.\n");  // Indicating the program has ended

    return EXIT_SUCCESS;  // Exiting the program with a success status
}