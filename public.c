#include <omp.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <assert.h> 
#include <time.h> 


int main(int argc,char * argv[]) {
	int nthread,tid;

	if(argc != 2) {
		printf("Usage : public.exe <thread num>\n");
		return 0;
	}

	int threadnum;
	sscanf(argv[1],"%d",&threadnum);
	printf("threadnum is %d\n",threadnum);

	time_t t_start, t_end;
  t_start = time(NULL) ;
	
	#pragma omp parallel num_threads(threadnum)
	{
		for(int i=0;i<1000*1000*100;i++) {}
	}
  t_end = time(NULL) ;
	double diff =  difftime(t_end,t_start);
  printf("time: %f s\n", diff) ;	
	return 0;
}
