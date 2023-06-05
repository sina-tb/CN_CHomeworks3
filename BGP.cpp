#include "./include/BGP.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "./include/Provider.hpp"
#include "./include/Customer.hpp"

// Default Strings
const string BGP_MNU = 
"Press one of the following options:\n\
1) Add a providern\n\
2) Add a customer\n\
3) Assign a customer to a provider\n\
4) Define a relation between two providers(peer)\n\
5) Advertise a routing from one AS to another\n\
6) End the simulation\n";

const string BGP_ENDED = "Simulation has been Finished\n";

// Error
const string BGP_MNU_ERR = "Error! Your input is not correct\n";
const string PRV_EXIST_ERR = "Error! A Provider by this ID Already exists!\n";
const string CUS_EXIST_ERR = "Error! A Customer by this ID Already exists!\n";

// Help/Guide
const string HLP = "Hint : ";
const string HLP_ADD_PRV = HLP + "<ASID> and then press enter";


enum MNU_OPT
{
    ADD_PRV = 1,
    ADD_CUSTOMER = 2,        // input is incorrect
    CUST_TO_PRV = 3,
    ADD_PEER = 4,
    ADV = 5,
    SIM_END = 6,
};

using namespace std;

BGP::BGP()
{   }

BGP::~BGP()
{   }

void BGP::runBGP()
{
    cout << BGP_MNU;
    while(1)
    {
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

    }
    else if(input == to_string(CUST_TO_PRV))
    {
        // Assign provider to customer
    }
    else if(input == to_string(ADD_PEER))
    {

    }
    else if(input == to_string(ADV))
    {
        // Advertise suggesting routing table
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
        _providerList.push_back(new Provider(inp));
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