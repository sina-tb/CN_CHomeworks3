#ifndef _PROVIDER_HPP_
#define _PROVIDER_HPP_

#include <vector>
#include <string>

#include "Customer.hpp"


using namespace std;

class Provider : public Customer
{
private:
    vector<Customer*> _customers;
    vector<Provider*> _peers;

public:
    Provider();
    Provider(Provider* provider, string id);
    ~Provider();

};

#endif