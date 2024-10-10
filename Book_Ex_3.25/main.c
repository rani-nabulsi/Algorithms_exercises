/*
Given the two following files for the donations and the voluntary list:
File "donation"
JH-YY 300
VH-ZZ 400
JH-YY 200
BS-00 500
JH-YY 600
VH-ZZ 400

File "voluntary"
BS-00 Writer Bram Stoker
JH-YY Agent Jonathan Harker
VT-XX Cont Vlad Tepes
VH-ZZ Doctor Van Helsing

the application has to print-out the following information:
BS-00 Bram Stoker: 1 donation/s - 500 cc
JH-YY Jonathan Harker: 3 donation/s - 1100 cc
VT-XX Vlad Tepes: 0 donation/s - 0 cc
VH-ZZ Van Helsing: 2 donation/s - 800 cc

*/


#include <stdio.h>
#include <stdlib.h>  // library for memory allocation
#include <string.h>  // library for strcpy and strcmp

// Constants
#define MAX_ID 5+1  // define max length for ID (+1 for null terminator)
#define MAX_NAME 20+1  // define maximum length for name/surnames (+1 null terminator)

// Struct
typedef struct {  // defines a struct to represent each volunteer
    char id[MAX_ID];  // id
    char surname[MAX_NAME];  // surname
    char name[MAX_NAME];  // name
    int total_amount;  // total amount donated by volunteer
    int num_donations;  // number of donations made by the volunteer
} donor_t;

// Prototypes
donor_t *donor_read(int *num_ptr);  // function to read the voluntary file and return dynamic array of donors
void donation_read(donor_t *donors, int n);  // function to reach donation file and update the donor information
int id_search (donor_t *donors, char id[MAX_ID+1], int n);  // function to search for a donor by their ID
void result_display(donor_t *donors, int n);  // function to display the final results (donor info)


// read volunteers file
donor_t *donor_read(int *num_ptr) {
    char id[MAX_ID], name[MAX_NAME], surname[MAX_NAME]; // temporary storage for reading from file
    donor_t *donors; // pointer to hold the array of donors
    int i, n;  // loop counter and number of donors
    FILE *fp;  // file pointer

    printf(stdout, "Donors file name: ");  // ask the user to input volunteers filename
    scanf("%s", name);  // store the filename in name

    fp = fopen(name, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error in opening file.\n", name);
        exit(EXIT_FAILURE);
    }
    n = 0;  // initialize donor count
    while (fscanf(fp, "%s %s %s", id, surname, name) != EOF) { // count the number of entries in the file
        n++;
    }
    fclose(fp);

    donors = (donor_t *) malloc(n * sizeof(donor_t)); // allocate memory for 'n' donors
    if (donors == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    fp = fopen(name, "r");  // reopen the file to actually read the dT
    if (fp == NULL) {
        fprintf(stderr, "Error in opening file.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        fscanf(fp, "%s %s %s", id, surname, name);  // read info from file
        strcpy(donors[i].id, id); // copy id into donor struct
        strcpy(donors[i].surname, surname); // copy surname into donor struct
        strcpy(donors[i].name, name); // copy name into donor struct
        donors[i].total_amount = 0;  // initialize total_amount to 0
        donors[i].num_donations = 0;  // initialize num_donations to 0
    }
    fclose(fp);
    *num_ptr = n;  // set the number of donors
    return donors;  // return the dynamic array of donors
}

// read donation file and update donor records
void donation_read(donor_t *donors, int n) {
    char name[MAX_NAME],id[MAX_ID];  // temporary storage for reading from file
    int i, amount;  // i for donor index, amount --> donation amount
    FILE *fp;  // file pointer

    printf(stdout, "Donations file name: ");  // ask user to enter donation file name
    scanf("%s", name);  // store the file name in name

    fp = fopen(name, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error in opening file.\n", name);
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%s %d", id, &amount) != EOF) { // while there are lines in the file, read ID and donation amount
        i = id_search(donors, id, n); // search for donor id in the array
        if (i != -1) {  // if ID is found --> donor exists
            donors[i].total_amount += amount;  // add donation amount to the donor's total
            donors[i].num_donations ++; // increment number of donations done by that donor
        }
    }

    fclose(fp);
}

// function to search for a donor by their ID
int id_search(donor_t *donors, char id[MAX_ID+1], int n) {
    int i;  // loop counter

    for (i = 0; i < n; i++) {  // loop through all the donors
        if (strcmp(donors[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// function to display final results
void result_display(donor_t *donors, int n) {
    int i;  // loop counter

    for (i = 0; i < n; i++) {  // loop through all donors
        // print donor's ID, name, surname, amount of donations, total amount (quantity)
        printf(stdout, "%s %s", donors[i].id, donors[i].name);
        printf(stdout, "%s: %d donation/s - %d cc\n", donors[i].surname, donors[i].num_donations, donors[i].total_amount);
    }
}

int main(void) {
    donor_t *donors; // declare a pointer to hold array of donors
    int n;  // variable to store number of donors

    donors = donor_read(&n); // call function to load donors read from file, passing the address of n to store number of donors
    donation_read(donors, n); // call function to process donations and update the donor array
    result_display(donors, n); // call function to print the final output

    free(donors);  // free dynamically allocated memory after its use
    return EXIT_SUCCESS;
}