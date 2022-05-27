//
// Created by robin on 20-May-22.
//

#include "CharacterStats.h"


CharacterStats::CharacterStats(CharacterType characterType, float health, float moveSpeed,
                               CharacterType attackTarget, float attackDamage, float attackSpeed,
                               float attackRange)
        : characterType(characterType), health(health), moveSpeed(moveSpeed),
          AttackTarget(attackTarget), AttackDamage(attackDamage), attackSpeed(attackSpeed),
          attackRange(attackRange){}
