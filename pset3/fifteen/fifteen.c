/**
 * fifteen.c
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

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
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
    FILE *file = fopen("log.txt", "w");
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
        int tile = get_int();
        
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
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int counter = d*d-1;
            
    for (int r=0; r<d; r++)
    {
        for (int c=0; c<d; c++)
        {
            board[r][c] = counter;
            counter --;
        }
    }
    
    if (d % 2 == 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int r=0; r<d; r++)
    {
        for (int c=0; c<d; c++)
        {
            if (board[r][c] == 0)
            {
                printf("%3s", "_");
            } else 
            {
                printf("%3d", board[r][c]);
            }
        }
        printf("\n\n");
    }
}

void swap_tiles(int empty_row, int empty_col, int tile_row, int tile_col, int tile)
{
    board[empty_row][empty_col] = tile;
    board[tile_row][tile_col] = 0;
}


/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    bool did_move = false;
    
    int empty_row, empty_col, tile_row, tile_col;
    for (int r=0; r<d; r++)
    {
        for (int c=0; c<d; c++)
        {
            if (board[r][c] == tile)
            {
                tile_row = r;
                tile_col = c;
            } else if (board[r][c] == 0)
            {
                empty_row = r;
                empty_col = c;
            }
        }
    }
    if (tile_row != 0) // able to check above for the empty spot
    {
     if (board[tile_row-1][tile_col] == 0)
     {
         swap_tiles(empty_row, empty_col, tile_row, tile_col, tile);
         did_move = true;
         return did_move;
     }
    }
    if (tile_row != d - 1) // able to check below for the empty spot
    {
        if (board[tile_row+1][tile_col] == 0)
        {
            swap_tiles(empty_row, empty_col, tile_row, tile_col, tile);
            did_move = true;
            return did_move;
        }
    }
    if (tile_col != 0) // able to check left
    {
        if (board[tile_row][tile_col - 1] == 0)
        {
            swap_tiles(empty_row, empty_col, tile_row, tile_col, tile);
            did_move = true;
            return did_move;   
        }
    }
    if (tile_col != d-1) // able to check right
    {
        if (board[tile_row][tile_col + 1] == 0)
        {
            swap_tiles(empty_row, empty_col, tile_row, tile_col, tile);
            did_move = true;
            return did_move;              
        }
    }
    return did_move;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    bool blank_at_end = false;
    bool pieces_positioned = true;
    int counter = 1;
    
    for (int r=0; r<d; r++)
    {
        for (int c=0; c<d; c++)
        {
            if (board[r][c] == 0 && (r == d-1 && c == d-1))
            {
                blank_at_end = true;
            }
            else if (board[r][c] != counter)
            {
                pieces_positioned = false;
            }
            counter ++;
        }
    }
    return blank_at_end && pieces_positioned;
}
