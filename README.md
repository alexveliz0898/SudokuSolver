# SudokuSolver
While browing thorugh https://projecteuler.net I came across a problem on solving sudoku puzzles
The problem set containted about 50 different problems so I thought I would solve them by writing a program for it

I downloaded the probelem set from https://projecteuler.net/problem=96 as a .txt file and ran it throught my c++ program
as a command line arguement. 

While coming up with a solution, I came across the Backtracking technique. I figuered that was a better method for solving a sudoku
puzzle than keeping track of each cell's possible candidates.

My program utilizes the backtracking method which is utilizs recursion to build solutions incrementally, solving for each cell
at a time. If we run into problems and the current solution path isnt leading is down the correct solution, the program "Backtrack"
and chooses a different candidate for the solution.

The backtracking algorithm in the program solve() utilizes a variety of helper functions that 
  - allow it to check if a cell is empty
  - check if placing the current candidate will be a valid move
  - utilizes a base case that checks if cells are empty
  
 
 
