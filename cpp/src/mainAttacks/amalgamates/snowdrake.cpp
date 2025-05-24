#include "attack_amalgamates.h"
#include "env.h"

void AttackAmalgamates::attack_snowdrake_1() {
    float margin = 20.0f;
    sys->time_loop(Array::make(0.5), [this, margin](double delta, TimeAccumPtr acc) {
        double* time = acc[0];
        if(*time >= 0.6) {
            DefaultBullet* claw = create_clawbullet(Masking::RELATIVE_BOX);
            float random_x = UFus::randf_range(20, box->get_size().x - margin);
            claw->set_position(Vector2(random_x, -10));
            claw->fire(Vector2(random_x, 1), Bullet::MOVEMENT_VELOCITY, 30);

            float scale = UFus::randf_range(0.8, 1.2);
            claw->set_scale(Vector2(scale, scale));
            *time = 0;
        }else *time += delta;
    }, 13);
    sys->sleep([this]() { end_attack(); }, 14);
}

void AttackAmalgamates::attack_snowdrake_2() {
}