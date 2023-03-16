# Breadth-First-Search
# Wolf, Goat, Cabbage and Water Jugs Puzzles

This repository contains two classic puzzle-solving programs: the Wolf, Goat, Cabbage puzzle, and the Water Jugs puzzle.

## Wolf, Goat, Cabbage

The program `wolfGoatCabbage.cpp` solves the classic Wolf, Goat, Cabbage problem.

**Problem**: You are standing with a wolf, goat, and cabbage, next to a river, and you would like to transport all three of these items to the other side. However, you only have access to a small boat that can fit at most one item (besides yourself). If you leave the wolf and goat alone unattended, bad things happen to the goat. If you leave the goat and cabbage unattended, bad things happen to the cabbage.

**Solution**: The program performs a breadth-first search to find the solution and outputs the steps required to safely transport all items across the river.

## Water Jugs

The program `waterJugs.cpp` solves the Water Jugs problem.

**Problem**: You are standing next to a river with a very content-looking wolf, a head of cabbage, and two water jugs, which have integer sizes A = 3 and B = 4. In order to boil the cabbage for your dinner, you would like to measure out exactly 5 units of water.

**Solution**: The program performs a breadth-first search to find the sequence of actions required to measure out exactly 5 units of water using the two jugs.

## How to run the programs

1. Compile the C++ source files using a C++ compiler (e.g., g++):
```bash
g++ -o wolfGoatCabbage wolfGoatCabbage.cpp
g++ -o waterJugs waterJugs.cpp

2. Run the compiled programs:
```bash
g++ -o wolfGoatCabbage wolfGoatCabbage.cpp
g++ -o waterJugs waterJugs.cpp
./wolfGoatCabbage
./waterJugs

Both programs will output the steps required to solve their respective puzzles.
