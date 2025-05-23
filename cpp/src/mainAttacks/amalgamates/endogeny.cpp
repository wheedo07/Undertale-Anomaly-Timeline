#include "attack_amalgamates.h"
#include "env.h"

void AttackAmalgamates::attack_endogeny_1() {
    box->change_size(Vector2(300, 140));
    Nofacedog* dog = create_nofacedog(Masking::ABSOLUTE, 1);
    dog->set_position(Vector2(555, 310));
    sys->time_loop(Array(), [this](double delta, TimeAccumPtr acc) {
        double* time = acc[0];
        if(*time >= 4) {
            box->change_size(Vector2(-50, 0), true);
            *time = 0;
        }else *time += delta;
    }, 23);
    dog->play([this, dog]() {
        float dog_speed = 95.0f;
        dog->fire(Vector2(555, 260), Bullet::MOVEMENT_TWEEN, dog_speed);
        
        bool* moving_up = new bool(true);
        sys->time_loop(Array::make(0.1), [this, dog, moving_up, dog_speed](double delta, TimeAccumPtr acc) {
            double* time = acc[0];
            
            Vector2 current_pos = dog->get_position();
            if(*moving_up && fabs(current_pos.y - 260.0f) < 5.0f) {
                *moving_up = false;
                dog->fire(Vector2(555, 380), Bullet::MOVEMENT_TWEEN, dog_speed);
            }else if(!*moving_up && fabs(current_pos.y - 380.0f) < 5.0f) {
                *moving_up = true;
                dog->fire(Vector2(555, 260), Bullet::MOVEMENT_TWEEN, dog_speed);
            }
            
            if(*time >= UFus::randf_range(0.2, 0.3)) {
                DefaultBullet* missle = create_dogmissle(Masking::ABSOLUTE);
                Vector2 vec = dog->get_position();
                missle->set_position(vec);
                missle->fire(Vector2(100, vec.y), Bullet::MOVEMENT_VELOCITY, 180);
                *time = 0;
            } else *time += delta;
        }, 20);
    });
    sys->sleep([this]() { end_attack(); }, 24);
}

void AttackAmalgamates::attack_endogeny_2() {
    box->change_size(Vector2(300, 140));
    Nofacedog* dog = create_nofacedog(Masking::ABSOLUTE, 2);
    dog->set_position(Vector2(555, 310));
    dog->play([this, dog]() {
        float dog_speed = 180.0f;
        sys->time_loop(Array(), [this, dog, dog_speed](double delta, TimeAccumPtr acc) {
            double* time = acc[0];
            
            if(*time >= UFus::randf_range(0.8, 1.5)) {
                Vector2 soul_pos = soul->get_position();
                dog->queue_fire(0, soul_pos, Bullet::MOVEMENT_TWEEN, dog_speed);
                *time = 0;
            }else *time += delta;
        }, 13);
        sys->sleep([this]() { end_attack(); }, 14);
        dog->set_mode(3)->play();
    });
}
