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
10) End the simulation\n";

const string BGP_ENDED = "Simulation has been Finished\n";
const string TXT_DEL = "~~~~~~~~~~~~\n";

// Error
const string BGP_MNU_ERR = "Error! Your input is not correct\n";
const string PRV_EXIST_ERR = "Error! A Provider by this ID Already exists!\n";
const string CUS_EXIST_ERR = "Error! A Customer by this ID Already exists!\n";
const string NO_PRV_ERR = "Error! Provider by this ID does not exist\n";
const string NO_ID_ERR = "Error! no AS by this ID exist!\n";

// Help/Guide
const string HLP = "Hint:\n";
const string HLP_ADD_PRV = HLP + "<ASID> and then press enter\n";
const string HLP_ADD_CUSTMR = HLP + "<ASID> and then press enter\n";
const string HLP_ASGN_PRV_CUSTMR = HLP + 
"Provider: <Provider's ASID> and then press enter\n\
Customer: <Customer's ASID> and then press enter\n";
const string HLP_SHW_SUB = HLP + "<Provider's ASID> and then press enter\n";
const string HLP_CUS_PRV = HLP + "<Customer's ASID> and then press \
enter.\nAlso note that A Provider can be a customer as well\n";

// Successful
const string SUC_ADD_PRV = "Provider has been added successfully!\n";
const string SUC_ADD_CUS = "Customer has been added successfully!\n";
const string SUC_ASGN_CUS_PRV = "Customer has been subscribed to provider successfully!\n";

enum MNU_OPT
{
    ADD_PRV = 1,
    ADD_CUSTOMER = 2,        // input is incorrect
    CUST_TO_PRV = 3,
    ADD_PEER = 4,
    ADV = 5,
    SHW_PRV = 6,
    SHW_CUS = 7,
    SHW_SUB = 8,
    SHW_CUS_S_PRV = 9,
    SIM_END = 10,
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

    }
    else if(input == to_string(ADV))
    {
        // Advertise suggesting routing table
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
    }
    else
    {
        cout << "Here's Customer: " <<
            inp << " list of providers\n";
        cs->printCustomerProviders();
    }
}