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
	this->myActions = vector<Action*>();
	this->messageQueue = System::FIFOQueue<Comms::Message*>();

}

Agent::~Agent() {
	// TODO Auto-generated destructor stub
}

void Agent::ScheduleAction(Action* act) {

}

void Agent::OnDelete() {}

} /* namespace Agent */
} /* namespace Project */
