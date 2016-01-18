/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9
char* space = "[     ]";

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void swap (int* a, int* b);
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
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
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    //counter variable declared (will be used eventually in double-for-loop)
    int counter = 0;
    
    //two loops, one to iterate through rows and one to iterate through columns
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            //counter is increased by 1
            counter++;
            //places the numbers into the array in descending order
            board[i][j] = (d*d) - counter;
        }
        //if there is an odd amount of tiles, swaps 1 and 2.
        if (d % 2 == 0) swap(&board[d-1][d-2], &board[d-1][d-3]);
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    //two loops, one to iterate through rows and one to iterate through columns
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            //makes sure that the board looks like an actual board, not a single line
            if (j%d == 0) printf("\n");
            //prints the number of all tiles except for the empty tile
            if (board[i][j] > 0) printf("[  %d  ]", board[i][j]);
            //prints the last tile 
            if (board[i][j] == 0) printf("%s", space);
        }
    }
    printf("\n");
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    //two loops, one to iterate through rows and one to iterate through columns
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            //readies the selected tile to be moved
            if (board[i][j] == tile) {
                //lines 223-227 do all the swapping
                //only allows swap if j >= 1 to prevent loss of numbers
                if (j>=1) if (board[i][j-1] == 0) swap(&board[i][j-1], &board[i][j]);
                //only allows swap if i >= 1 to prevent loss of numbers
                if (i>=1) if (board[i-1][j] == 0) swap(&board[i-1][j], &board[i][j]);
                if (j<=1) if (board[i][j+1] == 0) swap(&board[i][j+1], &board[i][j]);
                if (i<=1) if (board[i+1][j] == 0) swap(&board[i+1][j], &board[i][j]);
                return true;
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    //counter variable initialized (will be used eventually in double-for-loop)
    int counter = 0;
    
    //two loops, one to iterate through rows and one to iterate through columns
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            counter++;
            //fixes off by 1 error towards the end (illegal move)
            if (board[i][j] == (d*d)-1) break;
            //places the numbers into the array in ascending order
            if (board[i][j] != counter) return false;
        }
    }
    return true;
    
    //For some reason, I can't get the 4x4 test to run...
    //./fifteen 4 < ~cs50/pset3/4x4.txt doesn't work when I run it, so I don't
    //have a way to see why my code fails the 4x4 test
}