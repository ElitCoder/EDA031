#include <iostream>
#include "list.h"

List::List() :
	first(nullptr) {
}

List::~List() {
	Node *current = first;

	while(current != nullptr) {
		Node *next = current->next;

		delete current;
		current = next;
	}
}

bool List::exists(int d) const {
	Node *current = first;

	while(current != nullptr) {
		if(current->value == d) {
			return true;
		}

		current = current->next;
	}

	return false;
}

int List::size() const {
	unsigned int size = 0;
	Node *current = first;

	while(current != nullptr) {
		current = current->next;
		++size;
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
	Node *previous = nullptr;
	Node *current = first;

	while(current != nullptr) {
		bool removeCurrent = false;

		switch(df) {
			case DeleteFlag::LESS:
				if(current->value < d) {
					removeCurrent = true;
				}
				break;

			case DeleteFlag::EQUAL:
				if(current->value == d) {
					removeCurrent = true;
				}
				break;

			case DeleteFlag::GREATER:
				if(current->value > d) {
					removeCurrent = true;
				}
				break;
		}

		if(removeCurrent) {
			Node *next = current->next;

			if(current == first) {
				first = next;
				previous = nullptr;
			}

			else {
				previous->next = next;
			}

			delete current;
			current = next;

			continue;
		}

		previous = current;
		current = current->next;
	}
}

void List::print() const {
	Node *current = first;

	while(current != nullptr) {
		std::cout << current->value << " ";

		current = current->next;
	}
}
