#include <iostream>
#include "list.h"

List::List() {
	first = nullptr;


}

List::~List() {
	Node* n(first);
	while(n != nullptr){
		Node* next(n->next);
		delete n;
		n = next;
	}
	first = nullptr;


}

bool List::exists(int d) const {
	Node* n(first);
	while(n != nullptr) {
		if (d == n->value) {

			return true;
		}
		n = n->next;
	}
	return false;


}

int List::size() const {
	Node* n(first);
	int size(0);
	while(n != nullptr){
		++size;
		n = n->next;
	}
	return size;

}

bool List::empty() const {
	return first == nullptr;
}

void List::insertFirst(int d) {

	first = new Node(d, first);



}

void List::remove(int d, DeleteFlag df) {
	if (first == nullptr){
		return;
	}
	if (df == DeleteFlag::EQUAL){
		Node* n(first);
		Node* previous(nullptr);
		while (n != nullptr){
			if(n->value == d){
				if (n == first){
					first = n->next;

					delete n;
					n = first;
				}else {
				previous->next = n->next;
				delete n;
				n = previous->next;
				}
			}else {
				previous = n;
				n = n->next;
			}


		}
	}

	if (df == DeleteFlag::LESS){
		Node* n(first);
		Node* previous(nullptr);
		while (n != nullptr){
			if(n->value < d){
				if (n == first){
					first = n->next;

					delete n;
					n = first;
				}else {
				previous->next = n->next;
				delete n;
				n = previous->next;
				}
			}else {
				previous = n;
				n = n->next;
			}


		}
	}
	if (df == DeleteFlag::GREATER){
		Node* n(first);
		Node* previous(nullptr);
		while (n != nullptr){
			if(n->value > d){
				if (n == first){
					first = n->next;

					delete n;
					n = first;
				}else {
				previous->next = n->next;
				delete n;
				n = previous->next;
				}
			}else {
				previous = n;
				n = n->next;
			}


		}
	}
}


void List::print() const {
	Node* n(first);
	while(n != nullptr) {
		std::cout<< n->value << std::endl;
		n = n->next;
	}


}
