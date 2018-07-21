#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* threadFunc1(void *arg) {
	printf("thread 1 returning\n");
	sleep(3);
	return ((void*)1);
}

void* threadFunc2(void *arg) {
	printf("thread 2 exiting\n");
	pthread_exit((void*)2);
}

int main() 
{
	int err;
	pthread_t tid1, tid2;
	void *tret;
	
	err = pthread_create(&tid1, NULL, threadFunc1, NULL);
	if(err != 0) {
		fprintf(stderr, "can not create thread 1");
		return -1;
	}
	err = pthread_create(&tid2, NULL, threadFunc2, NULL);
	if(err != 0) {
		fprintf(stderr, "can not create thread 2");
		return -1;
	}
	err = pthread_join(tid1, &tret);
	if(err != 0) {
		fprintf(stderr, "can not join with thread 1");
		return -1;
	}
	printf("thread 1 exit code %ld\n", (long)tret);
	err = pthread_join(tid2, &tret);
	if(err != 0) {
		fprintf(stderr, "can not join with thread 2");
		return -1;
	}
	printf("thread 2 exit code %ld\n", (long)tret);
	exit(0);
}