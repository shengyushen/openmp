#include<omp.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc,void* argv[]) {
	unsigned int i=0;
	#pragma omp parallel 
	{
		int nthread = omp_get_num_threads();
		int tid=omp_get_thread_num();
		if(tid==0) {
			printf("number of thread is %d\n",nthread);
		}
		#pragma omp critical
		{
			i++;
			printf("tid %d reach %d\n",tid,i);
		}
	}
}
