# Virtual File System Simulator (C++)

A command-line simulation of a hierarchical file system, implemented as a university assignment in C++.

## What it does

- Loads a file system hierarchy from an input file
- Represents directories and files as nodes in a tree structure
- Parses and executes file system commands (similar to shell commands)
- Logs operations to an output file

## Key concepts demonstrated

| Concept | Implementation detail |
|---------|-----------------------|
| Tree data structure | `FSnode` represents each file/directory; parent/child pointers form the hierarchy |
| Command parser | `FSparser` tokenises input strings into commands and arguments |
| File I/O | Reading hierarchy definitions and writing operation logs |
| OOP design | `FileSystem`, `FSnode`, `FSparser` with single-responsibility separation |
| Recursive traversal | Listing and searching the directory tree recursively |

## Building

```bash
g++ -std=c++14 -o filesystem *.cpp
./filesystem
```
