/*
 * Message.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_MESSAGE_H_
#define SRC_MESSAGE_H_

#include "dependencies.h"
#include "Agent.h"



namespace Project {
	namespace Comms {

		class Message {
		public:
			Message(Agent::AgentID* sender, const string& content);
			virtual ~Message();

			const Agent::AgentID* GetSender();
			const string GetContent();
			//void SetContent()

			friend class System::Runtime;
		private:
			struct Agent::AgentID* sender;
			string content;

		};

	} /* namespace Comms */
} /* namespace Project */

#endif /* SRC_MESSAGE_H_ */
