# Tetris

Feeling inspired after watching
[Tetris (2023)](https://en.wikipedia.org/wiki/Tetris_(film)) (especially
[this scene](https://www.youtube.com/watch?v=c0qEO3gisvo)), I decided to make a
terminal-based Tetris in C. This is the result of that.


```
           <!                          !>
           <!                          !>
           <!                          !>
           <!                          !>
           <!                          !>
           <!                          !>
           <!                          !>
           <!                          !>
           <!                          !>
           <!      []                  !>
           <!      [][]                !>          SCORE: 19
           <!      []                  !>
           <!                          !>
           <!                          !>
           <!                          !>
           <!                          !>
           <!                          !>
           <!      ()        []      []!>
           <!      ()()    [][]      []!>
           <!      ()[][][][][]    [][]!>
           <!==========================!>
             \/\/\/\/\/\/\/\/\/\/\/\/\/
```

Check out [this](https://www.youtube.com/watch?v=iaHm9NIWYfU) YouTube video for
a gameplay.


# How to play?

## Building and running

Download the source code or clone the repository
```bash
git clone https://github.com/rajdeep-314/tetris-c
```

Build the executable using `make`
```bash
make tetris
```

And then execute the executable to start playing
```bash
./tetris
```

To build and then run in a single command, you can use
```bash
make run
```

## Controls

### Main screen

- `x` : Exit
- `a`, `h` : Move the block left
- `d`, `l` : Move the block right
- `s` : Gentle drop
- `␣` : Hard drop
- `p` : Pause
- `r` : Restart
- `t` : Refresh (in case of a visual glitch)
- `w`, `k` : Rotate the block clockwise by $90^\circ$

### Pause screen

- `p` : Resume
- `x` : Exit

### Game over screen

- `p` : Play again
- `x` : Exit

