/**
 * @file
 * @brief Header file for the GameTimer class
 * @author Ewout
 * @date 24-05-2022
 */

#ifndef GAMETIMER_H
#define GAMETIMER_H

/**
 * @brief Class for keeping track of the time between 2 frames
 */
class GameTimer
{
private:
    inline static double lastTime = 0;

public:
    /**
     * Variable containing the delta time from the previous to the current frame
     */
    inline static float deltatime = 0.0f;

    /**
     * Updates the internal timer and delta time with the new time
     * @param time Time since program start or a timestamp.
     * Must be larger than internal timer and non-negative.
     */
    static void update(double time);

};


#endif // GAMETIMER_H