using namespace std;
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 999
/*
Function to count total vertices in input Graph
*/
int countVertices(FILE * fptr)
{
	int msize=0;size_t size=100;
	char * line =(char*) malloc(size);
    if(fptr)
    	while(-1 != getline(&line, &size, fptr))
        {
            msize++;
        }
        return msize;
}
/*
Funcation For allocating memery to the graph array
*/
int ** allocateGraph(int vertexCount)
{
	int i = 0;
	int ** graph = new int*[vertexCount];
	for (i = 0; i < vertexCount; i++)
		graph[i] = new int[vertexCount];
	return graph;
}

/*
Function to load data from input file into Graph
*/
int **load(char const * inputFile,FILE * fp,int vertexCount)
{
	int i = 0,j,k;
	int ** graph = allocateGraph(vertexCount);
	int * temp_array = new int[vertexCount * vertexCount];

	char * line = new char[100];
	char * tokens;
	i=0;
	while (fgets(line, 100, fp) != NULL) 
	{
		tokens = strtok(line, ",");
		while (tokens) 
		{
			temp_array[i++] = atoi(tokens);
			tokens = strtok(NULL, ",");
		}
	}
	for (i = 0, k = 0; i < vertexCount; ++i) 
	{
		for (j = 0; j < vertexCount; ++j, k++) 
		{
			graph[i][j] = temp_array[k];
		}
	}
	return graph;
}

/*
Function to update the closed array which maintains visited virtices in Graph
*/
int inclose(int i,int n1, int * closed) 
{  
	int j; 
	for(j=0;j<=n1;j++) 
		if(closed[j]==i) 
			return 1; 
		return 0;
}

/*
Function to Find minimum Spanning tree using Prims Algorithm
*/
void primSpanningTree(int ** graph,int * closed,int **new_graph,int vertexCount ) 
{ 
	int i=0,j,count=0; 
	int min,k,v1=0,v2=0; 
	closed[0]=0; 
	while(count<vertexCount-1) 
	{ 
		min=INF; 
		for(i=0;i<=count;i++) 
			for(j=0;j<vertexCount;j++) 
				if(graph[closed[i]][j]<min && !inclose(j,count,closed)) 
					{ 
						min=graph[closed[i]][j]; 
						v1=closed[i]; v2=j;
					}
		new_graph[v1][v2]=new_graph[v2][v1]=min; 
		count++; 
		closed[count]=v2; 
	}
}

/*
Function to initialize the array to INF value.
*/
void initializeGraph(int vertexCount, int **new_graph,int * vertex)
{
	int i,j;
	for(i=0;i<vertexCount;i++) 
	{ 
		vertex[i]=i+1; 
		for(j=0;j<vertexCount;j++) 
		{ 
			new_graph[i][j]=INF;
		}
	}
}

/*
Function to Print the MST for input Graph.
*/
void printOutput(int vertexCount,int * vertex,int ** new_graph)
{
	int sum=0, i,j;
	cout<<"MINIMUM SPANNING TREE"<<endl;
		cout<<"Edge\t\tWeight";
		for(i=0;i<vertexCount;i++) 
			for(j=i+1;j<vertexCount;j++) 
				if(new_graph[i][j]!=INF) 
				{ 
					cout<<endl<<vertex[i]<<" <--> "<<vertex[j]<<"\t"<<new_graph[i][j];
					sum = sum + new_graph[i][j];
				}
		cout<<endl<<"Total Weight of Minimum Spanning Tree : "<<sum<<endl;
}

int main(int argc, char const *argv[])
{
	int i;
	/*
	Check for input file argument
	*/
	if (argc < 2) {
		cout<<"Please provide an input file!"<<endl;
		exit(1);
	}
	else
	{
		FILE *fp;
		/*
		Check for Null pointer error
		*/
		if((fp = fopen(argv[1], "r")) == NULL) 
		{
			cout<<"Error opening file!!"<<endl;
			exit(1);
		}
		int vertexCount = 0, i, j, k;
		vertexCount = countVertices(fp);
		rewind(fp);
		int * vertex = new int[vertexCount];
		int ** graph = load(argv[1],fp,vertexCount);	
		int ** new_graph = allocateGraph(vertexCount);
		int * closed = new int[vertexCount];
		initializeGraph( vertexCount, new_graph,vertex);
		primSpanningTree(graph,closed,new_graph,vertexCount); 
		printOutput( vertexCount,vertex,new_graph);
		return 0;
	}
}