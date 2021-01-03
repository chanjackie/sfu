// ID cbdaaf363f8f199871c6a35420714712

#include "task08.h"

OrderedList::Node* OrderedList::add(int val) {
	Node* newNode = new Node(val);
	if (head != nullptr && !head->isValid()) {
		Node* current = head;
		head = head->getNext();
		delete current;
	}
	if (head == nullptr) {
		head = newNode;
		return newNode;
	}
	if (newNode->getValue() <= head->getValue()) {
		newNode->setNext(head);
		head = newNode;
		return newNode;
	}
	Node* iter = head->getNext();
	Node* prev = head;
	while (iter != nullptr) {
		if (!iter->isValid()) {
			Node* current = iter;
			iter = iter->getNext();
			prev->setNext(iter);
			delete current;
			continue;
		}
		if (newNode->getValue() <= iter->getValue()) {
			newNode->setNext(iter);
			prev->setNext(newNode);
			return newNode;
		}
		prev = iter;
		iter = iter->getNext();
	}
	prev->setNext(newNode);
	return newNode;
}

OrderedList::Node* OrderedList::getNode(int val) {
	if (head != nullptr && !head->isValid()) {
		Node* current = head;
		head = head->getNext();
		delete current;
	}
	if (head == nullptr) {
		return nullptr;
	}
	if (head->getValue() == val) {
		return head;
	}
	Node* iter = head->getNext();
	Node* prev = head;
	while (iter != nullptr) {
		if (!iter->isValid()) {
			Node* current = iter;
			iter = iter->getNext();
			prev->setNext(iter);
			delete current;
			continue;
		}
		if (iter->getValue() == val) {
			return iter;
		}
		prev = iter;
		iter = iter->getNext();
	}
	return nullptr;
}

OrderedList::~OrderedList() {
	Node* curr;
	while (head != nullptr) {
		curr = head;
		head = head->getNext();
		delete curr;
	}
}
