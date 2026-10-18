# Public Transport Network Simulator (C++)

A console application that models a city's public transport network and answers route queries, built as a university project in C++.

## What it does

- Loads bus/tram stops and line definitions from input files
- Stores the network as a weighted directed graph (adjacency matrix)
- Displays information about individual stops and lines
- Finds paths between any two stops using graph traversal
- Supports bidirectional lines (Direction A and Direction B)

## Key concepts demonstrated

| Concept | Implementation detail |
|---------|-----------------------|
| Graph representation | `Matrica` — adjacency matrix mapping connections between stops |
| Pathfinding | Graph traversal (BFS/DFS) to find routes between a source and destination stop |
| Complex data modelling | `GradskiPrevoz`, `Linija`, `Stajaliste` classes reflecting real transport domain |
| File parsing | Reading stop lists and line schedules; handling malformed input |
| Exception handling | String-based exception messages for invalid stops/lines |

## Building

```bash
g++ -std=c++14 -o transport *.cpp
./transport
```
