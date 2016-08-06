/*
 * Action.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_ACTION_H_
#define SRC_ACTION_H_

#include "dependencies.h"

namespace Project {
namespace Agent {
class Action {
public:
	Action (Agent* a);
	virtual ~Action();
	function<void()>* actionReference;
	virtual void Act ();
	Agent* my_agent;
//private:

};

} /* namespace Agent */
} /* namespace Project */

#endif /* SRC_ACTION_H_ */
