/*
 * FIFOQueue.cpp
 *
 *  Created on: 19/lug/2016
 *      Author: luca
 */

#include "FIFOQueue.h"
#include <pthread.h>

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
bool FIFOQueue<T>::Pop(T& element){
	pthread_mutex_lock(&head_mutex);
	struct Node * new_head = head->next;
	if (new_head == NULL) {
		pthread_mutex_unlock(&head_mutex);
	    return false;
	}
	element = new_head->content;
	struct Node * n = head;
	head = new_head;
	pthread_mutex_unlock(&head_mutex);
	delete(n);
	return true;
}

template <typename T>
void FIFOQueue<T>::Push(const T& element){
	struct Node * n = new struct Node();
	n->content = element;
	n->next = NULL;
	pthread_mutex_lock(&tail_mutex);
	tail->next = n;
	tail = n;
	pthread_mutex_unlock(&tail_mutex);
}



} /* namespace System */
} /* namespace AgentC */
