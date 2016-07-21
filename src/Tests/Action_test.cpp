/*
 * Action_test.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: Luca Rickler
 */

#include "../Action.h"

using Project::Agent::Action;
using std::cout;
using std::endl;

class myAction : public Action {
public:
	string name;
	myAction() : Action(){

	}
	void Act() {
		cout << "Azione " << name << " eseguita" << endl;
	}
};

int main() {
	myAction* act1,* act2;
	act1 = new myAction();
	act2 = new myAction();
	act1->name = "1";
	act2->name = "2";

	cout << "Esecuzione dell'azione direttamente: " << endl;
	act1->Act();
	act2->Act();
	cout << "Esecuzione dell'azione via wrapper: " << endl;
	auto func1 = act1->DoAction();
	func1();
	func1 = act2->DoAction();
	func1();

	return 0;
}

