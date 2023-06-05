#include "./include/Customer.hpp"
#include "./include/Provider.hpp"

#include <iostream>

const string PRV_ALRDY_EXST = "This provider is already the provider for this customer\n";

Customer::Customer() 
{   }

Customer::Customer(string id)
    : ASID(id)
{   }

Customer::Customer(Provider* provider, string id)
    : ASID(id)
{
    _providers.push_back(provider); 
}

Customer::~Customer()
{   }

bool Customer::providerExists(Provider* prv)
{
    for(Provider* p : _providers)
    {
        if(prv->ASID == p->ASID)
        {
            return true;
        }
    }
    return false;
}

Provider* Customer::addProvider(Provider* prv)
{
    if(!providerExists(prv))
    {
        _providers.push_back(prv);
        return prv;
    }
    else
    {
        cout << PRV_ALRDY_EXST;
        return nullptr;
    }
}

string Customer::getASID()
{
    return ASID;
}