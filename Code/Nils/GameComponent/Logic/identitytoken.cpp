#include "identitytoken.h"

/*----------------------------------------------------*/
/*METHODE DE CLASSE*/
/*----------------------------------------------------*/

int currentID = 1;

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

IdentityToken::IdentityToken() : id(0)
{
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

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
