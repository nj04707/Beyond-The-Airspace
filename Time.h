#pragma once
#include <SDL.h>
#include <iostream>

class Time
{
private:
    Uint32 current_time;

public:
    Time();

    Uint32 get_Time();      //get SDL_Ticks

    bool check_Time(Uint32);       //get the number of ticks between events

    void Time_Delay(Uint32);        //gets a delay between events
};