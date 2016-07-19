/*
 * project.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_PROJECT_H_
#define SRC_PROJECT_H_

#include <stdio.h>
#include <string>
#include <iomanip>
#include <cmath>

using std::string;

namespace Project {

	namespace System {
		class Runtime;
		class FIFOQueue;
	}

	namespace Agent {
		class Agent;
		class Action;
	}

	namespace Comms {
		class Message;
	}

}


#endif /* SRC_PROJECT_H_ */
