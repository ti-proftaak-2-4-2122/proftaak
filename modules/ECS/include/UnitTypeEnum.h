//
// Created by Daan van Donk on 01/06/2022.
//

#ifndef PROFTAAK24_UNITTYPEENUM_H
#define PROFTAAK24_UNITTYPEENUM_H

/**
 * @brief Type enum for all available units
 * @FAST Unit type that attacks fast, but in return has lower attack damage
 * @SLOW Unit type that attacks slow, but in return has high attack damage
 * @LAND Unit type that is a balance between the first 2 units.
 * @TOWER Unit type that is an objective for all other units to destroy,
 * this Unit has high damage with decent attack speed to not instantly die,
 * to other unit types.
 */

enum UnitTypeEnum {
    FAST,
    SLOW,
    LAND,
    TOWER,
    DUMMY_UNIT,
};

/**
 * @brief Function that Returns a string of the current Unit type, to work around enumeration
 * @param v Unit type that is to be printed to console
 * @return Returns the string of the corresponding unit type
 */
inline const char* ToString(UnitTypeEnum v)
{
    switch (v)
    {
        case FAST: return "Fast";
        case SLOW: return "Slow";
        case LAND: return "Land";
        case TOWER: return "Tower";
        default:   return "[Unknown Unit Type]";
    }
}
#endif //PROFTAAK24_UNITTYPEENUM_H
