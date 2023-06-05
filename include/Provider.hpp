#ifndef _PROVIDER_HPP_
#define _PROVIDER_HPP_

#include <vector>
#include <string>

#include "Customer.hpp"


using namespace std;

class Provider
{
private:
    vector<Customer*> _customers;
    vector<Provider*> _peers;
    string prvID;

public:
    Provider();
    ~Provider();
};

#endif