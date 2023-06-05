#ifndef _BGP_HPP_
#define _BGP_HPP_

#include <vector>
#include <string>

class Provider;
class Customer;

using namespace std;


class BGP
{
private:
    vector<Provider*> _providerList; // Multihomed/Transit AS
    vector<Customer*> _customerList; // Stub AS

public:
    BGP();
    ~BGP();
    void runBGP();
    void handleInput(string input);
    void bgpAddProvider();
    bool isNewIDAddable(string prID);
};

#endif