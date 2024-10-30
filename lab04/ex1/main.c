#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define myassert(actual, expected) \
    do { \
        if ((expected) == (actual)) { \
            printf("\u2713\n"); \
        } else { \
            printf("\u2717 Fail: %s != %s\n", #actual, #expected); \
        } \
    } while (0)

// FUNCTIONS TO BE IMPLEMENTED

// A.
int mult(int x, int y) {
    if (y == 0) {
        return 0;
    }
    if (y == 1) {
        return x;
    }
    return x + mult(x, y - 1);
}

// B.
void d2b(int d, int *b, int *n) {

    if (d == 0) { // # = 0
        return;
        if (*n == 0) { // case for 0 (binary = 0)
            b[(*n)++] = 0; // set first digit = 0 then increment
            return;
        }
    }
    b[(*n)++] = d % 2;
    d2b(d / 2, b, n);    // Recursive call with quotient d/2
    //b[(*n)++] = d % 2;   // Store the remainder as the next binary digit in the array
}

// C.
int catalan(int n) {
    if (n == 0)  // Base case: C_0 is defined as 1
        return 1;
    int res = 0; // Initialize result to accumulate sum
    for (int i = 0; i < n; i++) // Loop to sum up products of previous Catalan numbers
        res += catalan(i) * catalan(n - 1 - i); // Recursive computation as per the formula
    return res;
}


// D.
int countSpaces(char *s) {
    if (*s == '\0') // Base case: if we reach the end of the string, return 0
        return 0;
    return isspace(*s) + countSpaces(s + 1); // Check current char and move to next
}



// E.
int isPalindrome(char *s, int l) {
    if (l <= 1) // single character or empty string is a palindrome
        return 1;
    if (!isalnum(s[0])) // Skip non-alphanumeric character at the start
        return isPalindrome(s + 1, l - 1);
    if (!isalnum(s[l - 1])) // Skip non-alphanumeric character at the end
        return isPalindrome(s, l - 1);
    if (tolower(s[0]) != tolower(s[l - 1])) // Compare start and end, ignoring case
        return 0;
    return isPalindrome(s + 1, l - 2); // Move inward if match found
}


// support functions, do not modify
int arraycompare(int *, int, char *);

int main() {
    printf("Testing A.\n");
    myassert( mult(113,456), 51528 );
    myassert( mult(0,598), 0 );
    myassert( mult(501,0), 0 );
    myassert( mult(0,0), 0 );
    myassert( mult(1,1111), 1111 );

    printf("\nTesting B.\n");
    int b[256]={0}; int n=0;
    myassert( (n=0,d2b(2,b,&n),   arraycompare(b,n,"10")), 0);
    for (int i=0; i < n; i++) {
        printf("%d ", b[i]);
    }  printf("\n");
    myassert( (n=0,d2b(35,b,&n),  arraycompare(b,n,"100011")), 0);
    for (int i=0; i < n; i++) {
        printf("%d ", b[i]);
    } printf("\n");
    myassert( (n=0,d2b(255,b,&n), arraycompare(b,n,"11111111")), 0);
    for (int i=0; i < n; i++) {
        printf("%d ", b[i]);
    } printf("\n");
    myassert( (n=0,d2b(256,b,&n), arraycompare(b,n,"100000000")), 0);
    for (int i=0; i < n; i++) {
        printf("%d ", b[i]);
    } printf("\n%d\n", n);
    myassert( (n=0,d2b(0,b,&n),   arraycompare(b,n,"0")), 0);
    for (int i=0; i < n; i++) {
        printf("%d ", b[i]);
    } printf("\n");

    printf("\nTesting C.\n");
    myassert( catalan(0), 1);
    myassert( catalan(3), 5);
    myassert( catalan(6), 132);
    myassert( catalan(16), 35357670);

    printf("\nTesting D.\n");
    myassert( countSpaces("hello world"), 1);
    myassert( countSpaces("hello\t\tworld"), 2);
    myassert( countSpaces("\nhello\t\tworld\r"), 4);
    myassert( countSpaces("\nh e\vl\nl  o\t\twor  \rld\r"), 12);

    printf("\nTesting E.\n");
    myassert( isPalindrome("abcba", 5), 1);
    myassert( isPalindrome("aaaa", 4), 1);
    myassert( isPalindrome("a", 1), 1);
    myassert( isPalindrome("ab", 2), 0);
    myassert( isPalindrome("aaba", 4), 0);
    myassert( isPalindrome("aaba", 4), 0);
    myassert( isPalindrome("Madam, I'm Adam",15),1);
    myassert( isPalindrome("A man, a plan, a canal, Panama",30),1);
}

int arraycompare(int *array, int n, char *ref) {
    if( n != strlen(ref) )
        return -1;
    for( int i = n-1; i >= 0 ; i--) {
        if( array[i] != ref[n-i-1] - '0')
            return -1;
    }
    return 0;
}