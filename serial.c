#include<stdio.h>
#include<omp.h>
static long num_steps = 10000000;
double step;
int main()
{
	double t1,t2,t;
	t1 = omp_get_wtime();

	int i; double x,pi,sum = 0.0;

	step = 1.0/(double)num_steps;

	for(i=0;i<num_steps;i++){
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}
	pi = step*sum;
	t2 = omp_get_wtime();
	t = t2-t1;
	printf("Pi is %f, calculated in %f seconds \n",pi,t);
}
