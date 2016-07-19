/*
 * Action.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#include "Action.h"

namespace Project {
namespace Agent {

Action::Action() {
	// TODO Auto-generated constructor stub

}

Action::~Action() {
	// TODO Auto-generated destructor stub
}

void Action::Act() {
	puts("prova");
}

std::function<void()> Action::DoAction() {
	return [this](){this->Act();};
}

} /* namespace Agent */
} /* namespace Project */
