/*
 * Message.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_MESSAGE_H_
#define SRC_MESSAGE_H_

#include "project.h"

namespace Project {
	namespace Comms {

		class Message {
		public:
			Message();
			virtual ~Message();
		};

	} /* namespace Comms */
} /* namespace Project */

#endif /* SRC_MESSAGE_H_ */
