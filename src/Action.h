/*
 * Action.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_ACTION_H_
#define SRC_ACTION_H_

#include "project.h"

namespace Project {
namespace Agent {

class Action {
public:
	Action();
	Action (Agent* a);
	virtual ~Action();
	std::function<void()> DoAction ();
	void Act ();
};

} /* namespace Agent */
} /* namespace Project */

#endif /* SRC_ACTION_H_ */
