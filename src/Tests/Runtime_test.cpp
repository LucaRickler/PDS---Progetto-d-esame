/*
 * Runtime_test.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: Luca Rickler
 */

#include "../project.h"
#include "../Runtime.h"
#include "../Agent.h"
#include "../Action.h"
#include "../thread_code.h"

using Project::System::Runtime;

class MyAgent : public Project::Agent::Agent {
public:
	MyAgent (Runtime* runtime, string name) : Agent(runtime, name) {}
	void Setup() {
		std::cout << "Hello world from " << name << std::endl;
	}
};



int main() {
	Runtime runtime = Runtime();

	Project::System::CreateAgent<MyAgent>(&runtime, "agent");

	return 0;
}
