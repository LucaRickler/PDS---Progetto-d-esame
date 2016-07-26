/*
 * Runtime.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_RUNTIME_H_
#define SRC_RUNTIME_H_

//#include "Agent.h"
//#include "FIFOQueue.h"
#include "project.h"
#include "thread_code.h"
#include "Agent.h"

namespace Project {
	namespace System {

		class Runtime {
		public:
			Runtime();
			virtual ~Runtime();

			void Init(int argc, char** argv);
			//void Init();
			template <typename T> void friend CreateAgent(Runtime* runtime, string name);


		private:
			vector<pthread_t> threads;
			int active_threads;
			pthread_mutex_t active_threads_lock;
			pthread_cond_t empty_task;
			pthread_mutex_t empty_task_lock;
			bool run_cond;
			pthread_mutex_t run_cond_lock;

			Project::System::FIFOQueue<std::function<void()>*>* task_queue;
			Project::System::FIFOQueue<std::function<void()>*>* next_turn_task_queue;
			void SetUpTrheads(int n);

			vector<Agent::Agent*> agents;

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

//#include "Runtime.cpp"

#endif /* SRC_RUNTIME_H_ */
