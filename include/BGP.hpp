#ifndef _BGP_HPP_
#define _BGP_HPP_

#include <vector>

#include "Customer.hpp"
#include "Provider.hpp"

const string BGP_MNU = 
"Press one of the following options:\n\
1) Add a providern\n\
2) Add a customer\n\
3) Assign a customer to a provider\n\
4) Define a relation between two providers(peer)\n\
5) Advertise a routing from one AS to another\n";


class BGP
{
private:

    vector<Provider*> _providerList;
    vector<Customer*> _customer;


public:
    BGP();
    ~BGP();
};

BGP::BGP()
{
}

BGP::~BGP()
{
}

#endif