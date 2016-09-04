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
	function<void()>* task;
	int sub_t;

	pthread_mutex_lock(&rtm->run_cond_lock);
	while (rtm->run_cond) {
		pthread_mutex_unlock(&rtm->run_cond_lock);

		pthread_mutex_lock(&rtm->sub_turn_lock);
		sub_t = rtm->sub_turn;
		pthread_mutex_unlock(&rtm->sub_turn_lock);

		while (rtm->task_queue[sub_t]->Pop(task)) {
			if (task) {
				(*task)();
				task = NULL;
			}
		}

		pthread_barrier_wait(&rtm->exec_sleep_barrier);

		pthread_barrier_wait(&rtm->exec_awake_barrier);

		pthread_mutex_lock(&rtm->run_cond_lock);
	}
	pthread_mutex_unlock(&rtm->run_cond_lock);

	return NULL;
}


}
}

