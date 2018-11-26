#include <omp.h> 
#include <stdlib.h> 
#include <stdio.h> 


int main(int argc,char * argv[]) {
	int nthread,tid;

	printf("running for all threads\n");
	#pragma omp parallel 
	{
		tid=omp_get_thread_num();
		printf("thread %d\n",tid);
	}

	printf("running for only 5 threads\n");
	#pragma omp parallel num_threads(5)
	{
		tid=omp_get_thread_num();
		printf("thread %d\n",tid);
	}
	return 0;
}
