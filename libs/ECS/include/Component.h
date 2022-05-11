//
// Created by Daan van Donk on 10/05/2022.
//

#ifndef PROFTAAK24_COMPONENT_H
#define PROFTAAK24_COMPONENT_H

class Component
{
public:
    virtual void Awake(){};
    virtual void Update(){};
    //Dont touch Draw method, is only for scenemanager
    virtual void Draw(){};
};


#endif //PROFTAAK24_COMPONENT_H
