#include <stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

#define time 1
#define false 0

int cnt=0;
pthread_mutex_t mutex;

int cntPrime(int num){
	int cnt=0;
	int i;
	if(num<2) return false;
	
	for(i=1;i*i<num;i++){
		if(num%i==0) cnt++;
	}
	if(i*i==num) cnt++;
	if(cnt==1) return true;
	else return false;
}

void *partial_prime(void* param){
	pthread_mutex_lock(&mutex);
	int range = *(int *)param;
	printf("thread for range (%d ~ %d)\n", range, range+99999);
	
	for (int i=range; i<=range+99999; i++) {
		if (cntPrime(i) == true) cnt++;
	}//count prime numbers within the range
	pthread_mutex_unlock(&mutex);
	
	pthread_exit(0);
}

int main(int argc, char* argv[]){
	int range=atoi(argv[1]);
	
	struct timespec start, finish;
	double elapsed;
	
	clock_gettime(CLOCK_MONOTONIC, &start);//get time
	
	pthread_mutex_init(&mutex, NULL);//initialize mutex lock
	
	int num_thread=0;
	pthread_t tids[1024];
	int limit[1024];
	
	int idx=0;
	while(idx<range){
		limit[num_thread]=idx;
		
		int res=pthread_create(&tids[num_thread], NULL, &partial_prime, (void *)&limit[num_thread]);//create thread
		
		num_thread++;
		idx+=100000;
		if(idx+1>range) idx=range;
	}
	
	for(int k=0;k<num_thread;k++){
		int res1=pthread_join(tids[k], NULL);//wait
	}
	
	clock_gettime(CLOCK_MONOTONIC, &finish);
    	elapsed = (finish.tv_sec - start.tv_sec);
    	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;//measure time
    	
    	printf("elapsed time: %f sec \n", elapsed);
    	printf("The number of prime numbers between 1~%d is %d\n", range, cnt);
    	
    	return 0;
}
    	
	
	
