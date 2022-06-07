//
// Created by Ewout on 1-6-2022.
//

#ifndef PROFTAAK24_GUI_H
#define PROFTAAK24_GUI_H

#include "Component.h"
#include "glad/glad.h"

class GameObject;

class Gui : public Component
{
private:
    GLuint fontTxId;



public:
    void Draw() override;

    Gui();

};


#endif //PROFTAAK24_GUI_H
