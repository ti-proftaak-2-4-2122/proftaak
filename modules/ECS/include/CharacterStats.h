//
// Created by Daan van Donk on 24/05/2022.
//

#ifndef PROFTAAK24_CHARACTERSTATS_H
#define PROFTAAK24_CHARACTERSTATS_H
struct CharacterStats : public Component
{
    float range;
    float health;
    float damage;
    float moveSpeed;

    CharacterStats(float range, float health, float damage, float moveSpeed) : range(range),
                                                                               health(health),
                                                                               damage(damage),
                                                                               moveSpeed(
                                                                                       moveSpeed) {}
};
#endif //PROFTAAK24_CHARACTERSTATS_H
