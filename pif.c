#include<stdio.h>
#include<omp.h>
static long num_steps = 100000000;
double step;
# define NUM_THREADS 4
int main()
{
	// Time calculation
	double t1,t2,t;
	t1 = omp_get_wtime();

	// Splitting program to different threads
	//int tot_threads = omp_get_num_threads();
	omp_set_num_threads(NUM_THREADS);

	long new_steps = num_steps/NUM_THREADS; // assuming even threads always, preferably 4

	double pi; int num_threads_avail;
	double sum[NUM_THREADS];
	
	step = 1.0/(double)num_steps;

	#pragma omp parallel
	{
	double x;
	int i,rank = omp_get_thread_num();
	if(rank==0) num_threads_avail = omp_get_num_threads();
	//sum[rank] = 0.0;
	double temp=0.0;
	for(i=0;i<new_steps;i++){
		x = ((i+rank*new_steps)+0.5)*step;
	//	sum[rank] = sum[rank] + 4.0/(1.0+x*x);
		temp = temp + 4.0/(1.0+x*x);
	}
	#pragma omp critical
	sum[rank] = temp;
	}
	double tot_sum = 0.0;
	int i;
	for(i=0;i<num_threads_avail;i++){
		tot_sum = tot_sum + sum[i];
	}
	pi = step*tot_sum;
	t2 = omp_get_wtime();
	t = t2-t1;
	printf("Pi is %f, calculated in %f seconds with %d number of threads out of %d threads requested \n",pi,t,num_threads_avail,NUM_THREADS);
}
