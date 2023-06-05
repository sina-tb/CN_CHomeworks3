#ifndef _BGP_HPP_
#define _BGP_HPP_

#include <vector>
#include <string>

class Provider;
class Customer;

using namespace std;


class BGP
{
private:
    vector<Provider*> _providerList; // Multihomed/Transit AS
    vector<Customer*> _customerList; // Stub AS
    vector<Customer*> _potentialCustomers;

public:
    BGP();
    ~BGP();
    void runBGP();
    void handleInput(string input);
    void bgpAddProvider();
    void bgpAddCustomer();
    void bgpAssignProviderCustomer();
    void bgpPrintProviders();
    void bgpPrintCustomers();
    void bgpPrintSubscribers();
    void bgpPrintCustomerProviders();
    void bgpAddPeer();
    void bgpPrintPeers();
    void bgpAdvertise();
    bool isNewIDAddable(string prID);
    Customer* getCustomerByID(string csID);
    Provider* getProviderByID(string prID);
    Customer* getPotentialCustomerByID(string id);
};

#endif