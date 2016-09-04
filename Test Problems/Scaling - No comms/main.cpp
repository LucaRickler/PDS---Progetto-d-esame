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

//Define actions here

class Compute : public Agent::Action {
public:
	Compute(Agent::Agent* a,const int& n) : Action(a) {
		this->n = n;
	}
	void Act() {
		int m = 0;
		bool divisible;
		int i, j;
		i = 2;
		//for(i = 1; i <= n; i++){
		while(i <= n) {
			divisible = false;
			for(j = 2; j< i; j++){
				if(i%j == 0){
					divisible = true;
				}
			}
			if(!divisible)
				m = i;
			i++;
		}
		printf("%d\n",m);
		my_agent->ScheduleAction("Compute");
	}
private:
	int n;
};
//Define  agents here

class MyAgent : public Agent::Agent {
public:
	MyAgent(System::Runtime* runtime, string name, int id) : Agent(runtime, name, id) {
		SetPriority(1);
	}
	void Setup() {
		AddAction("Compute", new Compute(this, 10000));
		ScheduleAction("Compute");
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
	System::Runtime* runtime = new System::Runtime(1);
	runtime->SetMaxTurns(3);

	//Here goes agent creation
	for(int i = 0; i < 2000; i++)
		System::CreateAgent<MyAgent>(runtime, "MyAgent");

	runtime->Init(nthread);
}

