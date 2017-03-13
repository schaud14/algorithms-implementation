using namespace std;
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxprofit=0;
int num=0;

void printInput(int itemCount, int weights[], int profit[], float profitByWeight[],int capacity )
{
	int i;
	cout<<"Input Data:"<<endl;
	cout<<itemCount<<endl;
	for (i = 0; i < itemCount; i++)
	{
		if (i == itemCount-1)
		{
			cout<<weights[i]; 
		}
		else
		{
			cout<<weights[i]<<", ";
		}
	}
	cout<<endl;
	for (i = 0; i < itemCount; i++)
	{
		if (i == itemCount-1)
		{
			cout<<profit[i]; 
		}
		else
		{
			cout<<profit[i]<<", ";
		}
	}
	cout<<endl;
	cout<<capacity<<endl;
	cout<<"profitByWeight"<<endl;
	for (i = 0; i < itemCount; i++)
	{
		if (i == itemCount-1)
		{
			cout<<profitByWeight[i]; 
		}
		else
		{
			cout<<profitByWeight[i]<<", ";
		}
	}
	cout<<endl;
}

float * calculateProfitByWeight(int itemCount, int weights[], int profit[])
{
	int i;
	float * temp = new float[itemCount];
	for(i = 0; i < itemCount; i++)
	{
		temp[i] = (float)profit[i]/(float)weights[i];
	}
	return temp;
}

void iswap(int position1, int position2, int array[])
{
	int temp;
	temp = array[position1];
	array[position1] = array[position2];
	array[position2] = temp; 
}

void fswap(int position1, int position2, float array[])
{
	float temp;
	temp = array[position1];
	array[position1] = array[position2];
	array[position2] = temp; 
}

void sortInputData(int itemCount, int weights[], int profit[], float profitByWeight[])
{
	int i,j;
	for(i = 0; i < itemCount; i++)
	{
		for(j = i+1; j<itemCount; j++)
		{
			if(profitByWeight[i]<profitByWeight[j])
			{
				fswap(i,j,profitByWeight);
				iswap(i,j,profit);
				iswap(i,j,weights);
			}
		}
	}
}


float fractionalUpperBound(int i, int weight, int profit1, int weights[], int profit[], int capacity, int itemCount)
{
	float bound;
	int j = 0;
	int x[itemCount];

	bound = profit1;

	for(j=i; j<=itemCount; j++)
	{
		x[j] = 0;
	}

	while((weight < capacity) && (i<=itemCount))
	{
		if(weight + weights[i] <= capacity)
		{
			x[i]=1;
			weight = weight + weights[i];
			bound = bound + profit[i];
		}
		else
		{
			x[i] = (capacity - weight)/weights[i];
			weight = capacity;
			bound = bound + profit[i]*x[i];
		}

		i=i+1;
	}
	return bound;
}
int promising(int i, int weight, int profit1, int weights[], int profit[], int capacity, int itemCount)
{
	int upperBound;

	if( weight >= capacity)
		return 0;
	upperBound = fractionalUpperBound(i+1, weights[i], profit[i], weights, profit, capacity, itemCount);
	return (upperBound > maxprofit);
}

void backtrack(int i, int weight, int profit1, int weights[], int profit[], int capacity, int itemCount, int include[], int bestset[])
{
	int k;
	if(weight <= capacity && profit1 > maxprofit)
	{
		maxprofit = profit1;
		num=i;
		for(k = 0; k<=itemCount; k++)
			bestset[k] = include[k];
	}

	if(promising(i, weight, profit1, weights, profit, capacity, itemCount))
	{
		include[i+1] = 1;
		backtrack(i+1, weight+weights[i+1], profit1+profit[i+1], weights, profit, capacity, itemCount, include, bestset);
		include[i+1] = 0;
		backtrack(i+1, weight, profit1, weights, profit, capacity, itemCount, include, bestset);
	}

}

int main(int argc, char const *argv[])
{
	int weight=0;
	int profit1=0;
	int itemCount;
	int * weights;
	int * profit;
	int i;
	int * include;
	int * bestset;
	int capacity=0;
	FILE* out;
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
	        		weights = new int[itemCount+1];
	        		char * tokens;
	        		tokens = strtok(line, ",");
	        		while (tokens) 
					{
						weights[i++] = atoi(tokens);
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
	float * profitByWeight = new float[itemCount];
	include = new int[itemCount+1];
	bestset = new int[itemCount+1];
	profitByWeight = calculateProfitByWeight(itemCount,weights,profit);
	sortInputData(itemCount,weights,profit,profitByWeight);
	int tweight = 0;
	for(i=1; i<=itemCount; i++)
	{
		include[i] = 0;
		bestset[i] = 0;
	}
	backtrack(0, 0, 0, weights, profit, capacity, itemCount, include, bestset);

	for(i = 1; i<=itemCount;i++)
	{
		if(bestset[i] == 1)
		{
			tweight = tweight + weights[i];
		}
	}
	if((out = fopen("backtrack_output.txt","w")) == NULL)
	{
		cout<<"Unbale to open brute_output.txt";
	}
	fprintf(out, "%d\n", tweight);
	fprintf(out, "%d\n",maxprofit);
	int y=0;
	for(i = 0; i<=itemCount+1;i++)
	{
		if(bestset[i] == 1)
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



