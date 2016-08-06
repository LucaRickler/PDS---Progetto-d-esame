/*
 * Runtime.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#include "Runtime.h"

namespace Project {
namespace System {

Runtime::Runtime(const int & e_depth) {
	execution_depth = e_depth;
	threads = vector<pthread_t>();
	task_queue = new FIFOQueue<std::function<void()>*>*[execution_depth+1]();
	for(int i = 0; i <= execution_depth; i++)
		task_queue[i] = new FIFOQueue<std::function<void()>*>();
	agents = vector<Agent::Agent*>();

	sub_turn = 0;
	pthread_mutex_init(&sub_turn_lock, NULL);

	run_cond = true;
	pthread_mutex_init(&run_cond_lock, NULL);

}

Runtime::~Runtime() {
	function<void()>* func;
	for(int i = 0; i <= execution_depth; i++) {
		while (task_queue[i]->Pop(func)) {
			delete func;
		}
		delete task_queue[i];
	}
	delete task_queue;
		std::for_each(agents.begin(), agents.end(),
			[](Agent::Agent* a) {delete a;});
}

void Runtime::DeleteAgent(Agent::Agent* a) {
	agents.erase(std::remove(agents.begin(), agents.end(), a), agents.end());
	delete a;
}

void Runtime::SetMaxTurns(const int & mt) {
	if (mt > 0) {
		max_turns = mt;
	}
}

const int Runtime::GetExecutionDepth() {
	return execution_depth;
}

//Standard parallel mode
#if EXECUTION_MODE==1

void Runtime::Init(int argc, char** argv) {
	std::for_each(agents.begin(), agents.end(), [this](Agent::Agent* a) {
		function<void()>* func = new function<void()>([a]() {a->Setup();});
		task_queue[a->GetPriority()]->Push(func);
	});

	SetUpTrheads(argc);

	MainCycle();
}

void Runtime::SetUpTrheads(int n) {
	pthread_barrier_init(&exec_sleep_barrier, NULL, n+1);
	pthread_barrier_init(&exec_awake_barrier, NULL, n+1);
	pthread_t thread;
	for (int i = 0; i < n; i++) {
		pthread_create(&thread, NULL, &ThreadExec, (void*) this);
		threads.push_back(thread);
	}
}

void Runtime::MainCycle() {
	for (int turn = 1; turn <= max_turns; turn++) {
		std::cout << "Turn #" << turn << "\n";
		for(int j = 0; j < execution_depth; j++){
			//std::cout << "sub_t : " << sub_turn << "\n";
			pthread_barrier_wait(&exec_sleep_barrier);
			//printf("Sleep\n");

			pthread_mutex_lock(&sub_turn_lock);
			sub_turn++;
			sub_turn = sub_turn%(execution_depth + 1);
			pthread_mutex_unlock(&sub_turn_lock);

			if (turn < max_turns || j < (execution_depth - 1)) {
				pthread_barrier_wait(&exec_awake_barrier);
				//printf("Start\n");
			}
		}
	}

	pthread_mutex_lock(&run_cond_lock);
	printf("Closing program\n");
	run_cond = false;
	pthread_mutex_unlock(&run_cond_lock);

	pthread_barrier_wait(&exec_awake_barrier);

	std::for_each(threads.begin(), threads.end(),
			[](pthread_t t) {pthread_join(t,NULL);});
}

//Sequential mode
#elif EXECUTION_MODE==0

void Runtime::Init(int argc, char** argv) {
	std::for_each(agents.begin(), agents.end(), [this](Agent::Agent* a) {
		function<void()>* func = new function<void()>([a]() {a->Setup();});
		task_queue[a->GetPriority()]->Push(func);
	});

	MainCycle();
}

void Runtime::MainCycle() {
	function<void()>* func;
	for (int turn = 1; turn <= max_turns; turn++) {
		std::cout << "Turn #" << turn << "\n";
		for(int j = 0; j < execution_depth; j++){
			std::cout  << "sub_t : " << sub_turn << "\n";
			while(task_queue[sub_turn]->Pop(func)){
				(*func)();
			}

			sub_turn++;
			sub_turn = sub_turn%(execution_depth + 1);//(sub_turn < execution_depth ? sub_turn++ : 0);
		}
	}
	printf("Closing program\n");
}

//Agent-dedicated threads parallel mode
#elif EXECUTION_MODE==2

void Runtime::Init(int argc, char** argv) {
	std::for_each(agents.begin(), agents.end(), [this](Agent::Agent* a) {
		function<void()>* func = new function<void()>([a]() {a->Setup();});
		task_queue[a->GetPriority()]->Push(func);
	});

	SetUpTrheads(argc);

	MainCycle();
}

void Runtime::SetUpTrheads(int n) {
	pthread_barrier_init(&exec_sleep_barrier, NULL, n+1);
	pthread_barrier_init(&exec_awake_barrier, NULL, n+1);
	pthread_t thread;
	for (int i = 0; i < n; i++) {
		pthread_create(&thread, NULL, &ThreadExec, (void*) this);
		threads.push_back(thread);
	}
}

void Runtime::MainCycle() {
	for (int turn = 1; turn <= max_turns; turn++) {
		std::cout << "Turn #" << turn << "\n";
		for(int j = 0; j < execution_depth; j++){
			pthread_barrier_wait(&exec_sleep_barrier);

			pthread_mutex_lock(&sub_turn_lock);
			sub_turn = (++sub_turn)%(execution_depth+ 1);
			pthread_mutex_unlock(&sub_turn_lock);

			if (turn < max_turns) {
				pthread_barrier_wait(&exec_awake_barrier);
			}
		}
	}

	pthread_mutex_lock(&run_cond_lock);
	printf("Closing program\n");
	run_cond = false;
	pthread_mutex_unlock(&run_cond_lock);

	pthread_barrier_wait(&exec_awake_barrier);

	std::for_each(threads.begin(), threads.end(),
			[](pthread_t t) {pthread_join(t,NULL);});
}

#endif

void Runtime::ScheduleAction(Agent::Action* act, const int &p) {
	pthread_mutex_lock(&sub_turn_lock);
	int s = (sub_turn + execution_depth)%(execution_depth + 1);
	task_queue[s]->Push(act->actionReference);
	//printf("action scheduled at %d\n", s);
	pthread_mutex_unlock(&sub_turn_lock);
}

void Runtime::DispatchMessage (Comms::Message* msg) {
	std::for_each(agents.begin(), agents.end(),
			[msg](Agent::Agent* a){a->DeliverMessage(msg);});
}

} /* namespace System */
} /* namespace AgentC */
