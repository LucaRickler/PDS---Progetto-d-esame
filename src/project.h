/*
 * project.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_PROJECT_H_
#define SRC_PROJECT_H_

namespace Project {

	namespace System {
		class Runtime;
		template <typename T> class FIFOQueue;
		struct ThreadPackage;
		void *ThreadExec (void* arg);
	}

	namespace Agent {
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

using std::string;
using std::vector;
using std::function;

#include "FIFOQueue.cpp"

#endif /* SRC_PROJECT_H_ */
