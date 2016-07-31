/*
 * Agent.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_AGENT_H_
#define SRC_AGENT_H_

#include "project.h"
#include "Runtime.h"

namespace Project {
	namespace Agent {
		typedef std::pair<string, Action*> ActionMapping;
		class Agent {
		public:
			Agent (System::Runtime* runtime, string name);
			virtual ~Agent ();
			virtual void Setup ();
			void DoDelete ();
			virtual void OnDelete ();

			void AddAction (const string& key, Action* act);
			void ScheduleAction (const string& act);

			void Send (const Comms::Message* msg);
			bool ReadMessage (Comms::Message* msg);

			string GetName ();
			Action* GetAction (const string& act);
		protected:
			unordered_map<string,Action*> myActions;
			string name;
			//AgentID id;
		private:
			System::Runtime* runtime;
			System::FIFOQueue<Comms::Message*> messageQueue;
		};

	} /* namespace Agent */
} /* namespace Project */

#endif /* SRC_AGENT_H_ */
