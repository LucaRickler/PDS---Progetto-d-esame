/*
 * Agent.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_AGENT_H_
#define SRC_AGENT_H_

#include "project.h"
//#include "Runtime.h"

namespace Project {
	namespace Agent {
		class Agent {
		public:
			Agent (System::Runtime* runtime, string name);
			virtual ~Agent ();
			void AddAction (Action* action);
			virtual void Setup ();
			void DoDelete ();
			virtual void OnDelete ();
			void Send (Comms::Message* message);
			Comms::Message ReadMessage ();
			void ScheduleAction (Action*);
		protected:
			std::vector<Action*> myActions;
			std::string name;
			//AgentID id;
		private:
			System::Runtime* runtime;
			System::FIFOQueue<Comms::Message*> messageQueue;
		};

	} /* namespace Agent */
} /* namespace Project */

#endif /* SRC_AGENT_H_ */
