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
	pthread_t thread1, thread2, thread3;
	FIFOQueue<int> * q = new FIFOQueue<int>();

	pthread_create(&thread1, NULL, (void* (*)(void*)) &producer, (void *) q);
	pthread_create(&thread2, NULL, (void* (*)(void*)) &consumer, (void *) q);
	pthread_create(&thread3, NULL, (void* (*)(void*)) &producer, (void *) q);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	return 0;
}

void *producer(void * arg) {
	FIFOQueue<int> * q = (FIFOQueue<int> *) arg;
	int count = 0;
	for (;;) {
		sleep(10);
		q->Push(count++);
	}
}

void *consumer(void * arg) {
	FIFOQueue<int> * q = (FIFOQueue<int> *) arg;
	for (;;) {
		sleep(1);
		int value;
		if (q->Pop(value)) {
			std::cout << value << "\n";
		} else {
			std::cout << "empty\n";
		}
	}
}

