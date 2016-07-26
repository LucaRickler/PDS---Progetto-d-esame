/*
 * thread_code.h
 *
 *  Created on: 21/lug/2016
 *      Author: luca
 */

#ifndef SRC_THREAD_CODE_H_
#define SRC_THREAD_CODE_H_

#include "project.h"

namespace Project {
	namespace System {

		struct ThreadPackage {
			Runtime* runtime;
			FIFOQueue<std::function<void()>*>* task_queue;
			int* active_threads;
			pthread_mutex_t* active_threads_lock;
			pthread_cond_t* empty_task;
			pthread_mutex_t* empty_task_lock;
			bool* run_cond;
			pthread_mutex_t* run_cond_lock;
		};

		void *ThreadExec (void* arg);

	}
}

#endif /* SRC_THREAD_CODE_H_ */
