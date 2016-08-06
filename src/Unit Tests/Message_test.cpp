/*
 * Message_test.cpp
 *
 *  Created on: 03/ago/2016
 *      Author: luca
 */

#include "../project.h"


using namespace Project;

class SenderAction : public Agent::Action {
public:
	SenderAction(Agent::Agent* a) : Action(a) {}
	void Act() {
		//string content = "Message";
		Comms::Message* msg = new Comms::Message(my_agent->GetID(), "Message received");
		my_agent->Send(msg);
		my_agent->ScheduleAction("Send");

	}
};

class Sender : public Agent::Agent {
public:
	Sender(System::Runtime* runtime, string name, int id) : Agent(runtime, name, id) {
		this->SetPriority(1);
	}
	void Setup() {
		AddAction("Send",new SenderAction(this));
		ScheduleAction("Send");
	}
};

class Receive : public Agent::Action {
public:
	Receive(Agent::Agent* a) : Action(a) {}
	void Act() {
		Comms::Message msg;
		if(my_agent->ReadMessage(msg))
			std::cout << msg.GetContent() << "\n";
		else
			printf("No message\n");
		my_agent->ScheduleAction("Receive");
	}
};

class Receiver : public Agent::Agent {
public:
	Receiver(System::Runtime* runtime, string name, int id) : Agent(runtime, name, id) {
		this->SetPriority(2);
	}
	void Setup() {
		AddAction("Receive",new Receive(this));
		ScheduleAction("Receive");
	}
};

int main() {
	System::Runtime* runtime = new System::Runtime(2);
	runtime->SetMaxTurns(4);

	System::CreateAgent<Sender>(runtime, "sender");
	System::CreateAgent<Receiver>(runtime, "receiver");
	System::CreateAgent<Receiver>(runtime, "receiver");

	runtime->Init(3);

	return 0;
}
