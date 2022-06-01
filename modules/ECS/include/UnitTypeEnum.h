//
// Created by Daan van Donk on 01/06/2022.
//

#ifndef PROFTAAK24_UNITTYPEENUM_H
#define PROFTAAK24_UNITTYPEENUM_H
enum UnitTypeEnum {
    AIR,
    GROUND,
    LAND,
    TOWER,
};

inline const char* ToString(UnitTypeEnum v)
{
    switch (v)
    {
        case AIR:   return "Air";
        case GROUND:   return "Ground";
        case LAND: return "Land";
        case TOWER: return "Tower";
        default:   return "[Unknown Unit Type]";
    }
}
#endif //PROFTAAK24_UNITTYPEENUM_H
