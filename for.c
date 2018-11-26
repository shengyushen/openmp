#include <omp.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <time.h> 
#include <assert.h> 

#define SIZE 64*2048*2048*2
#define min(a,b) ((a)<(b))?(a):(b)

int main(int argc,char * argv[]) {
	printf("SIZE %d\n",SIZE);
	int * a=malloc(SIZE*sizeof(int));
	int * b=malloc(SIZE*sizeof(int));
	for(int i=0;i<SIZE;i=i+1) {
		a[i]=i;
		b[i]=i;
	}

	double start;
	start=omp_get_wtime();
	int * c=malloc(SIZE*sizeof(int));
	for(long i=0;i<SIZE;i++) {
		c[i]=a[i]+b[i];
	}
	double difftime;
	difftime=omp_get_wtime()-start;
	printf("serial run takes %f seconds\n",difftime);

	start=omp_get_wtime();
	#pragma omp parallel
	{
		int nthread = omp_get_num_threads();
		int tid = omp_get_thread_num();
		int nsz= SIZE/nthread+1;
		int nstart = nsz*tid;
		int nend = min(nsz*(tid+1),SIZE);
		printf("tid %d start %d end %d\n",tid,nstart,nend);
		for(long i = nstart;i<nend;i++) {
			c[i]=a[i]+b[i];
		}
	}
	difftime=omp_get_wtime()-start;
	printf("parallel run takes %f seconds\n",difftime);

	int * c1=malloc(SIZE*sizeof(int));
	#pragma omp parallel
	{
		#pragma omp for
			for(long i=0;i<SIZE;i++) {
				c1[i]=a[i]+b[i];
			}
	}
	for(long i=0;i<SIZE;i++) {
		assert(c[i]==c1[i]);
	}

	int * c2=malloc(SIZE*sizeof(int));
	#pragma omp parallel for
			for(long i=0;i<SIZE;i++) {
				c2[i]=a[i]+b[i];
			}

	for(long i=0;i<SIZE;i++) {
		assert(c[i]==c2[i]);
	}
	return 0;
}
