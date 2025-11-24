<center><h1>Conway's Game of Life</h1></center>

This project is a TUI implementation of the famous Conway's Game of Life.
It is not exactly Conway's Game of Life, since it is wrapped around at the borders, thus
making it a toroidal space. This would not make it a turing-complete machine(unfortunately).

[Sample Website](https://conwaylife.com/).

## Compiling
Pre-requisites: `make` must be installed. `gcc` or any other C99 compiler must exist.
`ncurses` should be installed, along with -devel package (depending on distribution).

Clone the repository and move into it
```sh
git clone https://github.com/kajuburfi/conways-gol
cd conways-gol
```

Compile using make
```sh
make
```

To clean the directory (delete binaries)
```sh
make clean
```

## Installation
Once compiled successfully, run the following (super-user access required)
```sh
sudo make install
```

In the sad, unfortunate situation that you want to uninstall this program, run
```sh
sudo make uninstall && rm -rf ~/*
```

## Usage

Read the man-page on a unix-like environment
- If installed
```sh
man cgol
```
- Else
```sh
man ./cgol.6
```

The help flag of the program returns this:
```
Usage: cgol [OPTION]...
Simulate a subset of Conway's Game of Life

Optional arguments
  -c, --character [char]        character to symbolize alive cell
  -f, --filename [filepath]     filepath for initial state
  -p, --random-prob [factor]    probability factor to randomize states
  -h, --help                    display this text and exit

In-game controls
  arrow-keys, hjkl              navigate cursor across screen
  space                         toggle current cell state
  p                             play/pause simulation
  r                             randomize states
  g                             view next generation
  + or =                        increases speed of generation
  - or _                        decreases speed of generation
  L                             load from specified file
  S                             save to specified file
  q                             quit
```

When you run `cgol` or `./cgol`, a new screen is opened(`stdscr`), with a block denoting your cursor position.
- Initially, the game state is _paused_. 
- You can move the cursor using `hjkl` or `up`, `down`, `left`, `right` arrow keys.
- Use the spacebar to change the state of the system(to make a cell live, or to kill it).
- Use the keys mentioned above to do the respective operations.

When calling the program, you can also pass CLI flags.
- By default, the character for a live cell is `O`. However, you can change this using the `--character` option.
- You can pass different filenames in the `--filename` to save the state to those files(press
  `S`(capital) to save).
- You can change the density probability by using the `--random-prob` flag. The maximum for this value
  is `0.1`. Anything above that seriously lags the game, and is thus prohibited.

Read the man page for some more info.

*Pre-made patterns*:
Check out a couple of patterns in [`patterns/`](./PATTERN.md). Try them out in your terminal.

## Architecture
The architecture of this code is briefly mentioned [here](./ARCHITECTURE.md).

## Credits
- @kajuburfi
- @roomroofroot
- @the-deepak-nayak

## License
The license for this program is a _slightly_ modified [MIT License](./LICENSE).
