/* 
 *We need 2 arrays 'a' and 'b', of equal size
 *Here 'a' is the primary array (i.e which contains initial 
     input, and final output)
 *And 'b' is the temporary array,
     used for merging 2 sorted half's in 'a' 
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

void merge(int *,int,int,int);
void mergesort(int *,int,int);
long long inversions;
int readfiletoarray(const char*,int x[]);

int readfiletoarray(const char* filename, int x[])
{
	FILE *fp;
	int maxline = 8;
	char str[8],*line;
	int i = 0;
	
	fp = (FILE *)fopen(filename,"r");
	if(fp == NULL)
		printf("file error, cannot open the file");
	line = fgets(str,maxline,fp);
	while(line != NULL)
	{
		x[i++] = atoi(line);
		line = fgets(str,maxline,fp);
	}
	
	fclose(fp);
	return i;
}
  
void merge(int a[], int low, int mid, int high)
{
    int* b;
    int i = low,j = mid + 1,k = 0;
	b = (int *)malloc(MAX_SIZE*sizeof(int));
  
    while (i <= mid && j <= high) {
        if (a[i] <= a[j])
            b[k++] = a[i++];
        else
            {
				b[k++] = a[j++];
				inversions = inversions + mid - i +1;
			}
    }
    while (i <= mid)
        b[k++] = a[i++];
  
    while (j <= high)
        b[k++] = a[j++];
  
    k--;
	
	//copy all the contents to array
    while (k >= 0) {
        a[low + k] = b[k];
        k--;
    }
	
	free(b);
}
  
void mergesort(int a[], int low, int high)
{	
    if (low < high) {
        int m = (high + low)/2;
        mergesort(a, low, m);
        mergesort(a, m + 1, high);
        merge(a, low, m, high);
    }
}

void main(int argc, char** argv)
{
	int* array;	
	int length;
	int i;
	const char* filename;
	
	array = (int *)malloc(MAX_SIZE*sizeof(int));
	
	if(argc>=2)
		filename = argv[1];
		
	length = readfiletoarray(filename,array);	
	printf("Length of array is %d",length);
	
	mergesort(array,0,length-1);
	
	printf("\n number of inversions = %lld",inversions);
	
	free(array);
}