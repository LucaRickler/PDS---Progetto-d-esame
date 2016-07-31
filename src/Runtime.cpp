/*
 * Runtime.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#include "Runtime.h"

namespace Project {
namespace System {

Runtime::Runtime() {
	threads = vector<pthread_t>();
	task_queue = new FIFOQueue<std::function<void()>*>();
	next_turn_task_queue = new FIFOQueue<std::function<void()>*>();
	agents = vector<Agent::Agent*>();

	run_cond = true;
	pthread_mutex_init(&run_cond_lock, NULL);

	active_threads = 0;
	pthread_mutex_init(&active_threads_lock, NULL);

	pthread_cond_init(&empty_task, NULL);
	pthread_mutex_init(&empty_task_lock, NULL);

	pthread_cond_init(&main_t_sleep, NULL);
	pthread_mutex_init(&main_t_sleep_lock, NULL);

	//turn = 0;

	//max_turns = 10;
}

Runtime::~Runtime() {
	function<void()>* func;
	while (task_queue->Pop(func)) {
		delete func;
	}
	delete task_queue;
	while (next_turn_task_queue->Pop(func)) {
		delete func;
	}
	delete next_turn_task_queue;
	std::for_each(agents.begin(), agents.end(), [](Agent::Agent* a){delete a;});
}

void Runtime::DeleteAgent (Agent::Agent* a) {
	agents.erase(std::remove(agents.begin(),agents.end(), a), agents.end());
	delete a;
}

void Runtime::SetMaxTurns(const int & mt) {
	if(mt > 0) {
		max_turns = mt;
	}
}

void Runtime::Init(int argc, char** argv) {
	std::for_each(agents.begin(), agents.end(), [this](Agent::Agent* a) {
		function<void()>* func = new function<void()>([a]() {a->Setup();});
		task_queue->Push(func);
	});

	SetUpTrheads(argc);

	MainCycle();
}

void Runtime::SetUpTrheads(int n) {
	pthread_barrier_init(&turn_begin_barrier, NULL, n);
	pthread_barrier_init(&exec_sleep_barrier, NULL, n);
	pthread_t thread;
	//pthread_attr_t detached;
	//pthread_attr_init(&detached);
	for (int i = 0; i < n; i++) {
		pthread_create(&thread, NULL, &ThreadExec, (void*) this);
		threads.push_back(thread);
		pthread_mutex_lock(&active_threads_lock);
		active_threads++;
		pthread_mutex_unlock(&active_threads_lock);
	}
}

void Runtime::MainCycle() {
	for (int turn = 0; turn < max_turns; turn++) {
		std::cout << "Run #" << turn << "\n";
		pthread_mutex_lock(&active_threads_lock);
		while (active_threads != 0) {
			pthread_mutex_unlock(&active_threads_lock);

			printf("Main T Sleeping\n");
			pthread_mutex_lock(&main_t_sleep_lock);
			pthread_cond_wait(&main_t_sleep, &main_t_sleep_lock);
			pthread_mutex_unlock(&main_t_sleep_lock);

			pthread_mutex_lock(&active_threads_lock);
		}
		pthread_mutex_unlock(&active_threads_lock);

		if (next_turn_task_queue->isEmpty()) {
			turn = max_turns;
		} else {
			task_queue->Join(next_turn_task_queue);
			next_turn_task_queue->Clear();
		}

		pthread_mutex_lock(&empty_task_lock);
		pthread_cond_broadcast(&empty_task);
		pthread_mutex_unlock(&empty_task_lock);

		pthread_mutex_lock(&active_threads_lock);
		active_threads = threads.size();
		pthread_mutex_unlock(&active_threads_lock);
	}

	pthread_mutex_lock(&run_cond_lock);
	printf("Closing program\n");
	run_cond = false;
	pthread_mutex_unlock(&run_cond_lock);

	pthread_mutex_lock(&empty_task_lock);
	printf("Awake exec\n");
	pthread_cond_broadcast(&empty_task);
	pthread_mutex_unlock(&empty_task_lock);

	std::for_each(threads.begin(), threads.end(),
			[](pthread_t t) {pthread_join(t,NULL);});
}

void Runtime::ScheduleAction(Agent::Action* act) {
	next_turn_task_queue->Push(act->actionReference);
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
