#ifndef CLIENTLIST_H
#define CLIENTLIST_H

#include "client.h"

class ClientNode {
public:
	ClientNode();
	friend class ClientList;
private:
	Client* indirectObject;
	ClientNode* link;
};

class ClientList {
/* The ClientList class is an indirect container, A ClientList neither constructs nor
destroys its component objects.
   The consumer of a ClientList is responsible for ensuring that a Client component is not
   destroyed before being removed from a ClientList to which it belongs.
   The consumer is responsible for the destruction of the Client after its removal as a 
   component from a ClientList.
   */
public:
// Modifiers Members
	/* Member functions that add components to the list. the following members return 1 for
	success and 0 for failure. None of these methods duplicates its parameter, After these
	operations, the newely added client becomes the current one if the operation is
	successful, otherwise the current component doesn't change.*/
	int insert(Client& c);
	int append(Client& c);
	int insertBefore(Client& c);
	int insertAfter(Client& c);

	/* Member functions that remove components from the list. These members remove the
	Client component from the list, but do not destroy the Client. A return value of 1 
	indicates success and 0 failure. The component just after the one removed , then the
	first element becomes current. If the list is empty, then there is no current element.*/
	Client* remove();
	Client* remove(std::string ssn);

	void reset();
	void next();
	void previous();

// Accessor Members
	Client* retrieve(std::string ssn);
	Client* retrieve() const;
	Client* operator[](int i);

// Implementor Members
	int position() const;
	int end() const;
	int first() const;
	int size() const;

// Backbone Members
	ClientList& operator= (const ClientList& cl); 
	ClientList(const ClientList& cl); 
	ClientList();
	~ClientList();
private:
	ClientNode* head;     
	ClientNode* current;  
	int count;          
};
#endif // !CLIENTLIST_H

