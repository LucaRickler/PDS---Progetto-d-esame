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
	ThreadPackage* tp = (ThreadPackage*) arg;

	std::function<void()>* task = NULL;

	pthread_mutex_lock(tp->run_cond_lock);
	while (*(tp->run_cond)) {
		pthread_mutex_unlock(tp->run_cond_lock);
		while(tp->task_queue->Pop(task)){
			if(task){
				(*task)();
				task = NULL;
			}
		}

		pthread_mutex_lock(tp->empty_task_lock);
		while (tp->task_queue->isEmpty()){
			pthread_cond_wait(tp->empty_task, tp->empty_task_lock);
		}
		pthread_mutex_unlock(tp->empty_task_lock);

		pthread_mutex_lock(tp->run_cond_lock);
	}
	pthread_mutex_unlock(tp->run_cond_lock);

	return NULL;
}

}
}

