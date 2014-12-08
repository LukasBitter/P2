#ifndef NODE_H
#define NODE_H

class Gamer;

class Node : public Updatable
{
public:
    Node();
    Node(int x, int y);
    Node(Node *n);
    ~Node();
    double getNbRessources();
    double getRessourcesRate();
    int getPosY();
    int getPosX();
    Gamer* getOwner();
    vod setRessourcesRate(double r);
    void setNbRessources(double r);
    void setOwner(Gamer *g);
    void tic();

private:
    double nbRessources;
    double ressourcesRate;
    int posX;
    int posY;
    Gamer *owner;

};

#endif // NODE_H
