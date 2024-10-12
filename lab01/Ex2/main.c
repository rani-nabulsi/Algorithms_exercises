#include <stdlib.h>  // standard library for memory allocation
#include <string.h>
#include <stdio.h>

#define maxN 30   // maximum number of elements in the array
#define maxS 100  // maximum size of a string (used for rectangle names)

// rotate the array using simple one-step rotations
// dir: 1 for left; dif; -1 for right
// N: number of elements; P: number of positions to rotate
void rotateArray(int V[maxN], int dir, int N, int P) {
    int tmp, i, j;

    // if the direction is left (dir == 1)
    if (dir == 1) {
        for (i = 0; i < P; i++) {  // Rotate left by P steps, one step at a time
            tmp = V[0];  // store the first element temporarily
            for (j = 0; j < N - 1; j++) {  // shift all elements to the left by one position
                V[j] = V[j + 1];
            }
            V[N - 1] = tmp;  // place the temporarily store element at the end of thr array
        }
    } else { // else iif direction is right, perform right rotation
        for (i = 0; i < P; i++) { // Rotate left by P steps, one step at a time
            tmp = V[N - 1];  // store the last element temporarily
            for (j = N - 1; j > 0; j--) {  // shift all elements to the right by one position
                V[j] = V[j - 1];
            }
            V[0] = tmp;  // place the stored element at the front
        }
    }
}

// Rotate the array using a temporary array to save elements that "wrap around"
// dir: 1 for left; dif; -1 for right
// N: number of elements; P: number of positions to rotate
void rotateArray2(int V[maxN], int dir, int N, int P) {
    int tmpArray[maxN], i;

    // For left rotation (dir == 1)
    if (dir == 1) {
        for (i = 0; i < P; i++) {  // Store the first P elements in a temporary array.
            tmpArray[i] = V[i];
        }
        for (i = 0; i < N - P; i++) {  // Shift elements from index P to the left.
            V[i] = V[i + P];
        }
        for (i = 0; i < P; i++) {  // Move the saved elements to the last positions.
            V[N - P + i] = tmpArray[i];
        }
    } else {  // For right rotation (dir != 1)
        for (i = 0; i < P; i++) {  // Store the last P elements in a temporary array.
            tmpArray[i] = V[N - P + i];
        }
        for (i = N - 1; i >= P; i--) {  // Shift elements to the right by P positions.
            V[i] = V[i - P];
        }
        for (i = 0; i < P; i++) {  // Move the saved elements to the first positions.
            V[i] = tmpArray[i];
        }
    }
}

// Rotate the array using a generalized movement logic that shifts blocks of elements.
// dir: 1 for left, -1 for right; N: number of elements; P: number of positions to rotate.
void rotateArray3(int V[maxN], int dir, int N, int P) {
    int tmpArray[maxN], i, t0, t1, dest, src;

    // Determine the source and destination intervals for rotation.
    if (dir == 1) {  // For left rotation
        t0 = 0;  // Start saving from the beginning.
        t1 = N - P;  // The position where saved elements will go.
        dest = 0;  // Starting point for shifting elements.
    } else {  // For right rotation
        t0 = N - P;  // Start saving from the last P positions.
        t1 = 0;  // Copy back to the beginning.
        dest = N - 1;  // Start shifting from the last element.
    }

    // Save the interval that will be overwritten during the shift.
    for (i = 0; i < P; i++) {
        tmpArray[i] = V[t0 + i];
    }

    // Shift elements by P positions in the direction of rotation.
    for (i = 0; i < N - P; i++) {
        src = dest + P * dir;  // Calculate source based on direction.
        V[dest] = V[src];  // Shift element from source to destination.
        dest = dest + dir;  // Move destination index.
    }

    // Restore saved elements to their new positions.
    for (i = 0; i < P; i++) {
        V[t1 + i] = tmpArray[i];
    }
}

// Rotate the array by converting right rotation to left rotation for consistency.
// dir: 1 for left, -1 for right; N: number of elements; P: number of positions to rotate.
void rotateArray4(int V[maxN], int dir, int N, int P) {
    int tmpArray[maxN], i;

    // Convert right rotation to equivalent left rotation.
    if (dir == -1) {
        P = N - P;  // Equivalent left rotation for right rotation.
    }

    // Save the first P elements in a temporary array.
    for (i = 0; i < P; i++) {
        tmpArray[i] = V[i];
    }

    // Shift elements by P positions to the left.
    for (i = 0; i < N - P; i++) {
        V[i] = V[i + P];
    }

    // Restore the saved elements to the end of the array.
    for (i = 0; i < P; i++) {
        V[N - P + i] = tmpArray[i];
    }
}

// function to print the elements of the array
void printArray(int V[maxN], int N) {
    int i;
    for (i = 0; i < N; i++) {  // print each element with a space seperator
        printf("%d ", V[i]);
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int N, i, P, dir, fine = 0, arr[maxN] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // Default array.
    int selector = 1;

    // If a command-line argument is passed, use it as the selector for rotation method.
    if (argc > 1) {
        selector = atoi(argv[1]);
        if (selector < 1 || selector > 4)
            selector = 1;
    }

    printf("Insert number of elements (interval 1..%d)\n", maxN);
    printf("(Outside of interval to accept pre-set values): ");
    scanf("%d", &N);
    printf("Insert array of numers: ");
    if (N > 0 && N <= maxN) {
        for (i = 0; i < N; i++)
            scanf("%d", &arr[i]);
    } else {
        N = 10;
    }

    printArray(arr, N);

    do {
        printf("Command (P dir) (0 dir to terminate)> ");
        fine = scanf(" %d %d", &P, &dir) != 2;
        if (P <= 0)
            fine = 1;
        P = P % N; /* if P>N, the number of rotations is still P%N */
        if (!fine && (dir == 1 || dir == -1)) {
            switch (selector) {
                case 1:
                    rotateArray(arr, dir, N, P);
                    break;
                case 2:
                    rotateArray2(arr, dir, N, P);
                    break;
                case 3:
                    rotateArray3(arr, dir, N, P);
                    break;
                case 4:
                    rotateArray4(arr, dir, N, P);
                    break;
                default:
                    printf("Error: invalid selector\n");
            }
            printArray(arr, N);
        }
    } while (!fine);

    return 0;
}