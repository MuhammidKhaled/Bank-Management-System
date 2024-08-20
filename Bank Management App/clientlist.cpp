#include "clientlist.h"

// The Constructors
ClientNode::ClientNode() :indirectObject(0), link(0) {}

ClientList::ClientList(): head(0), current(0), count(0) {}

// Query Methods
int ClientList::position() const {
	if (head == nullptr) {
		return 0;
	}

	int pos = 1;
	ClientNode* temp = head;
	while (temp != current && temp != nullptr) {
		temp = temp->link;
		pos++;
	}

	return temp == nullptr ? 0 : pos;
}

int ClientList::first() const {
	return current == head;
}

int ClientList::end() const {
	if (current == 0)
		return 0;
	else
		return current->link == 0;
}

int ClientList::size() const {
	return count;
}

// Navigation Methods
void ClientList::reset() {
	current = head;
}

void ClientList::next() {
	if (current->link == 0)
		return;
	else
		current = current->link;
}

void ClientList::previous() {
	if (current != nullptr && current != head) {
		ClientNode* temp = head;
		while (temp->link != current) {
			temp = temp->link;
		}
		current = temp;
	}
}

// Inserting & Adding Methods
int ClientList::append(Client& c) {
	ClientNode* p;
	p = new ClientNode;
	if (p != 0) {
		p->indirectObject = &c;
		if (count == 0)
			head = current = p;
		else {
			ClientNode* prior, * after;
			prior = current;
			while (prior->link != 0)
				prior = prior->link;
			after = 0;
			prior->link = p;
			p->link = after;
		}
		count++; current = p;
		return 1;
	}
	else {
		return 0;
	}
}

int ClientList::insertBefore(Client& c) {
	ClientNode* p;
	p = new ClientNode;
	if (p != nullptr) {
		p->indirectObject = &c;
		if (count == 0 || current == head) {
			p->link = head;
			head = p;
			current = p;
		}
		else {
			ClientNode* prior;
			prior = head;
			while (prior->link != current) {
				prior = prior->link;
			}
			prior->link = p;
			p->link = current;
			current = p;
		}
		count++;
		return 1;
	}
	else {
		return 0;
	}
}

int ClientList::insertAfter(Client& c) {
	ClientNode* p;
	p = new ClientNode;
	if (p != 0) {
		p->indirectObject = &c;
		if (count == 0)
			head = current = p;
		else {
			ClientNode* prior, * after;
			prior = current;
			after = current->link;
			prior->link = p;
			p->link = after;
		}
		count++; current = p;
		return 1;
	}
	else {
		return 0;
	}
}

int ClientList::insert(Client& c) {
	ClientNode* p;
	p = new ClientNode;
	if (p != 0) {
		p->indirectObject = &c;
		p->link = head;
		count++; current = p; head = p;
		return 1;
	}
	else {
		return 0;
	}
}

// Retrieving Methods
Client* ClientList::retrieve() const {
	return current->indirectObject;
}

Client* ClientList::retrieve(std::string ssn) {
	int found = 0;
	ClientNode* p = head;
	Client* pc = nullptr;
	while (p != 0) {
		pc = p->indirectObject;
		if (pc->socialSecurityNumber() == ssn) {
			found = 1; break;
		}
		else {
			p = p->link; 
		}
	}
	if (found)
		current = p;
	else
		pc = 0;

	return pc;
}

Client* ClientList::operator[](int i) {
	Client* clientLoc;
	if (i < 0 || i > count - 1)
		clientLoc = 0;
	else {
		current = head;
		for (int k = 0; k < i; k++)
			current = current->link;
		clientLoc = current->indirectObject;
	}
	return clientLoc;
}

// Remove Methods
Client* ClientList::remove() {
	Client* clientLoc;
	if (count == 0)
		clientLoc = 0;
	else {
		ClientNode* after;
		after = current->link;
		if (current == head)
			head = after;
		else {
			ClientNode* prior;
			prior = head;
			while (prior->link != current)
				prior = prior->link;
			prior->link = after;
		}
		clientLoc = current->indirectObject;
		delete current;
		count--;
		if (after == 0)
			current = head;
		else
			current = after;
	}
	return clientLoc;
}

Client* ClientList::remove(std::string ssn) {
	Client* pc;
	pc = retrieve(ssn);
	if (pc != 0)
		remove();
	return pc;
}

ClientList::~ClientList() {
	ClientNode* p;
	current = head;
	for (int i = 0; i < count; i++) {
		p = current;
		current = current->link;
		delete p;
	}
}

// Assignment Operator
ClientList& ClientList::operator=(const ClientList& cl) {
	if (this != &cl) { 
		while (head != nullptr) {
			ClientNode* temp = head;
			head = head->link;
			delete temp;
		}
		current = nullptr;
		count = 0;

		ClientNode* pNode = cl.head;
		while (pNode != nullptr) {
			Client* pc = pNode->indirectObject;
			append(*pc);
			pNode = pNode->link;
		}
	}
	return *this;
}

// Copy Constructor
ClientList::ClientList(const ClientList& cl) : head(0), current(0), count(0) {
	ClientNode* pNode;
	Client* pc;
	int n = cl.count;
	pNode = cl.head;
	for (int i = 0; i < n; i++) {
		pc = pNode->indirectObject;
		this->append(*pc);
		pNode = pNode->link;
	}

	//Handling the current node
	if (cl.current != nullptr) {
		pNode = cl.head;
		ClientNode* newCurrentNode = this->head;
		for (int i = 0; pNode != nullptr && pNode != cl.current; i++) {
			pNode = pNode->link;
			if (newCurrentNode != nullptr) { 
				newCurrentNode = newCurrentNode->link;
			}
			else {
				break;
			}
		}
		this->current = newCurrentNode;
	}
}

