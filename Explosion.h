#include "GameObject.h"

class Explosion : public GameObject
{
private:
public:
    Explosion();

    void init(float x, float y, Manager *m, std::string id); //initialze components
};