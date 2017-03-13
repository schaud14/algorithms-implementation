using namespace std;
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

*/
int find3(int x, int * set)
{
	int root, node, parent, i;

	root = x;

	while(root != set[root]) {
		root = set[root];
		node = x;
		while(node != root) {
			parent = set[node];
			set[node] = root;
			node = parent;
		}
	}
	return root;
}
/*

*/
int union3(int x, int y, int val, int * set)
{
	int height[val];
	if (height[x] == height[y]) {
		height[x]++;
		set[y] = x;
	} else {
		if (height[x] > height[y])
			set[y] = x;
		else
			set[x] = y;
	}
}

/*
Functions For Randomized Quick Sort
*/
int generateRandomPivot(int min,int max)
{
	int random = min + rand()%(max - min + 1);
	return random;
}
int partition(int input[], int left, int right)
{
    int pivot = input[right];
    int temp;
    int j;
    int i = left;
    for (j = left; j < right; j++)
    {
        if (input[j] <= pivot)
        {
            temp = input[j];
            input[j] = input[i];
            input[i] = temp;
            i++;
        }
    }
 
    input[right] = input[i];
    input[i] = pivot;
 
    return i;
}	
int RandomizedPartition(int input[],int left, int right,int input_size)
{
  int i = generateRandomPivot(left,right);
  int pivot = input[i];
  input[i] = input[right];
  input[right] = pivot;
 i = partition(input, left, right);
 return i;
}
void RandomizedQuickSort(int input[],int left,int right,int input_size)
{
  if (left < right)
  {
    int q = RandomizedPartition(input,left,right,input_size);
    RandomizedQuickSort(input,left,q-1,input_size);
    RandomizedQuickSort(input,q+1,right,input_size);
  }
} 
/*
Quick Sort End--
*/

/*
Function to load input File(Graph) into Matrix.
*/
int ** load(char const * inputFile,FILE * fp,int vertexCount)
{
	int i = 0,j,k;
	int ** graph = new int*[vertexCount];
	for (i = 0; i < vertexCount; i++)
		graph[i] = new int[vertexCount];

	int * temp_array = new int[vertexCount * vertexCount];

	char * line = new char[100];
	char * tokens;
	i=0;
	while (fgets(line, 100, fp) != NULL) {
		tokens = strtok(line, ",");
		while (tokens) {
			temp_array[i++] = atoi(tokens);
			tokens = strtok(NULL, ",");
		}
	}

	for (i = 0, k = 0; i < vertexCount; ++i) {
		for (j = 0; j < vertexCount; ++j, k++) {
			graph[i][j] = temp_array[k];
		}
	}
	return graph;
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
			cout<<"Error opening file!"<<endl;
			exit(1);
		}
		int vertexCount = 0, i, j, k;
		vertexCount = countVertices(fp);
		rewind(fp);
		int ** graph = load(argv[1],fp,vertexCount);
		int * set = new int[vertexCount];
		int n = vertexCount;
		int edgeCount = (n*(n-1))/2;
		int ne,a,b,c,ucomp,vcomp,ned=0; 
		int edges[edgeCount][3],min[n][n],X[edgeCount][3],list[edgeCount];
		ne=0; 
		/*
		initailization of array of edges: containing two vertices and weight of the edge
		*/
		for(i=0;i<n;i++) 
		{ 
			for(j=0;j<n;j++) 
			{
				if(j>i) 
				{ 
					edges[ne][0] = i;
					edges[ne][1] = j; 
					edges[ne][2] = graph[i][j]; 
					ne++;
				}
			}
		}
		 
		/*
		Copy Weights of edges into a list
		*/
		for(i=0;i<edgeCount;i++)
		{
			list[i]=edges[i][2];
		}
		/*
		Sort New List of edges using Randomized Quick Sort
		*/	
		RandomizedQuickSort(list,0,edgeCount-1,edgeCount); 

		for(i=0;i<edgeCount;i++) 
		{
			int s = list[i];
			for(j=0;j<edgeCount;j++)
			{
				if(s==edges[j][2])
				{
					X[i][0]=edges[j][0];
					X[i][1]=edges[j][1];
					X[i][2]=edges[j][2];
					edges[j][0]=100;
					edges[j][1]=100;
					edges[j][2]=100;
					break;
				}
			}
		} 

		/*
		Loop For initialization
		*/
		for (i=0;i<n-1;i++)
		{
			for (j=0;j<3;j++)
			{ 
				min[i][j]=-1;
			}
		}      
		for(i=0;i<n;i++)
		{
			set[i]=i;
		}  

		/*
		Loop to find Spanning Tree
		*/
		int nedges=0,u=0,v=0,p=0,weight=0;
		while(nedges<n-1)
		{
			u=X[p][0];
			v=X[p][1];
			ucomp=find3(u,set);
			vcomp=find3(v,set);
		 
			if(ucomp!=vcomp)
			{
				union3(ucomp,vcomp,n,set);
				min[nedges][0]=X[p][0];
				min[nedges][1]=X[p][1];
				min[nedges][2]=X[p][2];
				nedges++;
			}
			p++;
		}
		/*
		Printing the Spanning Tree
		*/
		cout<<"Minimum Spanning Tree:"<<endl;
		cout<<"  Edge\t"<<"\t\t"<<"Weight"<<endl;
		for(i=0;i<n-1;i++)
		{
			cout<<min[i][0]<<" <--> "<<min[i][1]<<"\t\t"<<min[i][2]<<endl;
			weight = weight + min[i][2];
		}
		cout<<"Total Weight of Minimum Spanning Tree is : "<<weight<<endl;
		return 0;
	}
}