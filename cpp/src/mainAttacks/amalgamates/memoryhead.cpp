#include "attack_amalgamates.h"
#include "env.h"

void AttackAmalgamates::attack_memoryhead() {
    sys->sleep([this]() { end_attack(); }, 1+get_attack_id());
}