#ifndef _CUSTOMER_HPP_
#define _CUSTOMER_HPP_

#include <string>

#include "Provider.hpp"

class Customer
{
private:

    Provider* _provider;
    string _customerID;

public:

    Provider* setProvider(Provider* prv);
    Customer();

};

#endif