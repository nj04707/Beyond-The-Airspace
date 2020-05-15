#include "GameObject.h"

class Enemy : public GameObject
{
private:
    int health = 150; //
    int xpos;         //basic attributes of an enemy plane
    int ypos;         //

public:
    Enemy();

    void init(Manager *m, std::string id); //initialize components

    void setXY(); //update the position of plane

    void take_damage(int damage); //decrease health of the plane

    int get_health(); //gets the health of the plane
};