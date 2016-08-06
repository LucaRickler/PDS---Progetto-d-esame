/*
 * FIFOQueue_test.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: Luca Rickler
 */

#include "../FIFOQueue.cpp"
#include <pthread.h>
#include <iostream>
#include <unistd.h>

using Project::System::FIFOQueue;

void *producer(void *);
void *consumer(void *);

int main() {
	pthread_t thread1, thread2;
	FIFOQueue<int*> *q1= new FIFOQueue<int*>();


	pthread_create(&thread1, NULL, (void* (*)(void*)) &producer, (void *) q1);
	pthread_create(&thread2, NULL, (void* (*)(void*)) &consumer, (void *) q1);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return 0;
}

void *producer(void * arg) {
	FIFOQueue<int*>* q = (FIFOQueue<int*>*) arg;
	int *count;
	while (true) {
		sleep(10);
		for(int i = 0; i<10; i++){
			count = new int(i);
			q->Push(count);
		}
	}
}

void *consumer(void * arg) {
	FIFOQueue<int*>* q = (FIFOQueue<int*>*) arg;
	while (true) {
		sleep(1);
		int* value;
		if (q->Pop(value)) {
			std::cout << *value << "\n";
			delete value;
		} else {
			std::cout << "empty\n";
		}
	}
}

