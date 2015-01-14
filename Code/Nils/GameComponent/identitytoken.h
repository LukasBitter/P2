#ifndef IDENTITYTOKEN_H
#define IDENTITYTOKEN_H

namespace GameComponent {
class IdentityToken;
}

/**
 * @class IdentityToken
 * @brief Attribue a l'objet un identifiant unique
 */
class IdentityToken
{
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    IdentityToken();

    /*ASSESSEUR / MUTATEUR*/
    void setId(int i);
    int getId() const;
    void setNextId();
private:
    int id;
};

#endif // IDENTITYTOKEN_H
