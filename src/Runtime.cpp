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
	std::for_each(agents.begin(), agents.end(), [this](Agent::Agent* a){
		function<void()>* func = new function<void()>([a](){a->Setup();});
		task_queue->Push(func);
	});

	SetUpTrheads(argc);
	/*function<void()>* func;
	while(task_queue->Pop(func)){
		(*func)();
	}*/



	pthread_mutex_lock(&run_cond_lock);
	run_cond = false;
	pthread_mutex_unlock(&run_cond_lock);

	std::for_each(threads.begin(), threads.end(), [](pthread_t t){pthread_join(t,NULL);});
}

void Runtime::SetUpTrheads(int n) {
	pthread_t thread;
	//pthread_attr_t detached;
	//pthread_attr_init(&detached);
	for(int i = 0; i < n; i++) {
		pthread_create(&thread, NULL, &ThreadExec, (void*)this);
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
