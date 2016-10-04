
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void transpose_old(int* dst, int* src, int dim)
{
	printf("transpose_old called\n");
	int i, j;
	for(i = 0; i< dim; i++)
	{
		for(j = 0; j< dim; j++)
		{
			dst[j* dim + i] = src [i* dim + j ];
		}
	}
}

void transpose_new(int* dst, int *src, int dim)
{
	printf("transpose_new called\n");
	int i, j, k, l;
	int kaccum, laccum;
	//found out blockdim using 2 * (blockDim) * (blockDim) * sizeof(int) = 32768 (L1 cache size)

	int blockDim = (dim > 8) ? 8: dim;
	for(i = 0; i< dim; i+= blockDim)
	{
		for(j = 0; j< dim; j+= blockDim)
		{
			kaccum = 0;
			for(k = i; k < i+ blockDim && i < dim; k++)
			{
				laccum = 0;
				for(l = j; l < j + blockDim && j < dim; l++)
				{
					dst[laccum+ k] = src[kaccum + l];
					laccum+= dim;
				}
			}
			kaccum+= dim;
		}
	}
}


 
int main(int argc, char* argv[])
{
  int dim = 20000;
 
  int *src = malloc(dim*dim * sizeof(int));
  int *dest = malloc(dim*dim * sizeof(int));
                                                                                                                                                                                                                                                               
 
  int  count = 0;
  for(int i = 0; i<dim; i++)
    for(int j = 0; j<dim; j++)
      src[i*dim + j] = count++;
 
 
  //time this                                                                                                                                     
 
  clock_t start, end;
  double cpu_time_used;
 
  start = clock();
 
  transpose_old(dest, src, dim);
  //transpose_new(dest, src, dim);                                                                                                                          
 
  end = clock();
 
  cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
 
 printf("%f\n",cpu_time_used);
 
 free(src);
 free(dest);
 return 0;
}
