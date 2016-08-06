/*
 * Runtime_test.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: Luca Rickler
 */

#include "../project.h"


using Project::System::Runtime;

class MyAction : public Project::Agent::Action {
public:
	MyAction (Project::Agent::Agent* a) : Action(a) {}
	void Act () {
		printf("Doing stuff\n");
		my_agent->ScheduleAction("act1");
	}
};

class MyAgent1 : public Project::Agent::Agent {
public:
	MyAgent1 (Runtime* runtime, string name, int id) : Agent(runtime, name, id) {
		SetPriority(1);
	}
	void Setup() {
		std::cout << "Hello world from " << id->name << std::endl;
		AddAction("act1", new MyAction(this));
		ScheduleAction("act1");
	}
};
class MyAgent2 : public Project::Agent::Agent {
public:
	MyAgent2 (Runtime* runtime, string name, int id) : Agent(runtime, name, id) {
		SetPriority(2);
	}
	void Setup() {
		std::cout << "I shouldn't be here!"<< std::endl;
		AddAction("act1", new MyAction(this));
		ScheduleAction("act1");
	}
};

#include "../Runtime.h"
#include "../thread_code.h"

int main() {
	Runtime* runtime = new Runtime(2);
	runtime->SetMaxTurns(5);

	for(int i = 0; i < 1; i++)
		Project::System::CreateAgent<MyAgent1>(runtime, "agent_1");
	for(int i = 0; i < 1; i++)
		Project::System::CreateAgent<MyAgent2>(runtime, "agent_2");



	runtime->Init(1,NULL);
	return 0;
}
