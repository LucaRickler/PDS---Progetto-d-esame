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

struct qss {
	FIFOQueue<int*>* q1;
	FIFOQueue<int*>* q2;
};

int main() {
	pthread_t thread1, thread2;//, thread3;
	qss* qs = new qss;
	qs->q1 = new FIFOQueue<int*>();
	qs->q2 = new FIFOQueue<int*>();


	pthread_create(&thread1, NULL, (void* (*)(void*)) &producer, (void *) qs);
	pthread_create(&thread2, NULL, (void* (*)(void*)) &consumer, (void *) qs);
	//pthread_create(&thread3, NULL, (void* (*)(void*)) &producer, (void *) qs);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	//pthread_join(thread3, NULL);
	return 0;
}

void *producer(void * arg) {
	qss* qs = (qss*) arg;
	int *count;
	bool flag = true;
	while (true) {
		sleep(10);
		for(int i = 0; i<10; i++){
			count = new int(i);
			qs->q2->Push(count);
		}
		if(flag){
			qs->q1->Join(qs->q2);
			flag = false;
		}
	}
}

void *consumer(void * arg) {
	qss* qs = (qss*) arg;
	while (true) {
		sleep(1);
		int* value;
		if (qs->q2->Pop(value)) {
			std::cout << *value << "\n";
			delete value;
		} else {
			std::cout << "empty\n";
		}
	}
}

