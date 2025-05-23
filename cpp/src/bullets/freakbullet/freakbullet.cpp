#include "freakbullet.h"
#include "env.h"

Freakbullet::Freakbullet() {}

Freakbullet::~Freakbullet() {}

void Freakbullet::_bind_methods() {}

void Freakbullet::ready() {
    DefaultBullet::ready();
    sprite = Object::cast_to<AnimatedSprite2D>(get_node_internal(get_sprite_path()));
}

void Freakbullet::play() {
    sprite->connect("animation_finished", Callable(this, "kill"), CONNECT_ONE_SHOT);
    sprite->set_speed_scale(UFus::randf_range(1, 3));
    sprite->play();
}