/*
 * Runtime_test.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: Luca Rickler
 */

#include "../project.h"
#include "../Action.h"
#include "../Agent.h"

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
	MyAgent1 (Runtime* runtime, string name) : Agent(runtime, name) {}
	void Setup() {
		std::cout << "Hello world from " << name << std::endl;
		//Project::Agent::Action* act1 = ;
		AddAction("act1", new MyAction(this));
		ScheduleAction("act1");
	}
};
class MyAgent2 : public Project::Agent::Agent {
public:
	MyAgent2 (Runtime* runtime, string name) : Agent(runtime, name) {}
	void Setup() {
		std::cout << "I shouldn't be here!"<< std::endl;
		//Project::Agent::Action* act1 = new MyAction(this);
		AddAction("act1", new MyAction(this));
		ScheduleAction("act1");
	}
};

#include "../Runtime.h"
#include "../thread_code.h"

int main() {
	Runtime* runtime = new Runtime();

	Project::System::CreateAgent<MyAgent1>(runtime, "agent_1");
	Project::System::CreateAgent<MyAgent1>(runtime, "agent_2");
	Project::System::CreateAgent<MyAgent2>(runtime, "agent_3");

	runtime->SetMaxTurns(20);

	runtime->Init(100,NULL);
	return 0;
}
