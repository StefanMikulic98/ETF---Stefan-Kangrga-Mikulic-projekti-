# Numerical Mathematics — C++ Project

Implementations of classical numerical methods for solving systems of linear equations, written in C++ as a university project.

## Projects

### The First Task
An introductory numerical exercise covering basic algorithm implementation in C++.

### The Second Task — Linear Equation System Solver

Solves an n×n system of linear equations using two distinct methods and compares their results.

#### Methods implemented

| Method | Class | Notes |
|--------|-------|-------|
| Gaussian elimination with partial pivoting | `SistemJednacina` | Direct method; exact solution for well-conditioned systems |
| Gauss-Seidel iteration | `SistemJednacina` | Iterative method; converges for diagonally dominant systems |

#### Features
- Parses equation strings into a coefficient matrix (`Jednacina`)
- Displays the augmented matrix at each step for debugging
- Runs both solvers and prints results side by side for comparison

#### Key concepts demonstrated

| Concept | Detail |
|---------|--------|
| Matrix representation | 2-D array stored inside `SistemJednacina` |
| Gaussian elimination | Row reduction with partial pivot selection to improve numerical stability |
| Gauss-Seidel | Iterative update until convergence within a configurable tolerance |
| String parsing | `Jednacina` tokenises an equation string into variable coefficients |
| Scientific computing in C++ | Manual matrix operations without external linear-algebra libraries |

## Building

```bash
g++ -std=c++14 -o numerical *.cpp
./numerical
```
