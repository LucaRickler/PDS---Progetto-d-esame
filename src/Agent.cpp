/*
 * Agent.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#include "Agent.h"

namespace Project {
namespace Agent {

Agent::Agent(Project::System::Runtime* runtime, string name) {
	this->runtime = runtime;
	this->myActions = unordered_map<string,Action*>();
	this->messageQueue = System::FIFOQueue<Comms::Message*>();
	this->name = name;

}

Agent::~Agent() {
	std::for_each(myActions.begin(), myActions.end(), [](ActionMapping a){delete a.second;});
	Comms::Message* msg;
	while(messageQueue.Pop(msg)){
		delete msg;
	}
}
void Agent::AddAction (const string& key, Action* action){
	myActions.insert(ActionMapping(key,action));
}

void Agent::ScheduleAction(const string& key) {
	runtime->ScheduleAction(GetAction(key));
}

Action* Agent::GetAction(const string& key) {
	if(myActions.count(key))
		return myActions[key];
	return nullptr;
}

void Agent::DoDelete() {
	OnDelete();
	runtime->DeleteAgent(this);
}

void Agent::OnDelete() {}
void Agent::Setup() {}

} /* namespace Agent */
} /* namespace Project */
