#ifndef _PROVIDER_HPP_
#define _PROVIDER_HPP_

#include <vector>
#include <string>
#include <map>

class Customer;

#include "Customer.hpp"

using namespace std;

// a provider can have providers
// also customer of a provider can be a provider
class Provider : public Customer 
{
private:

    vector<Customer*> _customers;
    vector<Provider*> _peers;
    std::map<string, pair<int, int> > _cstmLengthPref; 
    std::map<string, pair<int, int> > _peerLengthPref;

public:

    Provider();
    Provider(string id);
    Provider(Provider* provider, string id);
    ~Provider();
    Customer* addCustomer(Customer* customer);
    bool customerExists(Customer* customer);
    bool peerExists(Provider* provider);
    void printSubscribers();
    void printPeers();
    void addCustomerLengthPref(Customer* customer,
        string length, string pref);
    void addPeerLenghtPref(Provider* prv,
        string length, string pref);
    Provider* addPeer(Provider* peerPrv);

};

#endif