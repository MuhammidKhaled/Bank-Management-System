#include "clientstatistics.h"
#include <limits>

// Modifiers Members:
void ClientStatistics::attachClientList(ClientList& cl) {
    cLoc = &cl;
}

void ClientStatistics::setAccountFlag(int on) {
    if (on == 1 || on == 0) {
        aFlag = on;
    }
}

double ClientStatistics::total() {
    double sum = 0.0;
    if (cLoc != nullptr) {
        for (int i = 0; i < cLoc->size(); ++i) {
            Client* client = (*cLoc)[i];
            if (client != nullptr) {
                sum += client->retrieveBalance();
            }
        }
    }
    return sum;
}

int ClientStatistics::numberOfClients() {
    if (cLoc != nullptr) {
        return cLoc->size();
    }
    return 0;
}

double ClientStatistics::average() {
    double totalSum = total();
    int numClients = numberOfClients();
    return numClients > 0 ? totalSum / numClients : 0.0;
}

double ClientStatistics::minimum() {
    double min = std::numeric_limits<double>::infinity(); 
    if (cLoc != nullptr) {
        for (int i = 0; i < cLoc->size(); ++i) {
            Client* client = (*cLoc)[i];
            if (client != nullptr) {
                double value = aFlag == 1 ? client->retrieveBalance() : client->totalWorth();
                if (value < min) {
                    min = value;
                }
            }
        }
    }
    return min != std::numeric_limits<double>::infinity() ? min : 0.0;
}

double ClientStatistics::maximum() {
    double max = -std::numeric_limits<double>::infinity(); 
    if (cLoc != nullptr) {
        for (int i = 0; i < cLoc->size(); ++i) {
            Client* client = (*cLoc)[i];
            if (client != nullptr) {
                double value = aFlag == 1 ? client->retrieveBalance() : client->totalWorth();
                if (value > max) {
                    max = value;
                }
            }
        }
    }
    return max != -std::numeric_limits<double>::infinity() ? max : 0.0;
}


ClientStatistics::ClientStatistics(ClientList& cl) : cLoc(&cl), aFlag(1), pFlag(0), n(0) {}

ClientStatistics::ClientStatistics() : cLoc(nullptr), aFlag(1), pFlag(0), n(0) {}
