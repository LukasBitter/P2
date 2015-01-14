#ifndef IDENTITYTOKEN_H
#define IDENTITYTOKEN_H

namespace GameComponent {
    class IdentityToken;
}

/**
  @class IdentityToken
 * @brief Attribue a l'objet un identifiant unique
 */
class IdentityToken
{
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    IdentityToken();

    /*ASSESSEUR / MUTATEUR*/
    /**
     * @brief A n'utiliser que dans un context de
     * mise à jour. Afin d'attribuer un nouvel identifiant
     * utiliser plutot la méthode setNextId
     */
    void setId(int i);
    ///Retourne l'identifiant de l'objet
    int getId() const;
    ///Défini l'identifiant avec le suivant disponible
    void setNextId();
private:
    int id; ///< Identifiant unique de l'objet
};

#endif // IDENTITYTOKEN_H
