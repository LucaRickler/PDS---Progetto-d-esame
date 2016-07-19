/*
 * FIFOQueue.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#include "FIFOQueue.h"

namespace Project {
namespace System {

template <typename T>
FIFOQueue<T>::FIFOQueue() {
	pthread_mutex_init(&head_mutex, NULL);
	pthread_mutex_init(&tail_mutex, NULL);
	struct Node * n = new struct Node();
	n->next = NULL;
	head = tail = n;
}

template <typename T>
FIFOQueue<T>::~FIFOQueue() {
	do{
		Node* n = head->next;
		delete head;
		head = n;
	}while(head);
}

template <typename T>
T Pop(){

}


} /* namespace System */
} /* namespace AgentC */
