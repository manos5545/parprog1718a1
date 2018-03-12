
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// compile like:  gcc -Wall -O2 -DNROWS=10000 matrix1.c -o matrix1


#define NCOLS 100
#define NROWS 100000

void get_walltime(double *wct) {
  struct timeval tp;
  gettimeofday(&tp,NULL);
  *wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}


int main() {
double *table;
double ts,te;


  table = (double *)malloc(NROWS*NCOLS*sizeof(double)); 
  if (table==NULL) {
    printf("alloc error!\n");
    exit(1);
  }

  
  	int i,j =0;
  	
	for (i=0; i<NROWS*NCOLS; i++) {
		table[i] = 1.0;
	}//We assign 1.0 beacuse we have double values and value of 1 to check accesses
	double sum = 0.0;
	
	
  // get starting time (double, seconds) 
  get_walltime(&ts);
  
  // workload
	for (i=0; i<NCOLS; i++) {
		for (j=0; j<NROWS; j++) {
			sum += table[i*NROWS+j];
		}
	}

  // get ending time
  get_walltime(&te);

  double time_elapsed = te - ts;

  printf ("Time elapsed is: %fsec\n", time_elapsed);
  

  // check results
  printf("sum = %f\n", sum);
  
  double m_acc = ((double)NROWS*NCOLS)/((te-ts)*1e6);
  
  printf("average array element Maccesses/sec = %f\n", m_acc);
  
  
  free(table);

  return 0;
}
