# Brainfuck Interpreter

A visual brainfuck interpreter that shows you what's happening in real-time. It displays the memory grid as the program runs, highlights the current instruction, and shows the output.

## What it does

- Shows a live memory grid (4 rows of 16 cells each)
- Highlights the current instruction in red
- Displays program output at the bottom
- You can step through execution with the `-m` flag
- Supports a halt instruction (`H`) to pause execution

## Building

First, make sure you have SDL2 and SDL2_ttf installed. Then:

```bash
mkdir build
cd build
cmake .. -GNinja
ninja
```

## Running

```bash
# Run a brainfuck program normally
./bfi ../prime.bf

# Run with step-through mode (hit any key to advance)
./bfi ../prime.bf -m
```

## Dependencies

You'll need:
- SDL2
- SDL2_ttf
- CMake
- Ninja

## A note about the code

The variable names in this project are... let's say "creative". I went with a mix of Greek letters, unicode emojis, and nonsense words instead of the usual descriptive names.

