/*
 * Runtime.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#include "Runtime.h"
//#include <pthread.h>

namespace Project {
namespace System {

Runtime::Runtime() {
	threads = vector<pthread_t>();
	task_queue = new FIFOQueue<std::function<void()>*>();
	next_turn_task_queue = new FIFOQueue<std::function<void()>*>();
	run_cond = true;
	pthread_cond_init(&empty_task, NULL);
	pthread_mutex_init(&run_cond_lock, NULL);
	pthread_mutex_init(&active_threads_lock, NULL);
	pthread_mutex_init(&empty_task_lock, NULL);

	agents = vector<Agent::Agent*>();
	active_threads = 0;
}

Runtime::~Runtime() {
	// TODO Auto-generated destructor stub
}

void Runtime::Init(int argc, char** argv) {

}

void Runtime::SetUpTrheads(int n) {
	pthread_t thread;
	pthread_attr_t detached;
	pthread_attr_init(&detached);
	pthread_attr_setdetachstate(&detached, PTHREAD_CREATE_DETACHED);
	ThreadPackage* tp = new ThreadPackage;
	tp->runtime = this;
	tp->task_queue = this->task_queue;
	tp->empty_task = &(this->empty_task);
	tp->empty_task_lock = &(this->empty_task_lock);
	tp->run_cond = &(this->run_cond);
	tp->run_cond_lock = &(this->run_cond_lock);
	tp->active_threads = &(this->active_threads);
	tp->active_threads_lock = &(this->active_threads_lock);
	for(int i = 1; i < n; i++) {
		pthread_create(&thread, &detached, &ThreadExec, (void*)&tp);
		threads.push_back(thread);
		active_threads++;
	}
}

/*void Runtime::Init() {

}*/

/*template<typename T>
Agent::Agent* InstantiateAgent (Runtime* runtime, string name){
	return new Agent::Agent(runtime, name);
}

template<typename T>
void CreateAgent (Runtime* runtime, string name){
	Agent::Agent* agent = InstantiateAgent<T>(runtime, name);
	runtime->agents.push_back(agent);
}*/

} /* namespace System */
} /* namespace AgentC */
