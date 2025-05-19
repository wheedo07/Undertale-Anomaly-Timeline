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

    if(type == Endogeny) {
        sprite_body->set_frame(0);
        bool use_attack1 = (main->turn_number % 2 == 0);
        bool use_attack2 = !use_attack1;
        
        if(UFus::randf() < 0.2) {
            sprite_body->set_frame(1);
            use_attack1 = true;
            use_attack2 = true;
        }
        if(use_attack1) create_attack()->start_attack();
        if(use_attack2) create_attack(2)->start_attack();
    }
}

AttackAmalgamates* Enemy_Amalgamates::create_attack(int id) {
    AttackAmalgamates* attack = Object::cast_to<AttackAmalgamates>(attacks->add_attack(attackScene));
    attack->set_type(type, id);
    return attack;
}

void Enemy_Amalgamates::set_amalgamates(AmalgamatesType value) {
    type = value;
}

AmalgamatesType Enemy_Amalgamates::get_amalgamates() const {
    return type;
}
