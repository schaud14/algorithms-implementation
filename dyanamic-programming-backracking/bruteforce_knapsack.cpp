using namespace std;
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct track
{
	int kweight, tprofit, deleted;
	int profit1[8];
	int weight1[8];
};

int maxprofit,num,max_sol_index;

void reverseArray(int array[], int first, int last)
{
	int temp;
	while(first<last)
	{
		temp = array[first];
		array[first] = array[last];
		array[last] = temp;
		first++;
		last--;
	}
}

void incrementbit(int a[])
{
	int i, carry = 0;
	for (i=7; i >= 0; i--)
	{
		if(carry == 0)
		{
			if( a[i] == 0)
			{
				a[i]=1;
				break;
			}
			else if( a[i] == 1)
			{
				a[i] = 0;
				carry = 1;
			}
		}
		else if( carry == 1)
		{
			if(a[i] == 0)
			{
				a[i] = 1;
				carry =0;
				break;
			}
			else if( a[i] == 1)
			{
				a[i] = 0;
			}
		}
	}
}

void changeValues(struct track path[],int array[],int profit1[],int weight1[],int count,int where,int capacity,int currentNode)
{
	int i,j;
	switch (where)
	{
		case 1:
		{
			for(i=0; i< count; i++)
			{
				path[i].deleted = 0;
				path[i].tprofit = 0;
				path[i].kweight = 0;
				for(j=0; j<8; j++ )
				{
					path[i].weight1[j] = 0;
					path[i].profit1[j] = 0;
				}
			}
			break;
		}
		case 2:
		{
			for(i=0; i<count; i++)
			{
				path[currentNode].profit1[i] = array[i] * profit1[i];
				path[currentNode].weight1[i] = array[i] * weight1[i];
			}
			break;
		}
		case 3:
		{
			for(i=0; i<8; i++)
			{
				path[currentNode].kweight = path[currentNode].kweight + path[currentNode].weight1[i];
				path[currentNode].tprofit = path[currentNode].tprofit + path[currentNode].profit1[i];
			}
			break;
		}
		case 4:
		{
			for (i=0; i < count; i++)
			{
				if(path[i].kweight > capacity)
				{
					path[i].deleted = 1;
				}
			}	
			break;
		}
	}
}

void brute_force(struct track path[],int profit1[], int weight1[], int capacity, int itemCount)
{
	int array[8] = { 0, 0, 0, 0, 0, 0, 0, 1};
	int i, j, k, max, currentNode, temp;//max_sol_index;
	max = pow(2, itemCount);
	changeValues(path,array,profit1,weight1,max,1,capacity,currentNode);
	currentNode = 0;
	while(currentNode < max)
	{
		reverseArray(array, 0, 7);
		changeValues(path,array,profit1,weight1,itemCount,2,capacity,currentNode);
		reverseArray( array, 0,7);
		changeValues(path,array,profit1,weight1,8,3,capacity,currentNode);
		incrementbit(array);
		currentNode++;
	}
	changeValues(path,array,profit1,weight1,max,4,capacity,currentNode);
	temp = 0;
	for(i=0; i<max; i++)
	{
		if((path[i].tprofit > temp) && (path[i].deleted != 1))
		{
			temp = path[i].tprofit;
			max_sol_index = i;
		}
	}
}



int main(int argc, char const *argv[])
{
	int itemCount;
	int i;
	int capacity=0;
	FILE* out;
	int * weight;
	int * profit;
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
		if((fp = fopen(argv[1], "r")) == NULL) 
		{
			cout<<"Error opening file!!"<<endl;
			exit(1);
		}
		int lineNumber=1;
		size_t size=100;
		char * line = new char[size];
		if(fp)
    	while(-1 != getline(&line, &size, fp))
        {
        	switch(lineNumber)
        	{
	        	case 1:
	        	{
	        		itemCount = atoi(line);
	        		lineNumber++;
	        		break;
	        	}
	        	case 2:
	        	{
	        		i=1;
	        		weight = new int[itemCount+1];
	        		char * tokens;
	        		tokens = strtok(line, ",");
	        		while (tokens) 
					{
						weight[i++] = atoi(tokens);
						tokens = strtok(NULL, ",");
					}
	        		lineNumber++;
	        		break;
	        	}
	        	case 3:
	        	{
	        		i=1;
	        		profit = new int[itemCount+1];
	        		char * tokens;
	        		tokens = strtok(line, ",");
	        		while (tokens) 
					{
						profit[i++] = atoi(tokens);
						tokens = strtok(NULL, ",");
					}
	        		lineNumber++;
	        		break;
	        	}
	        	case 4:
	        	{
	        		capacity = atoi(line);
	        		lineNumber++;
	        		break;
	        	}
	        }
        }
	}
	int max = pow(2,itemCount);
	struct track path[max];
	brute_force(path,profit,weight,capacity,itemCount);

	/*
	Output to file: 
	*/
	if((out = fopen("brute_output.txt","w")) == NULL)
	{
		cout<<"Unbale to open brute_output.txt";
	}
	fprintf(out, "%d\n", path[max_sol_index].kweight);
	fprintf(out, "%d\n",path[max_sol_index].tprofit);
	int y=0;
	for(i = 0; i < itemCount; i++)
	{
		if(path[max_sol_index].profit1[i] != 0)
			if (path[max_sol_index].weight1[i] != 0)
			{
				if(y==0)
					{
						fprintf(out, "%d",i-1 );
						y++;
					}
				else
					fprintf(out, ", %d",i-1 );
			}
	}
	return 0;
}