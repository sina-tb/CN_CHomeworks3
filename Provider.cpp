#include "./include/Provider.hpp"

#include <iostream>

const string NULL_ASGN_P = "Can not assign a null Provider object\n";
const string CSTMR_ALRDY_EXST = "This customer is already subscribed to provider\n";


Provider::Provider()
{   }

Provider::Provider(string id)
    : Customer(id)
{   }

Provider::Provider(Provider* provider, string id)
    : Customer(provider, id)
{   }

Provider::~Provider()
{   }

Customer* Provider::addCustomer(Customer* customer)
{
    if(customer == nullptr)
    {
        cout << NULL_ASGN_P;
        return nullptr;
    }
    if(!customerExists(customer))
    {
        _customers.push_back(customer);
        return customer;
    }
    else
    {
        cout << CSTMR_ALRDY_EXST;
        return customer;
    }
}

bool Provider::customerExists(Customer* customer)
{
    for(Customer* cs : _customers)
    {
        if(cs->getASID() == customer->getASID())
        {
            return true;
        }
    }
    return false;
}

void Provider::printSubscribers()
{
    if(_customers.empty())
    {
        cout << "There are no subscribers for this provider!\n";
        return;
    }
    for(Customer* cus : _customers)
    {
        cout << cus->getASID() << endl;
        cout << "~~~~~~~~~~~~\n";
    }
}