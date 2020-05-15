#pragma once
 #include "ECS.h"

 class PositionComponent:public Component
 {
private :
    int xpos;
    int ypos;
public:
    int x(){return xpos;}
    int y(){return ypos;}
    virtual void init()
    {//used virtual instead of override
        xpos=0;
        ypos=0;
    }
    virtual void update()
    {
        xpos++;
        ypos++;
        
    }

    void setPos(int x , int y)
    {
        xpos=x;
        ypos=y;
    }

 };