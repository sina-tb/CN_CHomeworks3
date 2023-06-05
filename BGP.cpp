#include "./include/BGP.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "./include/Provider.hpp"
#include "./include/Customer.hpp"

// Default Strings
const string BGP_MNU = 
"Press one of the following options:\n\
1) Add a provider\n\
2) Add a customer\n\
3) Assign a customer to a provider\n\
4) Define a relation between two providers(peer)\n\
5) Advertise a routing from one AS to another\n\
6) Show list of all Providers\n\
7) Show list of all Customers\n\
8) Show list of Subscribers for a Provider\n\
9) Show list of Providers for a Customer\n\
10) Show list of peers for a provider\n\
11) End the simulation\n";

const string BGP_ENDED = "Simulation has been Finished\n";
const string TXT_DEL = "~~~~~~~~~~~~\n";

// Error
const string BGP_MNU_ERR = "Error! Your input is not correct\n";
const string PRV_EXIST_ERR = "Error! A Provider by this ID Already exists!\n";
const string CUS_EXIST_ERR = "Error! A Customer by this ID Already exists!\n";
const string NO_PRV_ERR = "Error! Provider by this ID does not exist\n";
const string NO_ID_ERR = "Error! no AS by this ID exist!\n";
const string NO_ROUTE = "Error! advertising route is not in the advertiser(Provider)\n";
const string NO_RLT = "Error! two unrelated AS can not advertise to each other\n";
const string HIJACK = "Error! traffic has been Hijacked!\n";
const string ILLEGAL_LEN = "Error! Lenght provided for this path is not correct\n";

// Help/Guide
const string HLP = "Hint:\n";
const string HLP_ADD_PRV = HLP + "<ASID> and then press enter\n";
const string HLP_ADD_CUSTMR = HLP + "<ASID> and then press enter\n";
const string HLP_ASGN_PRV_CUSTMR = HLP + 
"Provider: <Provider's ASID> and then press enter\n\
Customer: <Customer's ASID> and then press enter\n\
Length: <Length of connection> and then press enter\n\
Preference: <Connection Priority> (higher better)\n";
const string HLP_SHW_SUB = HLP + "<Provider's ASID> and then press enter\n";
const string HLP_CUS_PRV = HLP + "<Customer's ASID> and then press \
enter.\nAlso note that A Provider can be a customer as well\n";
const string HLP_ADD_PER = HLP + 
"Provider1: <First Provider's ASID> and then press enter\n\
Provider2: <Second Provider's ASID> and then press enter\n\
Length: <Length of connection> and then press enter\n\
Preference: <Connection Priority> (higher better)\n";
const string HLP_SHW_PER = HLP + "<Provider's ASID> and then press enter\n";
const string HLP_ADVRT = HLP + 
"Provider: <Advertising Provider's ASID>\n\
Destination: <Advertisemnet Receiver Provider's>\n\
Route: <Advertising route ASID>\n\
Length: <Path Length>\n"; // technically prefix

// Successful
const string SUC_ADD_PRV = "Provider has been added successfully!\n";
const string SUC_ADD_CUS = "Customer has been added successfully!\n";
const string SUC_ASGN_CUS_PRV = "Customer has been subscribed to provider successfully!\n";
const string SUC_ADD_PER = "Prvoiders 1 & 2 are now peers!\n";

enum MNU_OPT
{
    ADD_PRV = 1,
    ADD_CUSTOMER = 2,        // input is incorrect
    CUST_TO_PRV = 3,
    ADD_PEER = 4,
    ADVRT = 5,
    SHW_PRV = 6,
    SHW_CUS = 7,
    SHW_SUB = 8,
    SHW_CUS_S_PRV = 9,
    SHW_PEER = 10,
    SIM_END = 11,
};

using namespace std;

BGP::BGP()
{   }

BGP::~BGP()
{   }

void BGP::runBGP()
{
    while(1)
    {
        cout << BGP_MNU;
        string inp;
        std::getline(std::cin, inp);
        if(inp == to_string(SIM_END))
        {
            break;
        }
        handleInput(inp);
    }
    cout << BGP_ENDED;
}

void BGP::handleInput(string input)
{
    if(input == to_string(ADD_PRV))
    {
        bgpAddProvider();
    }
    else if(input == to_string(ADD_CUSTOMER))
    {
        bgpAddCustomer();
    }
    else if(input == to_string(CUST_TO_PRV))
    {
        bgpAssignProviderCustomer();

    }
    else if(input == to_string(ADD_PEER))
    {
        bgpAddPeer();
    }
    else if(input == to_string(ADVRT))
    {
        bgpAdvertise();
    }
    else if(input == to_string(SHW_PRV))
    {
        bgpPrintProviders();
    }
    else if(input == to_string(SHW_CUS))
    {
        bgpPrintCustomers();
    }
    else if(input == to_string(SHW_SUB))
    {
        bgpPrintSubscribers();
    }
    else if(input == to_string(SHW_CUS_S_PRV))
    {
        bgpPrintCustomerProviders();
    }
    else if(input == to_string(SHW_PEER))
    {
        bgpPrintPeers();   
    }
    else
    {
        cout << BGP_MNU_ERR;
    }
}

void BGP::bgpAddProvider()
{
    cout << HLP_ADD_PRV;
    string inp;
    std::getline(cin, inp);
    if(isNewIDAddable(inp))
    {
        Provider* newPrv = new Provider(inp);
        _providerList.push_back(newPrv);
        _potentialCustomers.push_back(newPrv);
        cout << SUC_ADD_PRV;
    }
}

bool BGP::isNewIDAddable(string prID)
{
    for(Provider* iprv : _providerList)
    {
        if(prID == iprv->getASID())
        {
            cout << PRV_EXIST_ERR;
            return false;
        }
    }
    for(Customer* cus : _customerList)
    {
        if(prID == cus->getASID())
        {
            cout << CUS_EXIST_ERR;
            return false;
        }
    }
    return true;
}

void BGP::bgpAddCustomer()
{
    cout << HLP_ADD_CUSTMR;
    string inp;
    std::getline(std::cin, inp);
    if(isNewIDAddable(inp))
    {
        Customer* newCus = new Customer(inp);
        _customerList.push_back(newCus);
        _potentialCustomers.push_back(newCus);
        cout << SUC_ADD_CUS;
    }
}

Customer* BGP::getCustomerByID(string csID)
{
    if(_customerList.empty())
    {
        return nullptr;
    }
    for(auto csIt = _customerList.begin();
        csIt != _customerList.end();
        csIt++)
    {
        if((*csIt)->getASID() == csID)
        {
            return (*csIt);
        }
    }
    return nullptr;
}

Provider* BGP::getProviderByID(string prID)
{
    if(_providerList.empty())
    {
        return nullptr;
    }
    for(auto pIt = _providerList.begin();
        pIt != _providerList.end();
        pIt++)
    {
        if((*pIt)->getASID() == prID)
        {
            return (*pIt);
        }
    }
    return nullptr;
}

Customer* BGP::getPotentialCustomerByID(string id)
{
    if(_potentialCustomers.empty())
    {
        return nullptr;
    }
    for(auto idIt = _potentialCustomers.begin();
        idIt != _potentialCustomers.end();
        idIt++)
    {
        if((*idIt)->getASID() == id)
        {
            return (*idIt);
        }
    }
    return nullptr;
}

void BGP::bgpAssignProviderCustomer()
{
    cout << HLP_ASGN_PRV_CUSTMR;
    cout << "Provider: ";
    string prASID, cusASID;
    std::getline(std::cin, prASID);
    Provider* provider = getProviderByID(prASID);
    if(provider == nullptr)
    {
        cout << NO_PRV_ERR;
        return;
    }
    cout << "Customer: ";
    std::getline(std::cin, cusASID);
    Customer* customer = getPotentialCustomerByID(cusASID);
    if(customer == nullptr)
    {
        cout << NO_ID_ERR;
        return;
    }
    customer
            ->addProvider(provider)
            ->addCustomer(customer);
    string pathLength, pathPref;
    cout << "Length: ";
    std::getline(std::cin, pathLength);
    cout << "Preference: ";
    std::getline(std::cin, pathPref);
    provider->addCustomerLengthPref(customer, pathLength, pathPref);
    cout << SUC_ASGN_CUS_PRV;
}

void BGP::bgpPrintProviders()
{
    cout << "Here's the list of all providers\n";
    for(Provider* prv : _providerList)
    {
        cout << prv->getASID() << std::endl;
        cout << TXT_DEL;
    }
}

void BGP::bgpPrintCustomers()
{
    cout << "Here's the list of all Stub customers\
    (not including providers)\n";
    for(Customer* cus : _customerList)
    {
        cout << cus->getASID() << std::endl;
        cout << TXT_DEL;
    }
}

void BGP::bgpPrintSubscribers()
{
    cout << HLP_SHW_SUB;
    string inp;
    std::getline(std::cin, inp);
    Provider* pr = getProviderByID(inp);
    if(pr == nullptr)
    {
        cout << NO_PRV_ERR;
    }
    else
    {
        cout << "Here's Provider: " <<
            inp << " list of subscribers\n";
        pr->printSubscribers();
    }
}

void BGP::bgpPrintCustomerProviders()
{
    cout << HLP_CUS_PRV;
    cout << HLP_SHW_SUB;
    string inp;
    std::getline(std::cin, inp);
    Customer* cs = getPotentialCustomerByID(inp);
    if(cs == nullptr)
    {
        cout << NO_ID_ERR;
        return;
    }
    else
    {
        cout << "Here's Customer: " <<
            inp << " list of providers\n";
        cs->printCustomerProviders();
    }
}

void BGP::bgpAddPeer()
{
    cout << HLP_ADD_PER;
    string prv_1, prv_2;
    cout << "Provider1: ";
    std::getline(std::cin, prv_1);
    Provider* ppr1 = getProviderByID(prv_1);
    if(ppr1 == nullptr)
    {
        cout << NO_PRV_ERR;
        return;
    }
    cout << "Provider2: ";
    std::getline(std::cin, prv_2);
    Provider* ppr2 = getProviderByID(prv_2);
    if(ppr2 == nullptr)
    {
        cout << NO_PRV_ERR;
        return;
    }
    ppr1
        ->addPeer(ppr2)
        ->addPeer(ppr1);
    string pathLenght, pathPref;
    cout << "Length: ";
    std::getline(std::cin, pathLenght);
    cout << "Preference: ";
    std::getline(std::cin, pathPref);
    ppr1->addPeerLenghtPref(ppr2, pathLenght, pathPref);
    ppr2->addPeerLenghtPref(ppr1, pathLenght, pathPref);
    cout << SUC_ADD_PER;
}

void BGP::bgpPrintPeers()
{
    cout << HLP_SHW_PER;
    string inp;
    std::getline(std::cin, inp);
    Provider* prv = getProviderByID(inp);
    if(prv == nullptr)
    {
        cout << NO_PRV_ERR;
        return;
    }
    else
    {
        prv->printPeers();
    }
}

void BGP::bgpAdvertise()
{
    cout << HLP_ADVRT;
    cout << "Provider: ";
    string adPrv, dstPrv, rtCustomer;
    std::getline(std::cin, adPrv);
    Provider* prv = getProviderByID(adPrv);
    if(prv == nullptr)
    {
        cout << NO_PRV_ERR;
        return;
    }
    cout << "Destination: ";
    std::getline(std::cin, dstPrv);
    Provider* dst = getProviderByID(dstPrv);
    if(dst == nullptr)
    {
        cout << NO_PRV_ERR;
        return;
    }
    if(!dst->isRelated(prv))
    {
        cout << NO_RLT;
        return;
    }
    cout << "Route: ";
    std::getline(std::cin, rtCustomer);
    Customer* rt = getPotentialCustomerByID(rtCustomer);
    if(rt == nullptr)
    {
        cout << NO_ID_ERR;
        return;
    }
    if(!prv->isRouteInProvider(rt->getASID()))
    {
        cout << NO_ROUTE;
        return;
    }
    if(!dst->checkRouteSource(rt->getASID(), prv->getASID()))
    {
        cout << HIJACK;
        return;
    }
    
    cout << "Length: ";
    string pathLength;
    std::getline(std::cin, pathLength);
    if(!dst->checkAdvertisedLenght(rt->getASID(), pathLength))
    {
        cout << ILLEGAL_LEN;
        return;
    }
    dst->addToRoutingTable(prv->getASID(), rt->getASID(), pathLength);
}