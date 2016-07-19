/*
 * Runtime.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_RUNTIME_H_
#define SRC_RUNTIME_H_

#include "project.h"
#include "FIFOQueue.h"

//using namespace Project;

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
			void Init();

		private:
			Project::System::FIFOQueue<std::function<void()>*> TaskQueue;
		};

} /* namespace System */
} /* namespace AgentC */

#endif /* SRC_RUNTIME_H_ */
