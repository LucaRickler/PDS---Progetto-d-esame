/*
 * Selettore per la modalità di esecuzione.
 * Valori:
 * 		0	:	Sequenziale
 * 		1	:	Parallelo
 *
 * */
#define EXECUTION_MODE 		1

#include "../../src/project.h"
using namespace Project;

#include <cstdlib>

const int N_AGENTS = 2000000;

//Define actions here

class Generate : public Agent::Action {
public:
	Generate(Agent::Agent* a) : Action(a) {}

	void Act() {
		bool end = false;
		Comms::Message msg;
		if(my_agent->ReadMessage(msg))
			if(msg.GetOntology() == "Stop")
				end = true;

		if(!end){
			int n = rand()%N_AGENTS;
			printf("number: %d\n",n);
			my_agent->Send(new Comms::Message(my_agent->GetID(), std::to_string(n), "Result"));
			my_agent->ScheduleAction("Generate");
		}
	}
};

class Check : public Agent::Action {
public:
	Check(Agent::Agent* a) : Action(a) {
		number = std::to_string(my_agent->GetID()->id);
	}
	void Act() {
		bool end = false;
		Comms::Message msg;
		while(my_agent->ReadMessage(msg)) {
			if(msg.GetOntology() == "Stop"){
				end = true;
				break;
			}
			else if (msg.GetOntology() == "Result")
				if(msg.GetContent() == number){
					end = true;
					printf("Stopping game\n");
					my_agent->Send(new Comms::Message(my_agent->GetID(), "Stop", "Stop"));
				}

		}
		if(!end)
			my_agent->ScheduleAction("Check");
	}
private:
	string number;
};


//Define  agents here
class Sender : public Agent::Agent {
public:
	Sender(System::Runtime* runtime, string name, int id) : Agent(runtime, name, id) {
		SetPriority(1);
	}
	void Setup() {
		AddAction("Generate", new Generate(this));
		ScheduleAction("Generate");
	}
};

class Receiver : public Agent::Agent {
public:
	Receiver(System::Runtime* runtime, string name, int id) : Agent(runtime, name, id) {
		SetPriority(2);
	}
	void Setup() {
		AddAction("Check", new Check(this));
		ScheduleAction("Check");
	}
};

#include <sstream>

int main(int argc, char** argv) {
	std::istringstream ss(argv[1]);
	int nthread;
	if (!(ss >> nthread)){
		std::cerr << "Invalid number " << argv[1] << '\n';
		return 1;
	}

	System::Runtime* runtime = new System::Runtime(2);
	runtime->SetMaxTurns(3);

	//Here goes agent creation
	System::CreateAgent<Sender>(runtime, "Sender");
	for(int i = 0; i < N_AGENTS; i++)
		System::CreateAgent<Receiver>(runtime, "Receiver");

	runtime->Init(nthread);
}

