/*
 * thread_code.cpp
 *
 *  Created on: 20/lug/2016
 *      Author: luca
 */

#include "thread_code.h"

namespace Project {
namespace System {

void* ThreadExec (void* arg) {
	Runtime* rtm = (Runtime*) arg;
	printf("thread started\n");
	std::function<void()>* task;

	pthread_mutex_lock(&rtm->run_cond_lock);
	while (rtm->run_cond) {
		pthread_mutex_unlock(&rtm->run_cond_lock);
		while(rtm->task_queue->Pop(task)){
			if(task){
				(*task)();
				task = NULL;
			}
		}

		pthread_mutex_lock(&rtm->empty_task_lock);
		while (rtm->task_queue->isEmpty()){
			pthread_cond_wait(&rtm->empty_task, &rtm->empty_task_lock);
		}
		pthread_mutex_unlock(&rtm->empty_task_lock);

		pthread_mutex_lock(&rtm->run_cond_lock);
	}
	pthread_mutex_unlock(&rtm->run_cond_lock);

	return NULL;
}

}
}

