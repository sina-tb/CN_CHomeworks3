#ifndef _CUSTOMER_HPP_
#define _CUSTOMER_HPP_

#include <string>
#include <vector>


class Provider;

using namespace std;

class Customer
{
protected:

    vector<Provider*> _providers;
    string ASID;

public:

    Provider* addProvider(Provider* prv);
    Customer();
    Customer(string id);
    Customer(Provider* provider, string id);
    ~Customer();
    bool providerExists(Provider* prv);
    string getASID();
    void printCustomerProviders();

};

#endif