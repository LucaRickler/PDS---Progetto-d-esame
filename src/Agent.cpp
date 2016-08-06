/*
 * Agent.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#include "Agent.h"

namespace Project {
namespace Agent {

Agent::Agent(Project::System::Runtime* runtime, string name, int id) {
	this->runtime = runtime;
	this->myActions = unordered_map<string,Action*>();
	this->messageQueue = System::FIFOQueue<Comms::Message*>();
	//this->name = name;
	this->id = new AgentID(name, id);
}

Agent::~Agent() {
	std::for_each(myActions.begin(), myActions.end(), [](ActionMapping a){delete a.second;});
	Comms::Message* msg;
	while(messageQueue.Pop(msg)){
		delete msg;
	}
	delete id;
}

void Agent::AddAction (const string& key, Action* action){
	myActions.insert(ActionMapping(key,action));
}

void Agent::ScheduleAction(const string& key) {
	runtime->ScheduleAction(GetAction(key), GetPriority());
}

Action* Agent::GetAction(const string& key) {
	if(myActions.count(key))
		return myActions[key];
	return nullptr;
}

int Agent::GetPriority() {
	return execution_priority;
}

void Agent::SetPriority(const int & p) {
	if(p > runtime->GetExecutionDepth())
		execution_priority = runtime->GetExecutionDepth() -1;
	else
		execution_priority = p-1;
}

void Agent::Send(Comms::Message* msg) {
	runtime->DispatchMessage(msg);
}

void Agent::DeliverMessage(Comms::Message* msg) {
	this->messageQueue.Push(msg);
}



void Agent::DoDelete() {
	OnDelete();
	runtime->DeleteAgent(this);
}

void Agent::OnDelete() {}
void Agent::Setup() {}

} /* namespace Agent */
} /* namespace Project */
