#include "./include/Provider.hpp"

#include <iostream>

const string NULL_ASGN_P = "Can not assign a null Provider object\n";
const string CSTMR_ALRDY_EXST = "This customer is already subscribed to provider\n";
const string PER_ALRDY_EXST = "This Provider is already in peer with provider\n";

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

bool Provider::peerExists(Provider* peerPrv)
{
    if(_providers.empty())
    {
        return false;
    }
    for(Provider* p : _peers)
    {
        if(p->ASID == peerPrv->ASID)
        {
            return true;
        }
    }
    return false;
}

void Provider::printPeers()
{
    if(_peers.empty())
    {
        cout << "There are no peers for this provider\n";
        return;
    }
    for(Provider* p : _peers)
    {
        cout << p->ASID << endl;
        cout << "~~~~~~~~~~~~\n";
    }
}

Provider* Provider::addPeer(Provider* pprv)
{
    if(peerExists(pprv))
    {
        cout << PER_ALRDY_EXST;
        return pprv;
    }
    else
    {
        _peers.push_back(pprv);
        return pprv;
    }
}

void Provider::addCustomerLengthPref(Customer* customer,
    string length, string pref)
{
    try
    {
        _cstmLengthPref[customer->getASID()] = 
            pair<int, int>(stoi(length), stoi(pref));
    }
    catch(...)
    {
        cout << "length and pref must be integers" << endl;
    }
}

void Provider::addPeerLenghtPref(Provider* prv,
    string length, string pref)
{
    try
    {
        _peerLengthPref[prv->getASID()] = 
            pair<int, int>(stoi(length), stoi(pref));
    }
    catch(...)
    {
        cout << "length and preference must both be integers\n";
    }
 
}