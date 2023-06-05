#ifndef _PROVIDER_HPP_
#define _PROVIDER_HPP_

#include <vector>
#include <string>

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

public:

    Provider();
    Provider(string id);
    Provider(Provider* provider, string id);
    ~Provider();
    Customer* addCustomer(Customer* customer);
    bool customerExists(Customer* customer);
    void printSubscribers();

};

#endif