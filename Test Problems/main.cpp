/*
 * Selettore per la modalità di esecuzione.
 * Valori:
 * 		0	:	Sequenziale
 * 		1	:	Parallelo
 *
 * */
#define EXECUTION_MODE 		1

#include "../src/project.h"
using namespace Project;

//Define actions here

class MyAction : public Agent::Action {
public:
	MyAction(Agent::Agent* a) : Action(a) {

	}
	void Act() {

	}
};
//Define  agents here
class MyAgent : public Agent::Agent {
public:
	MyAgent(System::Runtime* runtime, string name, int id) : Agent(runtime, name, id) {
		SetPriority(1);
	}
	void Setup() {
		AddAction("MyAction", new MyAction(this));
		ScheduleAction("MyAction");
	}
};


int main() {
	System::Runtime* runtime = new System::Runtime(1);
	runtime->SetMaxTurns(1);

	//Here goes agent creation
	System::CreateAgent<MyAgent>(runtime, "MyAgent");

	runtime->Init(1);
}

