#include<stdio.h>
#include<omp.h>
static long num_steps = 100000;
double step;
int main()
{
	// Time calculation
	double t1,t2,t;
	t1 = omp_get_wtime();

	// Splitting program to different threads
	int tot_threads = omp_get_num_threads();
	long new_steps = num_steps/tot_threads; // assuming even threads always, preferably 4

	double pi; 
	double sum[tot_threads];
	
	step = 1.0/(double)num_steps;

	#pragma omp parallel
	{
	double x;
	int i,rank = omp_get_thread_num();
	//sum[rank] = 0.0;
	double temp=0.0;
	for(i=0;i<new_steps;i++){
		x = ((i+rank*new_steps)+0.5)*step;
	//	sum[rank] = sum[rank] + 4.0/(1.0+x*x);
		temp = temp + 4.0/(1.0+x*x);
	}
	sum[rank] = temp;
	}
	double tot_sum = 0.0;
	int i;
	for(i=0;i<tot_threads;i++){
		tot_sum = tot_sum + sum[i];
	}
	pi = step*tot_sum;
	t2 = omp_get_wtime();
	t = t2-t1;
	printf("Pi is %f, calculated in %f seconds \n",pi,t);
}
