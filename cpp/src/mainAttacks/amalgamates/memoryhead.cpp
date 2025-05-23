#include "attack_amalgamates.h"
#include "env.h"

void AttackAmalgamates::attack_memoryhead() {
    box->change_size(Vector2(300, 200));

    float margin = 20.0f;
    sys->time_loop(Array(), [this, margin](double delta, TimeAccumPtr acc) {
        double* time = acc[0];
        
        if(*time >= 0.8f) {
            float box_width = box->get_size().x;
            float box_height = box->get_size().y;
            
            float random_x = UFus::randf_range(margin, box_width - margin);
            float random_y = UFus::randf_range(margin, box_height - margin);
            
            Freakbullet* f = create_freakbullet(Masking::RELATIVE_BOX_CLIP);
            f->set_position(Vector2(random_x, random_y));
            f->play();
            *time = 0;
        }else *time += delta;
    }, 15);
    sys->sleep([this]() { end_attack(); }, 16+get_attack_id());
}