#include "../Action.h"

using Project::Agent::Action;
using std::cout;
using std::endl;

class myAction : public Action {
public:
	string name;
	myAction(Project::Agent::Agent* a) : Action(a){

	}
	void Act() {
		cout << "Azione " << name << " eseguita" << endl;
	}
};

int main() {
	Project::Agent::Agent* a;
	myAction* act1,* act2;
	act1 = new myAction(a);
	act2 = new myAction(a);
	act1->name = "1";
	act2->name = "2";

	cout << "Esecuzione dell'azione direttamente: " << endl;
	act1->Act();
	act2->Act();
	cout << "Esecuzione dell'azione via wrapper: " << endl;
	auto func1 = act1->actionReference;
	(*func1)();
	func1 = act2->actionReference;
	(*func1)();

	return 0;
}

