using namespace std;
#include <iostream>
#include <stdlib.h>
#include <time.h>

/*
	Function to allocate memory to initialized matrix.
*/
int ** allocate_matrix(int inputSize)
{
	int i,j;
	int ** matrix = new int*[inputSize];
	for (i=0; i<inputSize; i++)
	{
		matrix[i] = new int[inputSize];
	}

	for(i=0; i<inputSize; i++)
    {
    	for(j=0; j<inputSize; j++)
		{
			matrix[i][j]=0;
		}
	}
	return matrix;
}

/*
	Function to Generated random matrix.
*/
void generateRandomMatrix(int** matrix ,int inputSize)
{
	int random,i,j;
	for (i=0;i<inputSize;i++)
	{
		for (j=0;j<inputSize;j++)
		{
			matrix[i][j] = rand()%21 - 10;
		}
	}
}

/*
	Function to print matrix.
*/
void printMatrix(int ** matrix, int inputSize)
{
	int i,j;
	//printf("\n");
	cout<<endl;
	for (i=0;i<inputSize;i++)
	{
		for (j=0;j<inputSize;j++)
		{
			cout<<matrix[i][j]<<"\t";
			//printf("%2d\t",matrix[i][j]);
		}
		//printf("\n");
		cout<<endl;
	}
		cout<<endl;
}


/*
	Function to copy data of one matrix to another with required offset of rows and columns at right value.
*/
int ** copyData (int **inputMatrix,int **subMatrix,int newInputSize,int rowOffset,int colOffset)
{	
	int i,j;
	for(i=0; i<newInputSize; i++)
	{
		for(j=0; j<newInputSize; j++)
		{
			
			subMatrix[i][j] = inputMatrix[i+rowOffset][j+colOffset];
		//fprintf(stderr, "%s\n","second");
		
		}
	}
return subMatrix;
}


/*
	Function to add two matrices.
*/
int ** add_matrices(int  **matrix1, int **matrix2, int newInputSize)
{
		
	int i,j;
	int **temp = allocate_matrix(newInputSize);
	for(i=0; i<newInputSize; i++)
	{
		for(j=0; j<newInputSize; j++)
		{
			temp[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
	return temp;
}

/*
	Function to subtract two matrices.
*/
int ** subtract_matrices(int **matrix1,int **matrix2, int newInputSize)
{
	int i,j;
	int **temp = allocate_matrix(newInputSize);
	for(i=0; i<newInputSize; i++)
	{
		for(j=0; j<newInputSize; j++)
		{
			temp[i][j] = matrix1[i][j] - matrix2[i][j];
		}
	}
	return temp;
}

/*
	Function to copy data of one matrix to another with required offset of rows and columns at left value.
*/
int ** copyResult(int **matrix,int**temp,int newInputSize,int rowOffset,int colOffset)
{
	int i,j;
	for(i=0; i<newInputSize; i++)
	{
		for(j=0; j<newInputSize; j++)
		{
			matrix[i+rowOffset][j+colOffset] = temp[i][j];
		}
	}
	return matrix;
}


/*
	Traditional Method for Matrix multiplication.
*/
int ** matrixMulti(int ** matrix1, int ** matrix2, int inputSize)
{
	int i,j,k;
	int ** temp = allocate_matrix(inputSize);

	for (i = 0; i < inputSize; i++)
        {
            for (j = 0; j < inputSize; j++)
            {
                temp[i][j] = 0;
                for (int k = 0; k < inputSize; k++)
                {
                    temp[i][j] = temp[i][j] + matrix1[i][k] * matrix2[k][j];
                }
            }
        }
    return temp;
}


/*
	Recursive Function for Strassen's Matrix Multiplication
*/
int ** strassenMulti(int ** matrix1,int ** matrix2, int inputSize)
{
	int **m1,**m2,**m3,**m4,**m5,**m6,**m7;
	int **a11,**a12,**a21,**a22;
	int **b11,**b12,**b21,**b22;
	int **temp1, **temp2 ,**matrix;
	matrix = allocate_matrix(inputSize);
	
	/*
		-:BASE CASE:-
		if matrix size is 2 then calculate matrix directly.
	*/
	if (inputSize <= 2)
	{
		int m1,m2,m3,m4,m5,m6,m7;
		m1 = (matrix1[0][0] + matrix1[1][1]) * (matrix2[0][0] + matrix2[1][1]);
		m2 = (matrix1[1][0] + matrix1[1][1]) * matrix2[0][0];
		m3 =  matrix1[0][0] * (matrix2[0][1] - matrix2[1][1]);
		m4 =  matrix1[1][1] * (matrix2[1][0] - matrix2[0][0]);
		m5 = (matrix1[0][0] + matrix1[0][1]) * matrix2[1][1];
		m6 = (matrix1[1][0] - matrix1[0][0]) * (matrix2[0][0] + matrix2[0][1]);
		m7 = (matrix1[0][1] - matrix1[1][1]) * (matrix2[1][0] + matrix2[1][1]);		

		matrix[0][0] = m1+m4-m5+m7; 
		matrix[0][1] = m3+m5;
		matrix[1][0] = m2+m4;
		matrix[1][1] = m1+m3-m2+m6;
		
		return matrix;
	}
	else
	{
		/*
			-:RECURSIVE CASE:-
			Redece input size in half 
			resulting in 4 new sub matrices
		*/
		int newInputSize = inputSize / 2;
		
		/*
			allocatate 4 matrices in first input
		*/
		a11 = allocate_matrix(newInputSize);
		a12 = allocate_matrix(newInputSize);
		a21 = allocate_matrix(newInputSize);
		a22 = allocate_matrix(newInputSize);

		/*
			allocatate 4 matrices in second input
		*/
		b11 = allocate_matrix(newInputSize);
		b12 = allocate_matrix(newInputSize);
		b21 = allocate_matrix(newInputSize);
		b22 = allocate_matrix(newInputSize);

		/*
		Allocating temporary matrices for calculations
		*/
		temp1 = allocate_matrix(newInputSize);
		temp2 = allocate_matrix(newInputSize);

		/*
		Allocation of m1 to m7 matrices
		*/
		m1 = allocate_matrix(newInputSize);		
		m2 = allocate_matrix(newInputSize);
		m3 = allocate_matrix(newInputSize);
		m4 = allocate_matrix(newInputSize);
		m5 = allocate_matrix(newInputSize);
		m6 = allocate_matrix(newInputSize);
		m7 = allocate_matrix(newInputSize);

		/*
			copy elements in respected matrices
		*/
		a11 = copyData(matrix1,a11,newInputSize,0,0);
		//printMatrix(a11,newInputSize);
		a12 = copyData(matrix1,a12,newInputSize,0,newInputSize);
		//printMatrix(a12,newInputSize);
		a21 = copyData(matrix1,a21,newInputSize,newInputSize,0);
		//printMatrix(a21,newInputSize);
		a22 = copyData(matrix1,a22,newInputSize,newInputSize,newInputSize);
		//printMatrix(a22,newInputSize);

		b11 = copyData(matrix2,b11,newInputSize,0,0);
		//printMatrix(b11,newInputSize);
		b12 = copyData(matrix2,b12,newInputSize,0,newInputSize);
		//printMatrix(b12,newInputSize);
		b21 = copyData(matrix2,b21,newInputSize,newInputSize,0);
		//printMatrix(b21,newInputSize);
		b22 = copyData(matrix2,b22,newInputSize,newInputSize,newInputSize);
		//printMatrix(b22,newInputSize);
		
		//cout <<"after Copy";
		temp1 = add_matrices(a11,a22,newInputSize);
		temp2 = add_matrices(b11,b22,newInputSize);
		
		m1 = strassenMulti(temp1,temp2 ,newInputSize);
		// cout<<"---m1";
		// printMatrix(m1,newInputSize);	
		
		temp1 = add_matrices(a21,a22,newInputSize);
		m2 = strassenMulti(temp1,b11,newInputSize);
		// cout<<"---m2";
		// printMatrix(m2,newInputSize);

		temp2 = subtract_matrices(b12,b22,newInputSize);
		m3 = strassenMulti(a11,temp2,newInputSize);
		// cout<<"---m3";
		// printMatrix(m3,newInputSize);

		temp2 = subtract_matrices(b21,b11,newInputSize);
		m4 = strassenMulti(a22,temp2,newInputSize);
		// cout<<"---m4";
		// printMatrix(m4,newInputSize);

		temp1 = add_matrices(a11,a12,newInputSize);
		m5 = strassenMulti(temp1,b22,newInputSize);
		// cout<<"---m5";
		// printMatrix(m5,newInputSize);

		temp1 = subtract_matrices(a21,a11,newInputSize);
		temp2 = add_matrices(b11,b12,newInputSize);
		m6 = strassenMulti(temp1,temp2,newInputSize);
		// cout<<"---m6";
		// printMatrix(m6,newInputSize);

		temp1 = subtract_matrices(a12,a22,newInputSize);
		temp2 = add_matrices(b21,b22,newInputSize);
		m7 = strassenMulti(temp1,temp2,newInputSize);
		// cout<<"---m7";
		// printMatrix(m7,newInputSize);

		/*
		Collaborating results
		*/ 

		temp1 = add_matrices(m1,m4,newInputSize);
		temp1 = subtract_matrices(temp1,m5,newInputSize);
		temp1 = add_matrices(temp1,m7,newInputSize);
		matrix = copyResult(matrix,temp1,newInputSize,0,0);
		// cout<<"Quadrant 1";
		// printMatrix(matrix,inputSize);

		temp1 = add_matrices(m3,m5,newInputSize);
		matrix = copyResult(matrix,temp1,newInputSize,0,newInputSize);
		// cout<<"Quadrant 2";
		// printMatrix(matrix,inputSize);

		temp1 = add_matrices(m2,m4,newInputSize);
		matrix = copyResult(matrix,temp1,newInputSize,newInputSize,0);
		// cout<<"Quadrant 3";
		// printMatrix(matrix,inputSize);

		temp1 = add_matrices(m1,m3,newInputSize);
		temp1 = subtract_matrices(temp1,m2,newInputSize);
		temp1 = add_matrices(temp1,m6,newInputSize);
		matrix = copyResult(matrix,temp1,newInputSize,newInputSize,newInputSize); 
		// cout<<"Quadrant 4";
		// printMatrix(matrix,inputSize);

		return matrix;

	}
	
}
/*
	Function to Check Validity of Input.
*/
int inputCheck(int x)
{
	while (((x % 2) == 0) && x > 1) /* While x is even and > 1 */
   		{
   			x /= 2;
   		}
 	if (x == 1)
 		return x;
 	else
 		return -1;
}


int main()
{
	int inputSize,i,j;
	srand (time(NULL));
	do
	{
		cout<<"Enter the input size (in Power of 2):  ";
		cin>>inputSize;
	}while (inputCheck(inputSize) != 1);

	/*
	Allocation and Generation random matrices for given input.
	*/
	int ** matrix1 = allocate_matrix(inputSize);
	generateRandomMatrix(matrix1,inputSize);
	cout <<endl<<"matrix 1 Generated :"<<endl;
	printMatrix(matrix1,inputSize);

	int ** matrix2 = allocate_matrix(inputSize);
	generateRandomMatrix(matrix2,inputSize);
	cout <<endl<<"matrix 2 Generated :"<<endl;
	printMatrix(matrix2,inputSize);

	/*
	Allocating Matrices to store Final results.
	*/
	int ** matrix = allocate_matrix(inputSize);
	int ** matrix3 = allocate_matrix(inputSize);
	
	/*
	matrix multiplication by Strassen's Method 
	*/
	matrix = strassenMulti(matrix1,matrix2,inputSize);
	
	/*
	matrix multiplication by traditional Method 
	*/
	matrix3 = matrixMulti(matrix1,matrix2,inputSize);
	
	cout<<endl<<"The Matrix multiplication by Strassen's Method"<<endl;
	printMatrix(matrix3,inputSize);
	cout<<endl<<"The Matrix multiplication by Traditional Method"<<endl;
	printMatrix(matrix,inputSize);
	return 0;
}