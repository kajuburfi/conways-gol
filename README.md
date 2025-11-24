<center><h1>Conway's Game of Life</h1></center>

This project is a TUI implementation of the famous Conway's Game of Life.
It is not exactly Conway's Game of Life, since it is wrapped around at the borders, thus
making it a toroidal space. This would not make it a turing-complete machine(unfortunately).

[Sample Website](https://conwaylife.com/).

## How to install
Pre-requisites: `git` must be installed. `gcc` or any other C compiler must exist.
`ncurses` should also be there(comes pre-installed in most distributions).

Clone the repository and move into it
```sh
git clone https://github.com/kajuburfi/conways-gol
cd conways-gol
```

Compile using the `-lncurses` flag
```sh
gcc -o <executable_name> cgol.c -lncurses
```

Read the man-page on a unix-like environment
```sh
man ./cgol.6
```

If you want to be able to run this from anywhere in your system,
add the executable `cgol` to your `$PATH`. One such place would be,
```sh
cp cgol ~/.local/bin/
```
To read the `man` page from anywhere, copy the man page `cgol.6` to
any place that your man pages are stored. For instance(make the directory if not existing),
```sh
cp cgol.6 /usr/local/man/man6/
```

## Usage

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

## Architecture
The architecture of this code is briefly mentioned [here](./ARCHITECTURE.md).

## Credits
- @kajuburfi
- @roomroofroot
- @the-deepak-nayak

## License
The license for this program is a _slightly_ modified [MIT License](./LICENSE).
