# Architecture
This file contains the architecture of the system.

We have used a code formatter [`clang-format`](https://docs.kernel.org/dev-tools/clang-format.html)
to format the code into a standard.

This codebase is very simple and consists of a single file.
The filesystem is split as follows:
```
.
├── .git
│   ├── 
│   └── (truncated)
├── ARCHITECTURE.md
├── cgol.6
├── cgol.c
├── LICENSE
└── README.md
```
(This is just the output of `tree .`, truncated).

From here on, I'll explain the codebase.

The libraries we use are
- `ncurses.h`: For the TUI part(mostly in `main()` and related). 
- `stdio.h`: For standard printing
- `stdlib.h`: For `malloc()`, `rand()`, `free()`, `atof()`.
- `string.h`: For `strcmp()` in the CLI arguments.
- `unistd.h`: For `usleep()` between generations.

The one and only structure we use is `Cell`, which is a node for a linked list, along with
containing the `r`(row) and `c`(column) where it is alive.
We maintain a linked list of all live cells, and iterate over it to display.

### Functions
Here are all the functions written in `cgol.c` and the documentation comments mentioned above them
(as in the code).
```c
/************* the-deepak-nayak ****************/
/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */

// @function: Iterates through the linked list and checks if the cell exists.
// @params:
// head: Head of the linked list.
// r: Row of the cell that we need to check.
// c: Column of the cell that we need to check.
// @returns: 1 if it is alive; 0 if dead
int is_alive(Cell *head, int r, int c);


// @function: Insert cell only if not already present
//            Inserts at the beginning itself, since the order doesn't matter.
// @params:
// head: Head of the linked list.
// r: Row of the cell that we need to check.
// c: Column of the cell that we need to check.
// @returns: void
void insert_cell(Cell **head, int r, int c);


// @function: Remove a cell(Same as deleting a node in a linked list).
// @params:
// head: Head of the linked list.
// r: Row of the cell that we need to check.
// c: Column of the cell that we need to check.
// @returns: void
void remove_cell(Cell **head, int r, int c);


// @function: Free the linked list
// @params:
// head: Head of the linked list
// @returns: void
void free_cells(Cell *head);

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/************* the-deepak-nayak ****************/


/************* roomroofroot ****************/
/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */

// @function: Count the neighbors of a given cell.
// @params:
// head: Head of the linked list.
// rows: Total number of rows in the terminal screen.
// cols: Total number of columns in the terminal screen.
// r: Row of the cell that we need to check.
// c: Column of the cell that we need to check.
// @returns: Number of neighbors of the cell
int count_neighbors(Cell *head, int rows, int cols, int r, int c);


// @function: Compute next generation.
// @params:
// head: Head of the linked list.
// rows: Number of rows of the terminal screen.
// cols: Number of columns of the terminal screen.
// @returns: The new linked list with the new generation's values
Cell *step_cells(Cell *head, int rows, int cols);


// @function: File IO (Save)
// @params:
// head: Head of the linked list.
// fname: Name of the file to which to save the current state.
// @returns: void
void save_to_file(Cell *head, char *fname);


// @function: Filo IO (Load)
// @params:
// fname: Name of the file from which to read.
// @returns: The linked list which contains the new state.
Cell *load_from_file(char *fname);

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/************* roomroofroot ****************/

/************* kajuburfi ****************/
/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */

// @function: Draws the cells onto the screen(stdscr)
// @params:
// head: Head of the linked list from which to get the cells' positions.
// rows: Number of rows in the terminal stdscr.
// cols: Number of columns in the terminal stdscr.
// cur_r: Row of the position of the cursor.
// cur_c: Column of the position of the cursor.
// running: Whether the game state is running or not(1 or 0).
// gen: The generation number.
// wait_time: The time(in microseconds) between generations(when the program
// sleeps).
// cell_char: The character that should be drawn for a live cell.
// @returns: void
void draw_cells(Cell *head, int rows, int cols, int cur_r, int cur_c,
                int running, long gen, int wait_time, char cell_char,
                char *savefile);


// @function: Randomize the state completely.
// @params:
// head: Head of the linked list(which we free).
// rows: Number of rows of the terminal stdscr.
// cols: Number of cols of the terminal stdscr.
// prob: How much of the screen should be live(probability of this).
// @returns: void
void randomize_cells(Cell **head, int rows, int cols, double prob);


// Main function
int main(int argc, int *argv[]);

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/************* kajuburfi ****************/
```
