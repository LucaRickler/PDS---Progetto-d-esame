/*
 * Message.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#include "Message.h"

namespace Project {
namespace Comms {

Message::Message(Agent::AgentID* sender, const string& content) {
	this->sender = sender;
	this->content = content;
}

Message::~Message() {}

const Agent::AgentID* Message::GetSender() {
	return sender;
}

const string Message::GetContent() {
	return content;
}

} /* namespace Comms */
} /* namespace Project */
