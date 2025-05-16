#include "enemy_amalgamates.h"
#include "src/mainAttacks/amalgamates/attack_amalgamates.h"
#include "env.h"

Enemy_Amalgamates::Enemy_Amalgamates() {
    type = Endogeny;
}

Enemy_Amalgamates::~Enemy_Amalgamates() {}

void Enemy_Amalgamates::_bind_methods() {
    BIND_ENUM_CONSTANT(Endogeny);
    BIND_ENUM_CONSTANT(Memoryhead);
    BIND_ENUM_CONSTANT(Snowdrake);
    BIND_ENUM_CONSTANT(LemonBread);
    BIND_ENUM_CONSTANT(ReaperBird);

    ClassDB::bind_method(D_METHOD("set_amalgamates", "value"), &Enemy_Amalgamates::set_amalgamates);
    ClassDB::bind_method(D_METHOD("get_amalgamates"), &Enemy_Amalgamates::get_amalgamates);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "amalgamates", PROPERTY_HINT_ENUM, "Endogeny,Memoryhead,Snowdrake,LemonBread,ReaperBird"), "set_amalgamates", "get_amalgamates");
}

void Enemy_Amalgamates::ready() {
    attackScene = ResourceLoader::get_singleton()->load("res://Game/mainAttacks/attack_amalgamates.tscn");
    sprite_body = Object::cast_to<AnimatedSprite2D>(get_sprites()->get_node_internal("body"));

    if(type == Endogeny) {
        shader = sprite_body->get_material();
        shader->set_shader_parameter("time", 0);
    }
}

void Enemy_Amalgamates::_process(double delta) {
    if(!shader.is_valid()) return;
    double time = shader->get_shader_parameter("time");
    time += delta;
    shader->set_shader_parameter("time", time);
}

void Enemy_Amalgamates::_on_get_turn() {
    soul->set_mode();
    create_attack();
    attacks->start_attacks();
}

AttackAmalgamates* Enemy_Amalgamates::create_attack() {
    AttackAmalgamates* attack = Object::cast_to<AttackAmalgamates>(attacks->add_attack(attackScene));
    attack->set_type(type);
    return attack;
}

void Enemy_Amalgamates::set_amalgamates(AmalgamatesType value) {
    type = value;
}

AmalgamatesType Enemy_Amalgamates::get_amalgamates() const {
    return type;
}
