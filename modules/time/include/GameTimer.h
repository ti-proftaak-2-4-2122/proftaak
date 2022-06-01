/**
 * @file
 * @brief Header file for the GameTimer class
 * @author Ewout
 * @date 24-05-2022
 */

#ifndef GAMETIMER_H
#define GAMETIMER_H

class GameTimer
{
private:
    inline static double lastTime = 0;

public:
    inline static float deltatime = 0.0f;

    static void update(double time);

};


#endif // GAMETIMER_H