#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0

int cntPrime(int num)
{
	int cnt = 0;
	int i;

	for (i=1; i*i<num; i++) {
		if (num%i == 0) cnt++;
	}
	if (i*i == num) cnt++;
	if (cnt == 1) return true;
	else return false;
}

int main(int argc, char* argv[])
{
	int cnt = 0;
	int range = atoi(argv[1]);

	struct timespec start, finish;
	double elapsed;	
	clock_gettime(CLOCK_MONOTONIC, &start);
	

	for (int i=2; i<range; i++) {

		if (cntPrime(i) == true) cnt++;
	}

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	printf("elapsed time: %f sec \n", elapsed);
	printf("The number of prime numbers between 1~%d is %d\n", range, cnt);

	return 0;

}
