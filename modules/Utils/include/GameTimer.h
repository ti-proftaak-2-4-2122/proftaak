/**
 * @file
 * @brief Header file for the GameTimer class
 * @author Ewout
 * @date 24-05-2022
 */

#pragma once

/**
 * @brief Class for keeping track of the time between 2 frames
 */
class GameTimer
{
private:
    inline static double currentTime = 0.0f;
    inline static float deltaTime = 0.0f;

public:

    /**
     * Updates the start time of the current frame and calculates the delta time
     * @param time Time in seconds, must be a timestamp or offset from the start of the program
     */
    static void update(double time);

    /**
     * Resets the GameTimer to 0
     */
    static void reset();

    /**
     * Gets the start time of the current frame
     * @return Time in seconds
     */
    static double getCurrentTime();

    /**
     * Gets the delta time between the previous and the current frame
     * @return Time in seconds
     */
    static float getDeltaTime();

};
