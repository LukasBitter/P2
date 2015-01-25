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
    /**
     * @brief setId Défini l'ID de l'objet
     * @param i ID voulu
     * @warning Utiliser UNIQUEMENT en cas de mise à jour, préférer setNextId sinon
     */
    void setId(int i);

    /**
     * @brief getId Retourne l'ID de l'objet
     */
    int getId() const;

    /**
     * @brief setNextId Prend comme ID l'ID libre suivant
     */
    void setNextId();
private:
    int id; ///< Identifiant unique de l'objet
};

#endif // IDENTITYTOKEN_H
