#include "func.h"
#include <omp.h>

//#define NUM_THREADS 20

void Func1(int c[][TSIZE], int a[][TSIZE], int b[][TSIZE])
{
	int i, j, k, l, m;
	int temp;
	//#pragma omp parallel for default(none) shared(a,b,c) private(i, j,k, temp) collapse(2)//firstprivate(a,b,c) reduction(+:temp) 
	for (k=0; k<TSIZE; k++) {
		#pragma omp parallel for default(none) shared(a,b,c) private(j,temp) firstprivate(k)
   		for (i=0; i<TSIZE; i++) {
   			temp = a[i][k];
   			for (j=0; j<TSIZE; j++) {
   					//#pragma omp atomic //Change atomic to locks
   					c[i][j]+=temp*b[k][j];
			}
			//c[i][j] = temp;
		}
	}
}

void Func2(int d[][MSIZE], int c[][MSIZE])
{
	int i,j, k, l;
	int blockSize = (MSIZE > 16) ? 16: MSIZE;	
	//omp_set_num_threads(NUM_THREADS);
	
	#pragma omp parallel for default(none) private(j,k,l) firstprivate(d,c,blockSize) collapse(2)
	for(i=0; i<MSIZE; i+= blockSize) 
		for(j=0; j<MSIZE; j+= blockSize)
			//d[i][j] = c[j][i];
			{
				//#pragma omp parallel for //default (none) shared(d,c) collapse(2) schedule(static)
				for(k = i; k< i+blockSize && k < MSIZE; k++)
					for(l = j; l< j+blockSize && l < MSIZE; l++)
						d[k][l]=c[l][k];
			}
}

void Func3(int z[][MSIZE], int d[][MSIZE])
{
	int y, x;
	int near = 2;  		// The weight of neighbor
	int itself = 84; 	// The weight of center
	//omp_set_num_threads(NUM_THREADS);

	z[0][0] = (near * (d[0][0] +
						d[0][1] +
						d[1][0] +
						d[1][1] +
						d[0][0] +
						d[0][1] +
						d[0][0] +
						d[1][0]) +
						itself* d[0][0] ) / 100;
	z[0][MSIZE-1] = (near * (d[0][MSIZE-2] +
						d[0][MSIZE-1] +
						d[1][MSIZE-2] +
						d[1][MSIZE-1] +
						d[0][MSIZE-2] +
						d[0][MSIZE-1] +
						d[0][MSIZE-1] +
						d[1][MSIZE-1]) +
						itself * d[0][MSIZE-1] ) / 100;
	z[MSIZE-1][0] = (near * (d[MSIZE-2][0] +
						d[MSIZE-2][1] +
						d[MSIZE-2][0] +
						d[MSIZE-1][0] +
						d[MSIZE-1][1] +
						d[MSIZE-1][0] +
						d[MSIZE-1][1] +
						d[MSIZE-1][0]) +
						itself * d[MSIZE-1][0] ) / 100;
	z[MSIZE-1][MSIZE-1] = (near * (d[MSIZE-2][MSIZE-2] +
						d[MSIZE-2][MSIZE-1] +
						d[MSIZE-1][MSIZE-2] +
						d[MSIZE-1][MSIZE-1] +
						d[MSIZE-1][MSIZE-2] +
						d[MSIZE-1][MSIZE-1] +
						d[MSIZE-2][MSIZE-1] +
						d[MSIZE-1][MSIZE-1]) +
						itself * d[MSIZE-1][MSIZE-1]) / 100;

	#pragma omp parallel for default(none) shared(z) firstprivate(near, itself,d)
	for(y = 1; y< MSIZE - 1; y++)
	{
		// set x = 0 and x = MSIZE-1
		z[y][0] = (near * (d[y-1][0] +
						d[y-1][1] +
						d[y+1][0] +
						d[y+1][1] +
						d[y][0] +
						d[y][1] +
						d[y-1][0] +
						d[y+1][0]) +
						itself * d[y][0]) / 100;

		z[y][MSIZE-1] = (near * (d[y-1][MSIZE-2] +
						d[y-1][MSIZE-1] +
						d[y+1][MSIZE-2] +
						d[y+1][MSIZE-1] +
						d[y][MSIZE-2] +
						d[y][MSIZE-1] +
						d[y-1][MSIZE-1] +
						d[y+1][MSIZE-1]) +
						itself * d[y][MSIZE-1])/100;
	}	
	#pragma omp nowait

	#pragma omp parallel for default(none) shared(z) firstprivate(itself, near,d)
	for(x = 1; x< MSIZE-1; x++)
	{
		z[0][x] = (near * (d[0][x-1] +
						d[0][x+1] +
						d[1][x-1] +
						d[1][x+1] +
						d[0][x-1] +
						d[0][x+1] +
						d[0][x] +
						d[1][x]) +
						itself * d[0][x] )/100;

		z[MSIZE-1][x] = (near * (d[MSIZE-2][x-1] +
						d[MSIZE-2][x+1] +
						d[MSIZE-1][x-1] +
						d[MSIZE-1][x+1] +
						d[MSIZE-1][x-1] +
						d[MSIZE-1][x+1] +
						d[MSIZE-2][x] +
						d[MSIZE-1][x]) +
						itself * d[MSIZE-1][x])/100;
	}	
	#pragma omp nowait

	#pragma omp parallel for shared(z) collapse (2)
	for (y=1; y<MSIZE-1; y++) {
		for (x=1; x<MSIZE-1; x++) {
					z[y][x] = 	near * (d[y-1][x-1] +
						d[y-1][x+1] +
						d[y+1][x-1] +
						d[y+1][x+1] +
						d[y][x-1] +
						d[y][x+1] +
						d[y-1][x] +
						d[y+1][x]) +
						itself * d[y][x];
			z[y][x]/=100;
		}
	}

	


}
						
void Func4(int b[], int a[])
{
	int chuck_size=MSIZE;	 
	int array_size=VSIZE/chuck_size;
	int chuck[chuck_size];
    int i, j, k;
	int prod = 0;
	int temp;
	//int blockSize = (array_size > 16)? 16: array_size;
	//int accum;
	//#pragma omp parallel
	
		//omp_set_num_threads(NUM_THREADS);
	//#pragma omp parallel for default(none) firstprivate(a,b,chuck,array_size,chuck_size, blockSize) private(prod,i,k)
	#pragma omp parallel for default(none) private(i,prod) firstprivate(chuck_size, array_size) shared(a,b,chuck)
	for(j=0; j<chuck_size; j++) {
		prod = j* array_size;
		b[prod]=a[prod];
		for (i=1; i<array_size; i++) {
			b[prod+i]=b[prod+i-1]+a[prod+i];
		}
		chuck[j]=b[prod + array_size -1];
	}
	
	
	//#pragma omp parallel for schedule(static)
	//#pragma omp parallel for default(none) firstprivate(chuck, chuck_size) reduction(+:temp)
	#pragma omp parallel for default(none) firstprivate(chuck_size) private(temp) shared(chuck)
	for(j=1; j<chuck_size; j+= 6) {
		temp = chuck[j] + chuck[j-1];//+chuck[j];
		chuck[j] = temp;
		temp+= chuck[j+1];
		chuck[j+1] = temp;
		temp+= chuck[j+2];
		chuck[j+2] = temp;
		temp+= chuck[j+3];
		chuck[j+3] = temp;
		temp+= chuck[j+4];
		chuck[j+4] = temp;
		temp+= chuck[j+5];
		chuck[j+5] = temp;
	}

	//int num;
	#pragma omp parallel for default(none) firstprivate(chuck_size, array_size) private(i, prod) shared(b, chuck) 
	for(j=1; j<chuck_size; j++){
			prod = j*array_size;
			int num = chuck[j-1]/(j+1);
			for (i=0; i<array_size; i++) {
				b[prod+i] += num;
			}
		}
	//}
	
	
	
}

void Func5(int b[], int a[])
{
	int i=0, j,  stride, stride2, step;
    int temp;
	long log_N=log2(VSIZE);
	int pow1;
	int pow2;
	#pragma omp parallel for default(none) shared(a,b) schedule(static)
	for(j=0; j<VSIZE; j+=2) {
		int temp1 = a[j];
		int temp2 = a[j+1];
		b[j]=temp1;
		b[j+1] = temp1 + temp2;
		// CHECK IF LOOP UNROLLING HELPS
		/*temp1 = a[j+2];
		temp2 = a[j+3];
		b[j+2] = temp1;
		b[j+3] = temp1 + temp2;*/
	}
	
	//#pragma omp parallel for default(none) private(j) shared(b)
	for(i=4; i<VSIZE; i*= 2) {
		#pragma omp parallel for default(none) shared(b) firstprivate(i)
		for(j=0; j<VSIZE; j+=i) {
				b[j+i-1] = b[j+i/2-1] + b[j+i-1];
		}
	}
	
	b[VSIZE-1]=0;
 
	//#pragma omp parallel for default(none) firstprivate(stride2, stride, step, pow1, pow2, j, temp, log_N) shared(b)
 	for(i=(log_N-1); i>=0; i--) {
		stride2=(2<<i)-1;
		stride=(1<<i)-1;
		step=stride2+1;
		pow1 = (int)pow(2, i);
		pow2 = pow1 * 2;
		#pragma omp parallel for default(none) private(temp) shared(b) firstprivate(pow1, pow2)
		for(j=0; j<VSIZE; j+= pow2) {
            temp=b[j+pow1-1];
			b[j+pow1-1] = b[j+pow2-1];
			b[j+pow2-1] = temp+b[j+pow2-1];
		}
	}
}
