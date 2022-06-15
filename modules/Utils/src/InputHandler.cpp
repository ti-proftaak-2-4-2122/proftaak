//
// Created by tjtle on 13/06/2022.
//

#include "InputHandler.h"

void InputHandler::check_keys(int key, int action)
{
    for(auto const& [input, callback] : inputCallbacks) {
        if(key == input->keycode && action == input->keyaction) {
            callback();
        }
    }
}

void InputHandler::AddCallback(int keycode, int keyaction, const std::function<void()>& callback)
{
    auto* inputState = new InputState{keycode, keyaction};
    inputCallbacks.insert({inputState, callback});
}

void InputHandler::Init()
{

}


