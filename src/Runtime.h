/*
 * Runtime.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_RUNTIME_H_
#define SRC_RUNTIME_H_

#include "project.h"

namespace AgentC {
	namespace System {

		class Runtime {
		public:
			Runtime();
			virtual ~Runtime();

			void Init(string* argv, int argc);

		private:
			Project::System::FIFOQueue TaskQueue;
		};

} /* namespace System */
} /* namespace AgentC */

#endif /* SRC_RUNTIME_H_ */
