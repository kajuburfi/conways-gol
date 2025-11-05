<h1>Conway's Game of Life</h1>

This project is a TUI implementation of the famous Conway's Game of Life.
[Sample Website](https://conwaylife.com/).

## Plan
- Read the initial state from a file, in `.txt` format.
- Display the initial state as white blocks on the screen in an `n x m` cartesian grid of cells.
- Progress to the next generation by following the rules of conway's game of life.

## Implementation
- File I/O: Taking the initial state as a file in a CLI argument.
- Linked List: Maintain the coordinates of all alive cells in a singly linked list.
- Structs: Coordinate of the live cell as a struct.
- Dynamic memory: Linked list uses dynamic memory allocations.
- Pointers: Pointers are clearly used in linked lists.

### Planned logic
- Make a structure for the position of a live cell.
- Maintain two linked lists, one for the current state, and one for the previous state.
- Operations on linked lists(functions):
  - Add a Node to the linked list.
  - Delete a node(even from the middle of the linked list); coordinates are unique.
- Use a TUI library(which one?) for display.
- Functions to read through the linked list and display it on the terminal.
- Read `.txt` files as CLI arguments.

## Features
- Run the program with the initial state as a CLI argument(file), and grid size `n x m`.
- The screen is filled with the current state.
- Speed up and slow down the animation using arrow keys.
- Pause and play the animation using spacebar.
- Move forward or back generation by generation.
- Limit maximum number of generations after which the program quits.
- If all cells are dead, automatically quit.
- Provide 10-15 sample initial states(as files).
- If current state is the same as the previous state(nothing changes), then quit.

## Further developments
- Camera panning
- Color gradient of dead cells with respect to time.

