using namespace std;
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/*
Function to find Maximum of two numbers
*/
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/*
Function to find Lenght of LCS for given two strings
*/
int lcs( char *X, char *Y, int len1, int len2 )
{
   if (len1 == 0 || len2 == 0)
     return 0;
   if (X[len1-1] == Y[len2-1])
     return 1 + lcs(X, Y, len1-1, len2-1);
   else
     return max(lcs(X, Y, len1, len2-1), lcs(X, Y, len1-1, len2));
}
 

/*
Function to print the matrix
*/ 
void printmatrix(int ** matrix, int row, int column)
{
  int i,j;
  cout<<endl;
  for (i=0;i<row;i++)
  {
    for (j=0;j<column;j++)
    {
      cout<<matrix[i][j]<<"\t";
    }
    cout<<endl;
  }
    cout<<endl;
}

/*
Function to allocate 2D Integer Array.
*/
int ** allocate_matrix(int row,int column)
{
    int i;
  int ** len = new int*[row];
    for (i=0; i<row; i++)
    {
      len[i] = new int[column];
    }
  return len;
}

char * findLCS(int **len,int len1,int len2,char * string2,char* string1)
{
    int lcsLen = len[len1-1][len2-1];
        char* lcs =  new char[lcsLen+1];
        lcs[lcsLen] = '\0';
        int i = len1 - 1, j = len2 - 1;
        while (i >= 0 && j >= 0)
        {
            if (string1[i-1] == string2[j-1])
            {
                lcs[lcsLen-1] = string1[i-1]; 
                i--; j--; lcsLen--;
            }
            else if (len[i-1][j] > len[i][j-1])
                    i--;
                else
                    j--;
        } 
return lcs;
}

int main(int argc, char const *argv[])
{
    char* string1= new char[150];
    char* string2 = new char[150];
    /*
    Check for input file argument
    */
    if (argc < 2) 
    {
        cout<<"Please provide an input file!"<<endl;
        exit(1);
    }
    else
    {
        FILE *inputFile;
        /*
        Check for Null pointer error
        */
        if ((inputFile=fopen(argv[1],"r"))==NULL)
        {
            cout<<"Error! opening file"<<endl;
            exit(1);         
        }
        else 
        {
            while (fscanf(inputFile,"%s %s",string1,string2) != EOF)
            {
                /*
                Reading Two Strings from File.
                */
            }
        }
        int i ,j;
        int len1 = strlen(string1) + 1;
        int len2 = strlen(string2) + 1;

        int ** len = allocate_matrix(len1,len2);
        int ** dir = allocate_matrix(len1,len2);

        for (i = 0; i < len1; i++)
        {
            for (j = 0; j < len2; j++)
            {
                len[i][j] = lcs( string1, string2, i, j );
            }
        }
        //printmatrix(len, len1, len2);
        int lcsLen = len[len1-1][len2-1];
        char* lcs= new char[lcsLen+1];
        lcs = findLCS(len,len1,len2,string2,string1);
        cout<<"String1 : "<<string1<<endl;
        cout<<"String2 : "<<string2<<endl;
        cout << "Longest Common SubString : " <<lcs<<"     Lenght: "<<len[len1-1][len2-1]<<endl;
        return 0;
    }
}