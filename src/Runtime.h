/*
 * Runtime.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_RUNTIME_H_
#define SRC_RUNTIME_H_

#include "project.h"
#include "Agent.h"
#include "Action.h"

namespace Project {
	namespace System {

		class Runtime {
		public:
			Runtime();
			virtual ~Runtime();

			void Init(int argc, char** argv);
			//void Init();
			template <typename T> void friend CreateAgent(Runtime* runtime, string name);
			friend void* ThreadExec (void* arg);
			void DeleteAgent(Agent::Agent* agt);
			void ScheduleAction(Agent::Action* act);
			void SetMaxTurns (const int &);

		private:
			vector<pthread_t> threads;

			int active_threads;
			pthread_mutex_t active_threads_lock;

			pthread_cond_t empty_task;
			pthread_mutex_t empty_task_lock;

			bool run_cond;
			pthread_mutex_t run_cond_lock;

			pthread_cond_t main_t_sleep;
			pthread_mutex_t main_t_sleep_lock;

			pthread_barrier_t turn_begin_barrier;
			pthread_barrier_t exec_sleep_barrier;

			Project::System::FIFOQueue<std::function<void()>*>* task_queue;
			Project::System::FIFOQueue<std::function<void()>*>* next_turn_task_queue;
			vector<Agent::Agent*> agents;

			void SetUpTrheads(int n);
			void MainCycle ();

			int max_turns;
			//int turn;
		};
		template <typename T>
		Agent::Agent* InstantiateAgent(Runtime* runtime, string name) {
			return new T(runtime, name);
		}

		template <typename T>
		void CreateAgent(Runtime* runtime, string name) {
			Agent::Agent* agent = InstantiateAgent<T>(runtime, name);
			runtime->agents.push_back(agent);
		}

	} /* namespace System */
} /* namespace AgentC */

#include "thread_code.h"
//#include "Runtime.cpp"

#endif /* SRC_RUNTIME_H_ */
