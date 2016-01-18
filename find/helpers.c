/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

//original search
// bool search(int value, int values[], int n)
// {
//     //returns false right away if n isn't positive
//     if (n < 0) return false;
//     //for loop that tests if the ith value of array values is equal to value
//     for (int i = 0; i < n; i++) {
//         //returns true if the ith value of array values is equal to value
//         if (values[i] == value) return true;
//     }
//     //returns false otherwise
//     return false;
// }

//improved search
bool search(int value, int values[], int n)
{
    //initializing middle variable
    int m = 0;
    while (n > 0) {
        //calculating middle variable
        m = n / 2;
        if (values[m] > value) {
            //checks lower-half of values[] for value
            for (int i = m; i > 0; i--) {
                if (values[i] == value) return true;
            }
        }
        else if (values[m] < value) {
            //checks upper-half of values[] for value
            for (int i = m; i < n; i++) {
                if (values[i] == value) return true;
            }
        }
        //checks if the middle value of values[m] is the value
        else if (values[m] == value) return true;
        //goes down the list
        n--;
    }
    //returns false otherwise
    return false;
}

/**
 * Swaps values.
 */
void swap (int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    //double for-loop used to sort array
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            //swaps values if the current value is greater than the proceding value
            if (values[j] > values[j+1]) {
                swap(&values[j], &values[j+1]);
            }
        }
    }
}