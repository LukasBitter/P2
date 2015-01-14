#include "identitytoken.h"

int currentID = 1;

IdentityToken::IdentityToken() : id(0)
{
}

void IdentityToken::setId(int i)
{
    this->id = i;
    if(currentID <= id) currentID = id+1;
}

int IdentityToken::getId() const
{
    return id;
}

void IdentityToken::setNextId()
{
    id = currentID;
    ++currentID;
}
