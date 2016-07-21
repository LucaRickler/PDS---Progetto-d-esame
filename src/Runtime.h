/*
 * Runtime.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_RUNTIME_H_
#define SRC_RUNTIME_H_

#include "project.h"

namespace Project {
	namespace Agent {
		//typename ActionWrapper std::function<void()>;
	}
	namespace System {

		class Runtime {
		public:
			Runtime();
			virtual ~Runtime();

			void Init(int argc, char** argv);
			//void Init();

		private:
			vector<pthread_t> threads;
			Project::System::FIFOQueue<std::function<void()>*>* TaskQueue;
			void SetUpTrheads(int n);


		};

	} /* namespace System */
} /* namespace AgentC */

#endif /* SRC_RUNTIME_H_ */
