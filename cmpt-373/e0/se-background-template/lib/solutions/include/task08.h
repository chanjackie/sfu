// ID cbdaaf363f8f199871c6a35420714712
#pragma once

#include "Support.h"

#include <memory>

class OrderedList 
{
public:
	class Node {
	private:
		int value;
		Node* nextNode;
		bool valid = false;
	public:
		Node(int val) { value = val; nextNode = nullptr; valid = true; }
		Node* getNext() { return nextNode; }
		int getValue() { return value; }
		void remove() { valid = false; }
		bool isValid() { return valid; }
		void setNext(Node* node) { nextNode = node; }
	};

	OrderedList() { head = nullptr; }
	~OrderedList();

	Node* add(int val);
	Node* getNode(int val);
private:
	Node* head;
};