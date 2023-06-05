#include "./include/Customer.hpp"

Customer::Customer() 
    : _provider(nullptr)
{   }

Provider* Customer::setProvider(Provider* prv)
{
    _provider = prv;
    return prv;
}