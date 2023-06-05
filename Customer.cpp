#include "./include/Customer.hpp"
#include "./include/Provider.hpp"

#include <iostream>

const string PRV_ALRDY_EXST = "This provider is already the provider for this customer\n";
const string NULL_ASGN_C = "Can not assign a null Customer object\n";

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
    if(prv == nullptr)
    {
        cout << NULL_ASGN_C;
        return nullptr;
    }
    if(!providerExists(prv))
    {
        _providers.push_back(prv);
        return prv;
    }
    else
    {
        cout << PRV_ALRDY_EXST;
        return prv;
    }
}

string Customer::getASID()
{
    return ASID;
}

void Customer::printCustomerProviders()
{
    if(_providers.empty())
    {
        cout << "There are no providers for this customer!\n";
        return;
    }
    for(Provider* pr : _providers)
    {
        cout << pr->ASID << endl;
        cout << "~~~~~~~~~~~~\n";
    }
}

void Customer::addProviderLengthPref(Provider* prv,
    string length, string pref)
{
    try
    {
        _prvLengthPref[prv->ASID] = 
            pair<int, int>(stoi(length), stoi(pref));
    }
    catch(...)
    {
        cout << "lenght and pref must be integers" << endl;
    }
}