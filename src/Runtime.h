/*
 * Runtime.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_RUNTIME_H_
#define SRC_RUNTIME_H_

#include "Agent.h"
#include "Action.h"
#include "Message.h"
#include "dependencies.h"

namespace Project {
	namespace System {

		class Runtime {
		public:
			Runtime(const int &);
			virtual ~Runtime();

			void Init(int argc, char** argv);
			//void Init();
			template <typename T> void friend CreateAgent(Runtime* runtime, string name);
			friend void* ThreadExec (void* arg);
			void DeleteAgent(Agent::Agent* agt);
			void ScheduleAction(Agent::Action* act);
			void SetMaxTurns (const int &);
			const int GetExecutionDepth ();

			void DispatchMessage (Comms::Message* msg);
			void MarkAsRead (Comms::Message* msg);

		private:
			vector<pthread_t> threads;

			bool run_cond;
			pthread_mutex_t run_cond_lock;

			pthread_barrier_t exec_sleep_barrier;
			pthread_barrier_t exec_awake_barrier;

			int sub_turn;
			pthread_mutex_t sub_turn_lock;

			Project::System::FIFOQueue<std::function<void()>*>** task_queue;
			vector<Agent::Agent*> agents;

			void SetUpTrheads(int n);
			void MainCycle ();

			int max_turns;

			int execution_depth;
		};

		template <typename T>
		Agent::Agent* InstantiateAgent(Runtime* runtime, string name) {
			static int id = -1;
			return new T(runtime, name, ++id);
		}

		template <typename T>
		void CreateAgent(Runtime* runtime, string name) {
			Agent::Agent* agent = InstantiateAgent<T>(runtime, name);
			runtime->agents.push_back(agent);
		}

	} /* namespace System */
} /* namespace AgentC */

#include "thread_code.h"

#endif /* SRC_RUNTIME_H_ */
