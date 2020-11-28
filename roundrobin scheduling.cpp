
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

//Implementation of Circular Doubly Linked List

//Class Declaration

class DoubleCircularList {

public:
	int counter = 0;

//Node Declaration

	struct node {
		int processLength;
		struct node* next;
		struct node* prev;
	}*start, * last;

//Constructor

	DoubleCircularList() {
		start = NULL;
		last = NULL;
	}

//CREATE NODE AND ALLOCATE MEMORY DYNAMICALLY

	node* createNode(int value) {
		struct node* temp = new node();
		temp->processLength = value;
		return temp;
	}

//INSERTS ELEMENT AT LAST

	void insertLast(int processLength) {

		node* temp = createNode(processLength);
		if (start == last && start == NULL) {
			temp->next = temp;
			temp->prev = temp;
			start = temp;
			last = temp;
		}
		else {
			start->prev = temp;
			last->next = temp;
			temp->next = start;
			temp->prev = last;
			last = temp;
		}
		counter++;
	}

//Delete Node at Particular Position

	void deleteAtPos(int pos)
	{
		int i;
		node* ptr;
		if (start == last)
		{
			if (start == NULL) {
				cout << "List is empty, nothing to delete" << endl;
				return;
			}
			free(start);
			start = last = NULL;
			counter--;
			return;
		}
		ptr = start;
		for (i = 1; i < pos; i++) {
			ptr = ptr->next;
		}
		if (ptr == start) {
			start = ptr->next;
		}
		else if (ptr == last) {
			last = ptr->prev;
		}
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
		free(ptr);
		counter--;

	}

//Display Elements of the List

	void display() {
		if (start == last && start == NULL) {
			return;
		}
		node* temp = start;
		for (int i = 1; i < counter; i++) {
			cout << temp->processLength << "<->";
			temp = temp->next;
		}
		cout << temp->processLength << endl;
	}

//Round Robin implementation

	void roundRobinScheduling(int quantum) {
		cout << "\nOriginal process lengths are as follows:\n" << endl;
		this->display();
		if (start != NULL) {
			cout << "\nThe circular linked list after each quantum is as follows:\n" << endl;
		}
		while (start != NULL) {
			if (start->processLength > 0) {
				if (start->processLength > quantum) {
					start->processLength -= quantum;
					last = start;
					start = start->next;
				}
				else {
					start->processLength = 0;
				}
			}
			if (start->processLength == 0) {
				this->deleteAtPos(1);
			}
			this->display();
		}
	}
};

//main method to test the code

int main() {

	cout << "'''Implementation of Round Robin Scheduling'''" << endl << endl;

//Initialize a double circular list and insert process lengths

	DoubleCircularList cList;
	int i = 1, processLength = 0;
	cout << "Enter process lengths (Enter any negative number if there are no more processes)" << endl;
	while (1) {
		cout << "Process " << i << " : ";
		cin >> processLength;
		if (processLength < 0) {
			break;
		}
		cList.insertLast(processLength);
		i++;
	}

//Call the roundRobinScheduling method to test the algorithm

	int quantum = 5;
	cList.roundRobinScheduling(quantum);
	return 0;
}
