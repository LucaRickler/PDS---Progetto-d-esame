/*
 * Agent.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_AGENT_H_
#define SRC_AGENT_H_

#include "project.h"

namespace Project {

	namespace Comms {
		class Message;
	}

	namespace Agent {
		class Action;

		class Agent {
		public:
			Agent(Project::System::Runtime* runtime);
			virtual ~Agent();
			void AddAction (Action* action);
			void Setup ();
			void DoDelete ();
			void OnDelete ();
			void Send (Project::Comms::Message* message);
			Project::Comms::Message ReadMessage ();
			std::vector<Action*> myActions;
		protected:
			std::string name;
			//AgentID id;
		private:
			Project::System::Runtime* runtime;
			Project::System::FIFOQueue<Project::Comms::Message*> messageQueue;
		};

	} /* namespace Agent */
} /* namespace Project */

#endif /* SRC_AGENT_H_ */
