/*
 * Agent.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_AGENT_H_
#define SRC_AGENT_H_

#include "dependencies.h"
#include "Runtime.h"


namespace Project {
	namespace Agent {

		struct AgentID {
			string name;
			int id;
			AgentID(){}
			AgentID(string name, int id) {
				this->name = name;
				this->id = id;
			}
		};

		typedef std::pair<string, Action*> ActionMapping;
		class Agent {
		public:
			Agent (System::Runtime* runtime, string name, int id);
			virtual ~Agent ();
			virtual void Setup ();
			void DoDelete ();
			virtual void OnDelete ();

			void AddAction (const string& key, Action* act);
			void ScheduleAction (const string& act);

			void Send (Comms::Message* msg);
			bool ReadMessage (Comms::Message& msg);

			AgentID* GetID ();

			Action* GetAction (const string& act);

			int GetPriority ();
			void SetPriority (const int &);

			void DeliverMessage(Comms::Message* msg);
		protected:
			unordered_map<string,Action*> myActions;
			AgentID* id;

			int execution_priority;
		private:
			System::Runtime* runtime;
			System::FIFOQueue<Comms::Message*>* messageQueue;
		};

	} /* namespace Agent */
} /* namespace Project */

#endif /* SRC_AGENT_H_ */
