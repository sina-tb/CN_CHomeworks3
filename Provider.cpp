#include "./include/Provider.hpp"

Provider::Provider()
    {   }

Provider::Provider(Provider* provider, string id)
    : Customer(provider, id)
    {   }

Provider::~Provider()
    {   }