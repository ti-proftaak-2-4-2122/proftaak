//
// Created by tjtle on 13/06/2022.
//

#ifndef PROFTAAK24_INPUTHANDLER_H
#define PROFTAAK24_INPUTHANDLER_H


#include <vector>
#include <map>
#include <iostream>
#include <functional>
#include "GLFW/glfw3.h"

struct InputState {
    int keycode;
    int keyaction;
};

/**
 * @class InputHandler manages all the GLFW key callbacks that are added within the environment.
 * Also abides by the singleton structure
 */
class InputHandler
{
public:
    static InputHandler& getSingleton()
    {
        if(!singleton)
        {
            singleton = new InputHandler();
        }

        return *singleton;
    }

    void check_keys(int key, int action);
    void Init();
    void AddCallback(int keycode, int keyaction, const std::function<void()>& callback);
private:
    inline static InputHandler* singleton = nullptr;
    std::map<InputState*, std::function<void()>> inputCallbacks;
};


#endif //PROFTAAK24_INPUTHANDLER_H
