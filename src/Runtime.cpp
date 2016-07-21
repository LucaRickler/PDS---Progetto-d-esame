/*
 * Runtime.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#include "Runtime.h"
#include <pthread.h>

namespace Project {
namespace System {

Runtime::Runtime() {

}

Runtime::~Runtime() {
	// TODO Auto-generated destructor stub
}

void Runtime::Init(int argc, char** argv) {

}

void Runtime::SetUpTrheads(int n) {
	pthread_t thread;
	pthread_attr_t detached;
	pthread_attr_init(&detached);
	pthread_attr_setdetachstate(&detached, PTHREAD_CREATE_DETACHED);
	for(int i = 1; i < n; i++) {
		pthread_create(&thread, &detached, &thread_exec, NULL);
		threads.push_back(thread);
	}
}

/*void Runtime::Init() {

}*/

} /* namespace System */
} /* namespace AgentC */
