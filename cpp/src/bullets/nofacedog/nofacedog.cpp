#include "nofacedog.h"
#include "env.h"

Nofacedog::Nofacedog() {
    mode = 1;
}

Nofacedog::~Nofacedog() {}

void Nofacedog::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_animation_finished"), &Nofacedog::_animation_finished);
}

void Nofacedog::ready() {
    DefaultBullet::ready();
    sprite = Object::cast_to<AnimatedSprite2D>(get_node_internal(get_sprite_path()));
}

void Nofacedog::play(function<void()> fun) {
    sprite->connect("animation_finished", Callable(this, "_animation_finished"), CONNECT_ONE_SHOT);
    this->fun = fun;
    if(mode == 1) {
        sprite->set_animation("mouth");
    }else if(mode == 2) {
        sprite->set_animation("legtuck");
    }else if(mode == 3) {
        sprite->set_animation("rocket");
    }
    sprite->play();
}

void Nofacedog::_animation_finished() {
    fun();
}

Nofacedog* Nofacedog::set_mode(int type) {
    mode = type;
    return this;
}