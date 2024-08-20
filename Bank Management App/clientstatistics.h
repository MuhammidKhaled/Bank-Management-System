#ifndef CLIENTSTATISTICS_H
#define CLIENTSTATISTICS_H

#include "clientlist.h"

class ClientStatistics {
public:
// Modifiers Members:
	void attachClientList(ClientList& cl);
	void setAccountFlag(int on);
	/* If on is 1 then accounts will be included in analysis;
	if on is 0 then portfolios are not included.*/
// Implementor Members:
		/* All of the implementor members assume that the ClientStatistics object has
		an associated ClientList, either through the one-parameter constructor or via
		previous attachClientList() message.*/
	double total();
	double average();
	double minimum();
	double maximum();
	int numberOfClients();
// Backbone Members:
	ClientStatistics(ClientList& cl);
	ClientStatistics();
private:
	ClientList* cLoc; // points to the associated ClientList.
	int aFlag, pFlag; // signals which components to count
	int n;            // number of clients
};
#endif // !CLIENTSTATISTICS_H


