/*
 * Action.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#include "Action.h"

namespace Project {
namespace Agent {

Action::Action(Agent* a) {
	this->my_agent = a;
	actionReference = new std::function<void()>([this](){this->Act();});
}

Action::~Action() {
	delete actionReference;
}

void Action::Act() {}


} /* namespace Agent */
} /* namespace Project */
