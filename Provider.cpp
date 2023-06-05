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

bool Provider::isRouteInProvider(string routeASID)
{
    if(_cstmLengthPref.count(routeASID) <= 0
        && _routeTable.count(routeASID) <= 0)
    {
        return false;
    }
    return true;
}

bool Provider::isRelated(Provider* prv)
{
    for(Provider* p : _peers)
    {
        if(prv->ASID == p->ASID)
        {
            return true;
        }
    }

    for(Customer* c : _customers)
    {
        if(c->getASID() == prv->ASID)
        {
            return true;
        }
    }
    return false;
}

bool Provider::checkRouteSource(string routeASID,
    string sourceASID)
{
    // announcing route is not even in routeTable 
    if(!isRouteInProvider(routeASID)) 
    {
        return true;
    }
    else
    {
        if(_routeTable.count(routeASID) > 0)
        {
            if(_routeTable[routeASID].first != sourceASID)
            {
                return false;
            }
        }
        // route is actually a customer
        if(_cstmLengthPref.count(routeASID) > 0) 
        {
            if(routeASID != sourceASID)
            {
                return false;
            }
        }
        return true;
    }
}

bool Provider::checkAdvertisedLenght(string route, string length)
{
    if(_cstmLengthPref.count(route) > 0)
    {
        if(to_string(_cstmLengthPref[route].first) == length)
        {
            return true;
        }
        return false;
    }
    else if(_routeTable.count(route) > 0)
    {
        if(to_string(_routeTable[route].second) == length)
        {
            return true;
        }
        return false;
    }
    else
    {
        return false;
    }
}

void Provider::addToRoutingTable(string src
    , string route, string length)
{
    int len;
    try
    {
        len = stoi(length);
    }
    catch(...)
    {
        cout << "Length must be an Integer literal\n";
        return;
    }
    _routeTable[route] = 
        pair<string, int>(src, len);
}