/*
 * FIFOQueue.h
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#ifndef SRC_FIFOQUEUE_H_
#define SRC_FIFOQUEUE_H_

#include <pthread.h>

namespace Project {
	namespace System {

		template <typename T>
		class FIFOQueue {
			struct Node {
				T content;
				Node* next;
			};
		public:
			FIFOQueue();
			virtual ~FIFOQueue();
			void Push(T element);
			T Pop();
		private:
			pthread_mutex_t head_mutex;
			pthread_mutex_t tail_mutex;
			Node* head;
			Node* tail;
		};

	} /* namespace System */
} /* namespace AgentC */

#endif /* SRC_FIFOQUEUE_H_ */
