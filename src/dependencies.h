/*
 * project.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_DEPENDENCIES_H_
#define SRC_DEPENDENCIES_H_

#define EXECUTION_MODE 		1

namespace Project {

	namespace System {
		class Runtime;
		template <typename T> class FIFOQueue;
		void *ThreadExec (void* arg);
	}

	namespace Agent {
		struct AgentID;
		class Agent;
		class Action;
	}

	namespace Comms {
		class Message;
	}

}


#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <functional>
#include <pthread.h>
#include <algorithm>
#include <unordered_map>

using std::string;
using std::vector;
using std::function;
using std::unordered_map;

#include "FIFOQueue.cpp"

#endif /* SRC_DEPENDENCIES_H_ */
