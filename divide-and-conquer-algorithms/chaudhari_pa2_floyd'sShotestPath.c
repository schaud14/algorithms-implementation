#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int msize = 0;
/*
Function to print matrix
*/
char * str = NULL;
void printMatrix(int matrix[msize][msize], int inputSize)
{
    int i,col;
    printf("\n");
    for (i=1;i<inputSize;i++)
    {
        for (col=1;col<inputSize;col++)
        {
            printf("%2d\t",matrix[i][col]);
        }
        printf("\n");
    }
}

/*
Function to load input data intp matrix
*/
loadMatrix(int matrix[msize][msize])
{
    int row = 0;
    size_t size = 100;
    char * line = malloc(size);
    char * token;
    int val,i=0,col=1;

    FILE * ptr=fopen(str,"r");
    while(-1 != getline(&line, &size, ptr))
    {
        row++;
        col=1;
        //fprintf(stderr, "%d\n", row);
        //printf("%s\n",line );
        token = strtok(line,",");
        if (token != NULL)
            {
                val = atoi(token);
                //fprintf(stderr, "val is ------------%d\n", val);
                matrix[row][col] = val;
                col++;
            }
        while(token != NULL)
        {        
            token = strtok (NULL, ",");
            if (token != NULL)
            {
                val = atoi(token);  
                //fprintf(stderr, "val is ------------%d\n", val);
                matrix[row][col] = val;
                col++;
            }
        }
        //fprintf(stderr, "\n" );
    }
}

/*
Funtion to initialize matrix
*/
void initializeMatix(int matrix[msize][msize])
{
	int i,j;
	for(i=1; i<msize; i++)
    {
    	for(j=1; j<msize; j++)
		{
			matrix[i][j]=0;
		}
	}
}

/*
    Function to calculate Shortest path by Floyds Algorithm
*/
void floyd(int matrix[msize][msize], int path[msize][msize] ,int temp[msize][msize])
{
    loadMatrix(temp);
	int k,i,j;
        for(k=1;k<msize;k++)
        {
                for(i=1;i<msize;i++)
                {
                        for(j=1;j<msize;j++)
                        {
                            if(temp[i][j] > temp[i][k] + temp[k][j] && (temp[k][j] != 500 && temp[i][k] != 500))
                            {
                            	temp[i][j] = temp[i][k] + temp[k][j];
                            	path[i][j] = k;
                            }    	
                        }
                }
        //printMatrix(temp,msize);
        }    
}


int main(int argc, char *argv[])
{
    size_t size = 100;
    int node1,node2,result;
    char * line = malloc(size);
    str = argv[1];
    FILE * ptr=fopen(argv[1],"r");
    if (ptr)
    {
	    while(-1 != getline(&line, &size, ptr))
	        {
	            msize++;
	        }
	    msize++;
	    int matrix[msize][msize];
	    int path[msize][msize];
	    int temp[msize][msize];
	    initializeMatix(path);
	    loadMatrix(matrix);
	    printf("\nInput (D) Matrix is : \n");
	    printMatrix(matrix,msize);

	    floyd(matrix,path,temp);
	    
	    printf("\n%s\n","Path matrix :");
	    printMatrix(path,msize);
	    
	    printf("\n%s\n","Final D Matrix :");
	    printMatrix(temp,msize);

	/*
	Print Shortest path for each pair of node.
	*/
	    printf("\n%s\n","Shortest Path are as follows:");
	    for(node1=1;node1<msize;node1++)
	    {
	        printf("\t%s %d \n", "From Node ",node1);
	        for(node2=1;node2<msize;node2++)
	        {
	            printf("< %d, %d > = %d\n",node1,node2,temp[node1][node2]);
	        }
	    }
	}
	else
	{
		printf("%s\n","File Not Found");
		exit(0);
	}
}
