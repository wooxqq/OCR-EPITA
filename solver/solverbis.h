# ifndef _SOLVER_H
# define _SOLVER_H

# include <stdlib.h>
# include <stdio.h>
#define N 9

int solveSudoku(int grid[N][N], int row, int col);
int isSafe(int grid[N][N], int row,int col, int num);

# endif
