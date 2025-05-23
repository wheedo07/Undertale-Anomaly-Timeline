#include "attack_amalgamates.h"
using namespace godot;

AttackAmalgamates::AttackAmalgamates() {}

AttackAmalgamates::~AttackAmalgamates() {}

void AttackAmalgamates::_bind_methods() {}

void AttackAmalgamates::ready() {
    ResourceLoader* loader = ResourceLoader::get_singleton();
    scene_dogmissle = loader->load("res://Game/encounters/Bullets/dogmissle.tscn");
    scene_nofacedog = loader->load("res://Game/encounters/Bullets/nofacedog.tscn");
    scene_freakbullet = loader->load("res://Game/encounters/Bullets/freakbullet.tscn");
}

void AttackAmalgamates::start_attack() {
    if(type == Endogeny) {
        if(id == 1) 
            attack_endogeny_1();
        else if(id == 2)
            attack_endogeny_2();
    }else if(type == Memoryhead)
        attack_memoryhead();
}

void AttackAmalgamates::set_type(AmalgamatesType value, int id) {
    type = value;
    this->id = id;
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

Freakbullet* AttackAmalgamates::create_freakbullet(Masking type) {
    Freakbullet* freakbullet = Object::cast_to<Freakbullet>(scene_freakbullet->instantiate());
    add_bullet(freakbullet, type);
    return freakbullet;
}