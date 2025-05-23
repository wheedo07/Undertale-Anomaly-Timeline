#include "enemy_amalgamates.h"
#include "src/mainAttacks/amalgamates/attack_amalgamates.h"
#include "env.h"

void Enemy_Amalgamates::memoryhead_turn() {
    Ref<Tween> tween = create_tween()->set_trans(Tween::TRANS_SINE)->set_ease(Tween::EASE_OUT);
    tween->tween_property(sprite_body, "modulate:a", 0, 0.7);
    tween->tween_callback(Callable(create_attack(), "start_attack"))->set_delay(0.5);
}

void Enemy_Amalgamates::memoryhead_act(int option) {
    switch(option) {
        case 1: { // 합류하기
            play_dialogue(1);
            break;
        }
        case 2: { // 거절하기
            play_dialogue(2);
            is_mercy+=1;
            break;
        }
    }
    sys->executeTrue([this]() { return !global->get_battle_text_box(); },
    [this]() {
        if(is_mercy > 0) {
            set_current_state(1);
            Dictionary state = get_stats();
            state["def"] = -999;
            set_stats(state);
        }
        emit_signal("on_act_end");
    });
}