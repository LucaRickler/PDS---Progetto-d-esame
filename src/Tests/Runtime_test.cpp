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

class MyAgent1 : public Project::Agent::Agent {
public:
	MyAgent1 (Runtime* runtime, string name) : Agent(runtime, name) {}
	void Setup() {
		std::cout << "Hello world from " << name << std::endl;
	}
};
class MyAgent2 : public Project::Agent::Agent {
public:
	MyAgent2 (Runtime* runtime, string name) : Agent(runtime, name) {}
	void Setup() {
		std::cout << "I shouldn't be here!"<< std::endl;
	}
};


int main() {
	Runtime* runtime = new Runtime();

	Project::System::CreateAgent<MyAgent1>(runtime, "agent_1");
	Project::System::CreateAgent<MyAgent1>(runtime, "agent_2");
	Project::System::CreateAgent<MyAgent2>(runtime, "agent_3");


	runtime->Init(3,NULL);
	return 0;
}
