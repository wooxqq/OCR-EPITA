#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solverbis.h"
#define N 9
#define MAX_LINE_LENGTH 1000

void implement(FILE *ptr,int grid[N][N])
{
	char line[MAX_LINE_LENGTH];
	size_t x=0;
	size_t count=0;
	while(fgets(line,MAX_LINE_LENGTH,ptr))
	{
		if(strlen(line)!=1) //si c'est une vraie ligne
		{
			for (size_t i=0;i<strlen(line);i++)
			{
				if(line[i]!=' ' && i!=11)//si il y'a un chiffre
				{
				   if (line[i]=='.'){grid[x][i-count] =0 ;}
				
				   else
				   {
					   grid[x][i-count] =(int)line[i]-48;
				   }
				}
			        else{count++;}	
			}
			x++;
		}
		count=0;
	}	
}

void write(int grid[N][N],FILE *ptw)
{
	for (size_t row = 0;row<9;row++)
	{
		for (size_t col=0;col<9;col++)
		{
			fprintf(ptw,"%d",grid[row][col]);
			if (col == 2 || col ==5){fprintf(ptw," ");}
		}
		fprintf(ptw,"\n");
		if (row ==2 ||row ==5){fprintf(ptw,"\n");}
	}
}

int main (int argc, char *argv[])
{	
	if (argc != 2){errx(EXIT_FAILURE,"Only one parameter is required");}	

	FILE *ptr = fopen(argv[1],"r");
	int grid[N][N];
	implement(ptr,grid);
	if (solveSudoku(grid,0,0) == 1)
	{
		FILE *ptw = fopen(strcat(argv[1],".result"),"w");
		write(grid,ptw);
		fclose(ptr);
		fclose(ptw);
	}
	else
	{
		fclose(ptr);
		errx(EXIT_FAILURE,"The sudoku has no solution");
	}
}
