/*
 * project.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_PROJECT_H_
#define SRC_PROJECT_H_

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <functional>
#include <pthread.h>

using std::string;
using std::vector;

namespace Project {

	namespace System {
		class Runtime;
		template <typename T> class FIFOQueue;
		void *thread_exec (void *);
	}

	namespace Agent {
		class Agent;
		class Action;
		//class ActionWrapper;
	}

	namespace Comms {
		class Message;
	}

}

#include "FIFOQueue.cpp"
#include "Message.h"
#include "Agent.h"
#include "Action.h"
#include "Runtime.h"

#endif /* SRC_PROJECT_H_ */
