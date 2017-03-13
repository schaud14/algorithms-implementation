using namespace std;
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int **trominoMatrix;
int currentNum = 1;


/*
Function to generate Random number within given range
*/
int generateRandom(int matrixSize)
{
	int temp = rand()%matrixSize;
	return temp;
}


/*
Function to initialize Grid
*/
void initializeGrid(int matrixSize)
{
	int i,j;
	for ( i = 0; i < matrixSize; i++) 
	{
		for ( j = 0; j < matrixSize; j++) 
		{
			trominoMatrix[i][j] = 0;
		}
	}
}

/*
Funtion to Find the quadrant of hole.
Hole is represented by value -1 
*/
int find_holeQuadrant(int hole_row, int hole_col, int rowStart ,int colStart,int newMatrixSize)
{
	if (hole_row < rowStart + newMatrixSize && hole_col < colStart + newMatrixSize) 
		return 1;
	else if (hole_row < rowStart + newMatrixSize && hole_col >= colStart + newMatrixSize)
		return 2;
	else if (hole_row >= rowStart + newMatrixSize && hole_col < colStart + newMatrixSize)
		return 3;
	else if (hole_row >= rowStart + newMatrixSize && hole_col >= colStart + newMatrixSize)
		return 4;
}

/*
Function to print Tromino Grid.
*/
void printtTromino(int matrixSize)
{
	int i,j;
	for ( i = 0; i < matrixSize; i++)
	{
		for ( j = 0; j < matrixSize; j++)
		{
			if (trominoMatrix[i][j] != -1)
			{
				printf("%3d  ",trominoMatrix[i][j]);
			}
			else
			{
				printf("%3s  ","X");
			}
		}
		printf("\n");
	}

}

/*
Recursive Funtion for Tromino Tiling Algorithm
*/
void trominoTiling(int matrixSize, int hole_row, int hole_col, int rowStart ,int colStart)
{
	/*
		-:BASE CASE:-
	*/
	if (matrixSize == 2) 
	{
		int i,j;
		for ( i = 0; i < matrixSize; i++)
		{
			for ( j = 0; j < matrixSize; j++)
			{
				if (trominoMatrix[rowStart + i][colStart + j] == 0)
				{
					trominoMatrix[rowStart + i][colStart + j] = currentNum;
				}
			}
		}
		currentNum++;
	}
	else 
	{
		/*
			-:RECURSIVE CASE:-
		*/
		int newMatrixSize = matrixSize/2;
		int quadrant = find_holeQuadrant(hole_row,hole_col,rowStart,colStart,newMatrixSize);
		switch (quadrant)
		{
			case 1 :
			{
				/*
					Recursion for Upper Left Quadrant
				*/
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart, colStart);

				/*
					Filling the Middle Tromino
				*/
				trominoMatrix[rowStart + newMatrixSize][colStart + newMatrixSize - 1] = currentNum;
				trominoMatrix[rowStart + newMatrixSize][colStart + newMatrixSize] = currentNum;
				trominoMatrix[rowStart + newMatrixSize - 1][colStart + newMatrixSize] = currentNum;

				currentNum++;

				/*
					Recursive Calls for other three Quadrants
				*/
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart, colStart + newMatrixSize);
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart + newMatrixSize, colStart);
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart + newMatrixSize, colStart + newMatrixSize);

				break;
			}
			case 2 :
			{
				/*
					Recursion for Upper Right Quadrant
				*/
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart, colStart + newMatrixSize);

				/*
					Filling the Middle Tromino
				*/
				trominoMatrix[rowStart + newMatrixSize][colStart + newMatrixSize - 1] = currentNum;
				trominoMatrix[rowStart + newMatrixSize][colStart + newMatrixSize] = currentNum;
				trominoMatrix[rowStart + newMatrixSize - 1][colStart + newMatrixSize - 1] = currentNum;

				currentNum++;

				/*
					Recursive Calls for other three Quadrants
				*/
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart, colStart);
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart + newMatrixSize, colStart);
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart + newMatrixSize, colStart + newMatrixSize);
				break;
			}
			case 3 :
			{
				/*
					Recursion for Lower Left Quadrant
				*/
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart + newMatrixSize, colStart);

				/*
					Filling the Middle Tromino
				*/
				trominoMatrix[rowStart + newMatrixSize - 1][colStart + newMatrixSize] = currentNum;
				trominoMatrix[rowStart + newMatrixSize][colStart + newMatrixSize] = currentNum;
				trominoMatrix[rowStart + newMatrixSize - 1][colStart + newMatrixSize - 1] = currentNum;

				currentNum++;

				/*
					Recursive Calls for other three Quadrants
				*/
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart + newMatrixSize, colStart + newMatrixSize);
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart, colStart);
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart, colStart + newMatrixSize);
				break;
			}
			case 4 :
			{
				/*
					Recursion for Lower Right Quadrant
				*/
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart + newMatrixSize, colStart + newMatrixSize);

				/*
					Filling the Middle Tromino
				*/
				trominoMatrix[rowStart + newMatrixSize - 1][colStart + newMatrixSize] = currentNum;
				trominoMatrix[rowStart + newMatrixSize][colStart + newMatrixSize - 1] = currentNum;
				trominoMatrix[rowStart + newMatrixSize - 1][colStart + newMatrixSize - 1] = currentNum;

				currentNum++;

				/*
					Recursive Calls for other three Quadrants
				*/
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart + newMatrixSize, colStart);
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart, colStart + newMatrixSize);
				trominoTiling(newMatrixSize, hole_row, hole_col, rowStart, colStart);
				break;
			}
		}
	}
}

int main()
{
	int i,matrixSize;
	srand(time(NULL));
	
	printf("\n\tEnter Value of k: ");
	scanf("%d",&matrixSize);
	
	matrixSize = pow(2,matrixSize);
	
	trominoMatrix = new int*[matrixSize];
	for (i=0;i<matrixSize;i++)
	{
		trominoMatrix[i] = new int[matrixSize];
	}
	
	initializeGrid(matrixSize);//,hole_row,hole_col);
	
	int hole_row  = generateRandom(matrixSize);
	int hole_col  = generateRandom(matrixSize);
	
	trominoMatrix[hole_row][hole_col] = -1;
	
	trominoTiling(matrixSize,hole_row,hole_col,0,0);
	printtTromino(matrixSize);
	
	return 0;
}

