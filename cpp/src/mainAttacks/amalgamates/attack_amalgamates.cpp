#include "attack_amalgamates.h"
#include "env.h"

AttackAmalgamates::AttackAmalgamates() {}

AttackAmalgamates::~AttackAmalgamates() {}

void AttackAmalgamates::_bind_methods() {
}

void AttackAmalgamates::ready() {
    ResourceLoader* loader = ResourceLoader::get_singleton();
    scene_dogmissle = loader->load("res://Game/encounters/Bullets/dogmissle.tscn");
    scene_nofacedog = loader->load("res://Game/encounters/Bullets/nofacedog.tscn");
}

void AttackAmalgamates::start_attack() {
    if(type == Endogeny)
        attack_endogeny();
}

void AttackAmalgamates::set_type(AmalgamatesType value) {
    type = value;
}

DefaultBullet* AttackAmalgamates::create_dogmissle(Masking type) {
    DefaultBullet* dogmissle = Object::cast_to<DefaultBullet>(scene_dogmissle->instantiate());
    add_bullet(dogmissle, type);
    return dogmissle;
}

Nofacedog* AttackAmalgamates::create_nofacedog(Masking type, int mode) {
    Nofacedog* nofacedog = Object::cast_to<Nofacedog>(scene_nofacedog->instantiate());
    add_bullet(nofacedog, type);
    return nofacedog->set_mode(mode);
}