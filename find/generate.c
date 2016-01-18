/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    //returns an error if there aren't 2-3 commandline arguments
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    //converts the second commandline argument (the input for how many random numbers you want generated) from a string into an integer
    int n = atoi(argv[1]);

    //if there are three total commandline arguments, then initialize a sequence
    //of pseudo-random numbers of type "long int" with the input coming from the third commandline argument
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    //else returns null
    else
    {
        srand48((long int) time(NULL));
    }

    //prints pseudo-random integers n number of times (different integers every time)
    //while staying under the pre-defined limit
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    //success
    return 0;
}