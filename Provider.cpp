#include "./include/Provider.hpp"

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