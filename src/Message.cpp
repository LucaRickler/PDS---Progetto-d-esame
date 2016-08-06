/*
 * Message.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#include "Message.h"

namespace Project {
namespace Comms {

Message::Message() {}

Message::Message(Agent::AgentID* sender, const string& content) {
	this->sender = sender;
	this->content = content;
}

Message::Message(Message &other) {
	this->sender = other.sender;
	this->content = other.content;
}

Message::~Message() {}

const Agent::AgentID* Message::GetSender() {
	return sender;
}

const string Message::GetContent() {
	return content;
}

bool Message::SetRead() {
	--receivers;
	if(receivers == 0)
		return true;
	else
		return false;
}

} /* namespace Comms */
} /* namespace Project */
