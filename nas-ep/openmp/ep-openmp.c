#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main () {
	int nthreads, tid;
	#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		printf("Oi mundo, sou o thread %d\n", tid);
		if( tid == 0 ) {
			nthreads = omp_get_num_threads();
			printf("Total de threads: %d\n", nthreads);
		}
	}
}