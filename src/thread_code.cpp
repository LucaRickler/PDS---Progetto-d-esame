/*
 * thread_code.cpp
 *
 *  Created on: 20/lug/2016
 *      Author: luca
 */

#include "thread_code.h"

namespace Project {
namespace System {

void* ThreadExec(void* arg) {
	Runtime* rtm = (Runtime*) arg;
	printf("thread started\n");
	function<void()>* task;
	//bool iAmRunning = true;

	pthread_mutex_lock(&rtm->run_cond_lock);
	while (rtm->run_cond) {
		printf("thread running\n");
		pthread_mutex_unlock(&rtm->run_cond_lock);

		pthread_barrier_wait(&rtm->turn_begin_barrier);

		while (rtm->task_queue->Pop(task)) {
			if (task) {
				(*task)();
				task = NULL;
			}
		}

		pthread_mutex_lock(&rtm->active_threads_lock);
		rtm->active_threads--;
		printf("active threads: %d\n", rtm->active_threads);
		if (rtm->active_threads == 0) {

			pthread_mutex_lock(&rtm->main_t_sleep_lock);
			pthread_cond_signal(&rtm->main_t_sleep);
			pthread_mutex_unlock(&rtm->main_t_sleep_lock);

		}
		pthread_mutex_unlock(&rtm->active_threads_lock);

		pthread_barrier_wait(&rtm->exec_sleep_barrier);

		pthread_mutex_lock(&rtm->run_cond_lock);
		while (rtm->task_queue->isEmpty() && rtm->run_cond) {
			pthread_mutex_unlock(&rtm->run_cond_lock);

			//printf("queue empty\n");
			/*if(iAmRunning){
			 printf("Stopping\n");
			 iAmRunning = false;

			 pthread_mutex_lock(&rtm->active_threads_lock);
			 rtm->active_threads--;
			 if(rtm->active_threads == 0) {

			 pthread_mutex_lock(&rtm->main_t_sleep_lock);
			 pthread_cond_signal(&rtm->main_t_sleep);
			 pthread_mutex_unlock(&rtm->main_t_sleep_lock);

			 }
			 pthread_mutex_unlock(&rtm->active_threads_lock);
			 }*/

			pthread_mutex_lock(&rtm->empty_task_lock);
			printf("Sleeping\n");
			pthread_cond_wait(&rtm->empty_task, &rtm->empty_task_lock);
			printf("Awakening\n");
			pthread_mutex_unlock(&rtm->empty_task_lock);

			pthread_mutex_lock(&rtm->run_cond_lock);
		}
		pthread_mutex_unlock(&rtm->run_cond_lock);
		//iAmRunning = true;

		pthread_mutex_lock(&rtm->run_cond_lock);
	}
	pthread_mutex_unlock(&rtm->run_cond_lock);

	return NULL;
}

}
}

