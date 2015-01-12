#ifndef IDENTITYTOKEN_H
#define IDENTITYTOKEN_H

namespace GameComponent {
    class IdentityToken;
}

class IdentityToken
{
public:
    IdentityToken();
    void setId(int i);
    int getId() const;
    void setNextId();
private:
    int id;
};

#endif // IDENTITYTOKEN_H
