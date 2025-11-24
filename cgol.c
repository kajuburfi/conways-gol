// Conway's Game of Life

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Cell linked list structures
typedef struct cell Cell;
struct cell {
  int r, c;
  struct cell *next;
};

// @function: Iterates through the linked list and checks if the cell exists.
// @params:
// head: Head of the linked list.
// r: Row of the cell that we need to check.
// c: Column of the cell that we need to check.
// @returns: 1 if it is alive; 0 if dead
int is_alive(Cell *head, int r, int c) {
  for (Cell *p = head; p != NULL; p = p->next)
    if (p->r == r && p->c == c)
      return 1;
  return 0;
}

// @function: Insert cell only if not already present
//            Inserts at the beginning itself, since the order doesn't matter.
// @params:
// head: Head of the linked list.
// r: Row of the cell that we need to check.
// c: Column of the cell that we need to check.
// @returns: void
void insert_cell(Cell **head, int r, int c) {
  if (is_alive(*head, r, c))
    return;
  Cell *n = malloc(sizeof(Cell));
  n->r = r;
  n->c = c;
  n->next = *head;
  *head = n;
}

// @function: Remove a cell(Same as deleting a node in a linked list).
// @params:
// head: Head of the linked list.
// r: Row of the cell that we need to check.
// c: Column of the cell that we need to check.
// @returns: void
void remove_cell(Cell **head, int r, int c) {
  Cell *p = *head, *prev = NULL;
  while (p) {
    if (p->r == r && p->c == c) {
      if (prev)
        prev->next = p->next;
      else
        *head = p->next;
      free(p);
      break;
    }
    prev = p;
    p = p->next;
  }
}

// @function: Free the linked list
// @params:
// head: Head of the linked list
// @returns: void
void free_cells(Cell *head) {
  while (head) {
    Cell *tmp = head->next;
    free(head);
    head = tmp;
  }
}

// @function: Count the neighbors of a given cell.
// @params:
// head: Head of the linked list.
// rows: Total number of rows in the terminal screen.
// cols: Total number of columns in the terminal screen.
// r: Row of the cell that we need to check.
// c: Column of the cell that we need to check.
// @returns: Number of neighbors of the cell
int count_neighbors(Cell *head, int rows, int cols, int r, int c) {
  int count = 0;
  // Check for all 8 neighbors. dr and dc change from -1 to 1, thus representing
  // the difference in rows and columns from the center cell
  for (int dr = -1; dr <= 1; dr++) {
    for (int dc = -1; dc <= 1; dc++) {
      // Skip the cell itself
      if (dr == 0 && dc == 0)
        continue;
      // Using modulo rows and cols because to wrapping around
      int rr = (r + dr + rows) % rows;
      int cc = (c + dc + cols) % cols;
      if (is_alive(head, rr, cc))
        count++;
    }
  }
  return count;
}

// @function: Compute next generation.
// @params:
// head: Head of the linked list.
// rows: Number of rows of the terminal screen.
// cols: Number of columns of the terminal screen.
// @returns: The new linked list with the new generation's values
Cell *step_cells(Cell *head, int rows, int cols) {
  Cell *new = NULL;

  Cell *p = head;
  // Loop over every cell
  while (p) {
    // Similar logic to that of the previous function, count_neighbors()
    for (int dr = -1; dr <= 1; dr++) {
      for (int dc = -1; dc <= 1; dc++) {
        int rr = (p->r + dr + rows) % rows;
        int cc = (p->c + dc + cols) % cols;
        int n = count_neighbors(head, rows, cols, rr, cc);
        // Conway's Game of Life logic
        if (is_alive(head, rr, cc)) {
          if (n == 2 || n == 3)
            insert_cell(&new, rr, cc);
        } else {
          if (n == 3)
            insert_cell(&new, rr, cc);
        }
      }
    }
    p = p->next;
  }

  free_cells(head);
  return new;
}

// @function: File IO (Save)
// @params:
// head: Head of the linked list.
// fname: Name of the file to which to save the current state.
// @returns: void
void save_to_file(Cell *head, char *fname) {
  // Save format: Saves the live cells(which currently exists in a linked list)
  // as:
  // x1 y1
  // x2 y2
  // x3 y3
  //
  // And so on.
  FILE *f = fopen(fname, "w");
  // Ignore errors
  if (!f)
    return;
  for (Cell *p = head; p != NULL; p = p->next)
    fprintf(f, "%d %d\n", p->r, p->c);
  fclose(f);
}

// @function: Filo IO (Load)
// @params:
// fname: Name of the file from which to read.
// @returns: The linked list which contains the new state.
Cell *load_from_file(char *fname) {
  FILE *f = fopen(fname, "r");
  if (!f)
    return NULL;

  Cell *head = NULL;
  int r, c;
  while (fscanf(f, "%d %d", &r, &c) == 2)
    insert_cell(&head, r, c);

  fclose(f);
  return head;
}

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
                char *savefile) {
  erase();

  // Draw cells
  for (Cell *p = head; p; p = p->next) {
    if (p->r >= 0 && p->r < rows && p->c >= 0 && p->c < cols)
      mvaddch(p->r, p->c,
              cell_char); // Moves to p->r, p->c and prints 'O' there
  }

  // Draw cursor if it is paused(edit mode)
  if (!running) {
    if (is_alive(head, cur_r, cur_c)) {
      attron(A_REVERSE);
      mvaddch(cur_r, cur_c,
              ACS_BULLET); // Cursor style is different
      attroff(A_REVERSE);
    } else
      mvaddch(cur_r, cur_c,
              ACS_CKBOARD); // Cursor style is different
  }

  // Status line
  int h, w;
  getmaxyx(stdscr, h, w); // Gets size of terminal
  mvprintw(h - 2, 0,
           "Gen %ld  [%s]   p=play/pause  g=Next generation  space=Toggle  "
           "r=Random  S=Save  L=Load \n(Filename=%s)  q=quit  "
           "speed=%d gen/s",
           gen, running ? "Running" : "Paused", savefile, 1000000 / wait_time);

  refresh();
}

// @function: Randomize the state completely.
// @params:
// head: Head of the linked list(which we free).
// rows: Number of rows of the terminal stdscr.
// cols: Number of cols of the terminal stdscr.
// prob: How much of the screen should be live(probability of this).
// @returns: void
void randomize_cells(Cell **head, int rows, int cols, double prob) {
  free_cells(*head); // Clear all cells
  *head = NULL;
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
      if (((double)rand() / RAND_MAX) < prob)
        insert_cell(head, r, c);
}

int main(int argc, char *argv[]) {

  char *filename = "pattern.txt";
  int file_provided = 0;
  float rand_prob = 0.1;
  char cell_char = 'O';
  int exitstatus = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--filename") == 0 || strcmp(argv[i], "-f") == 0) {
      filename = argv[++i];
      file_provided = 1;
    } else if (strcmp(argv[i], "--character") == 0 ||
               strcmp(argv[i], "-c") == 0) {
      cell_char = argv[++i][0];
    } else if (strcmp(argv[i], "--rand-prob") == 0 ||
               strcmp(argv[i], "-p") == 0) {
      rand_prob = (atof(argv[++i]) == 0.0) ? 0.09 : atof(argv[i]);
      if (rand_prob > 0.1) {
        rand_prob = 0.1;
        printf("Random Probability passed was too high. Taking 0.1 as the "
               "max.\nPress enter to continue...\n");
        getchar();
      }
    } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
      printf(
          "Usage: cgol [OPTION]...\nSimulate Conway's Game of Life\n\n"
          "Optional arguments\n  "
          "-c, --character [char]        character to symbolize alive cell\n  "
          "-f, --filename [filepath]     filepath for initial state\n  "
          "-p, --random-prob [factor]    probability factor to randomize states"
          "\n  -h, --help                    display this text and exit\n\n"
          "In-game controls\n  "
          "arrow-keys, hjkl              navigate cursor across screen\n  "
          "space                         toggle current cell state\n  "
          "p                             play/pause simulation\n  "
          "r                             randomize states\n  "
          "g                             view next generation\n  "
          "L                             load from specified file\n  "
          "S                             save to specified file\n  "
          "q                             quit\n"
          "  +				increases the speed of generation\n"
          "  -				decreases the speed of generation\n");
      exitstatus = 1;
      break;
    } else {
      printf("Stop it, get some --help\n");
      exitstatus = 1;
      break;
    }
  }

  if (exitstatus)
    return 0;

  // NCurses initialization stuff
  initscr();             // Starts the screen(window)
  noecho();              // Doesn't echo key presses on to the terminal screen
  cbreak();              // Return key press directly to the program
  keypad(stdscr, TRUE);  // Extends keyboard functionality(accepts keypad inputs
                         // and function keys)
  curs_set(0);           // Makes the cursor invisible
  nodelay(stdscr, TRUE); // Do not wait for input into a fuction like getch()
                         // No input returns ERR

  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  rows--; // Reduce a row for the status bar

  Cell *head = NULL; // Empty linked list
  // Center the cursor initially
  int cur_r = rows / 2;
  int cur_c = cols / 2;

  int running = 0;        // Initially not running
  int wait_time = 100000; // In microseconds (=0.1s)
  long generation = 0;

  if (file_provided) {
    free_cells(head); // Clear screen
    head = load_from_file(filename);
    generation = 0;
  }

  while (1) {
    if (running && head == NULL) {
      running = !running;
    }

    int ch = getch();
    if (ch != ERR) {
      // Move if and only if not running
      // We are doing (mod rows) and (mod cols) for looping around.
      if ((ch == KEY_UP || ch == 'k') && !running)
        cur_r = (cur_r - 1 + rows) % rows;
      else if ((ch == KEY_DOWN || ch == 'j') && !running)
        cur_r = (cur_r + 1) % rows;
      else if ((ch == KEY_LEFT || ch == 'h') && !running)
        cur_c = (cur_c - 1 + cols) % cols;
      else if ((ch == KEY_RIGHT || ch == 'l') && !running)
        cur_c = (cur_c + 1) % cols;

      // Change cell state if and only if not running
      else if (ch == ' ' && !running) {
        if (is_alive(head, cur_r, cur_c))
          remove_cell(&head, cur_r, cur_c);
        else
          insert_cell(&head, cur_r, cur_c);
      } else if (ch == 'p') // Play or Pause
        running = !running;
      else if (ch == 'g') { // Go generation step by step
        head = step_cells(head, rows, cols);
        generation++;
      } else if (ch == 'r') {
        randomize_cells(&head, rows, cols, rand_prob);
        generation = 0;
      } else if (ch == 'S') {
        save_to_file(head, filename);
      } else if (ch == 'L') {
        free_cells(head); // Clear screen
        head = load_from_file(filename);
        generation = 0;
      } else if (ch == '+') {
        wait_time -= 10000;
      } else if (ch == '-') {
        wait_time += 10000;
      } else if (ch == 'q')
        break;
    }

    // Limits on the wait_time
    wait_time = (wait_time <= 1000) ? 1000 : wait_time;
    wait_time = (wait_time >= 200000) ? 200000 : wait_time;

    if (running) {
      head = step_cells(head, rows, cols);
      generation++;
      usleep(wait_time);
    }

    draw_cells(head, rows, cols, cur_r, cur_c, running, generation, wait_time,
               cell_char, filename);
    usleep(100);
  }

  free_cells(head);
  endwin();
  return 0;
}
