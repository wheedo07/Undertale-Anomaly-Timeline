#include "attack_sans1.h"
#include "env.h"

void AttackSans1::turn_2() {
    box->change_size(Vector2(500, 140));
    emit_signal("throws", Vector2(-1, 0), 75);

    sys->sleep([this]() {
        float speed = 65;
        emit_signal("throws", Vector2(0, 1), 30);
        Bone* bottom = create_bone(Masking::ABSOLUTE_CLIP);
        bottom->set_position(Vector2(1010, 383));
        bottom->set_rotation_degrees(180);
        bottom->tween_height(30, 0);
        bottom->tween_width(520, 0);
        bottom->fire(Vector2(570, 383), Bullet::MOVEMENT_TWEEN, speed);

        BattlePlatform* plat = create_platform(Masking::ABSOLUTE_CLIP);
        plat->set_position(Vector2(550, 330));
        plat->fire(Vector2(10, 330), 60, speed, BattleObject::VELOCITY);

        sys->sleep([this, bottom]() { bottom->scroll_texture(Vector2(-2, 0)); }, 5);
        sys->sequence({
            {[this, speed]() {
                BattlePlatform* plat = create_platform(Masking::ABSOLUTE_CLIP);
                plat->set_position(Vector2(600, 330));
                plat->fire(Vector2(10, 330), 60, speed, BattleObject::VELOCITY);

                sys->sleep([this]() {
                    Blaster* bl = create_blaster(Masking::ABSOLUTE);
                    bl->set_position(Vector2(310, -100));
                    bl->fire(Vector2(310, 100), 1.3);
                }, 4);
            }, 2.8f},
            {[this, speed]() {
                BattlePlatform* plat = create_platform(Masking::ABSOLUTE_CLIP);
                plat->set_position(Vector2(600, 330));
                plat->fire(Vector2(10, 330), 60, speed, BattleObject::VELOCITY);

                sys->sleep([this]() {
                    Bone* bone = create_bone(Masking::ABSOLUTE_CLIP);
                    bone->set_position(Vector2(582, 270));
                    bone->tween_height(200, 0);
                    bone->set_mode();
                    bone->fire(Vector2(100, 270), Bullet::MOVEMENT_TWEEN, 200);
                    bone->queue_fire(0.3, Vector2(500, 270), Bullet::MOVEMENT_VELOCITY, 250);
                }, 4);
            }, 2.8f},
            {[this, speed]() {
                BattlePlatform* plat = create_platform(Masking::ABSOLUTE_CLIP);
                plat->set_position(Vector2(600, 330));
                plat->fire(Vector2(10, 330), 60, speed, BattleObject::VELOCITY);
            }, 2.8f},
            {[this, speed]() {
                BattlePlatform* plat = create_platform(Masking::ABSOLUTE_CLIP);
                plat->set_position(Vector2(600, 330));
                plat->fire(Vector2(10, 330), 60, speed, BattleObject::VELOCITY);

                sys->sleep([this]() {
                    Blaster* bl = create_blaster(Masking::RELATIVE_BOX);
                    bl->set_position(Vector2(35, 35));
                    bl->set_rotation_degrees(-90);
                    bl->fire(Vector2(50, 35), 1.3);
                }, 4);
            }, 2.8f},
            {[this, speed, bottom]() {
                BattlePlatform* plat = create_platform(Masking::ABSOLUTE_CLIP);
                plat->set_position(Vector2(600, 297));
                plat->fire(Vector2(10, 297), 60, speed, BattleObject::VELOCITY);

                Bone* bone = create_bone(Masking::ABSOLUTE_CLIP);
                bone->set_position(Vector2(582, 330));
                bone->tween_height(100, 0);
                bone->tween_width(125, 0);
                bone->fire(Vector2(50, 330), Bullet::MOVEMENT_VELOCITY, speed);

                bottom->scroll_texture();
                bottom->fire(Vector2(500, 383), Bullet::MOVEMENT_VELOCITY, speed);
            }, 2.8f},
            {[this]() {
                end_attack();
            }, 10.0f}
        });
    }, 0.5);
}