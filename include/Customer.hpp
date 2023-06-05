#ifndef _CUSTOMER_HPP_
#define _CUSTOMER_HPP_

#include <string>
#include <vector>

#include "Provider.hpp"

class Customer
{
protected:
    vector<Provider*> _providers;
    string ASID;

public:
    Provider* addProvider(Provider* prv);
    Customer();
    Customer(Provider* provider, string id);
    ~Customer();
    bool providerExists(Provider* prv);

};

#endif