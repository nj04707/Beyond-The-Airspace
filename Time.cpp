#include "Time.h"

Time::Time()
{
    current_time = 0;
}

Uint32 Time::get_Time()
{
    current_time = SDL_GetTicks();
    //std::cout << current_time << std::endl;
    return current_time;
}

bool Time::check_Time(Uint32 second_time)
{
    Uint32 temp = this->get_Time();
    if ((temp > second_time - 100) && (temp < second_time))
    {
        return true;
    }
    return false;
}

void Time::Time_Delay(Uint32 delay)
{
    SDL_Delay(delay);
}