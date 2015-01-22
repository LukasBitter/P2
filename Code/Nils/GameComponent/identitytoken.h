#ifndef IDENTITYTOKEN_H
#define IDENTITYTOKEN_H

namespace GameComponent
{
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
    ///@warning Utiliser UNIQUEMENT en cas de mise
    /// à jour, préférer setNextId sinon
    void setId(int i);
    int getId() const;
    ///@brief Prend comme ID l'ID libre suivant
    void setNextId();
private:
    int id; ///< Identifiant unique de l'objet
};

#endif // IDENTITYTOKEN_H
