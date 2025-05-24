#include "enemy_amalgamates.h"
#include "src/mainAttacks/amalgamates/attack_amalgamates.h"
#include "env.h"

void Enemy_Amalgamates::snowdrake_turn() {
    box->change_size(Vector2(320, 140));
    play_dialogue(0);
    sys->executeTrue([this]() { return !global->get_battle_text_box(); },
    [this]() {
        create_attack()->start_attack();
    });
}

void Enemy_Amalgamates::snowdrake_act(int option) {
    if(is_mercy < 3) {
        switch(option) {
            case 1: { // 웃기
                if (is_act[option] == 0)
                    box->blitter_print({ 
                        String::utf8("* 융합체의 얼어붙은 부분이 약간 떨린다."),
                    });
                else if (is_act[option] == 1)
                    box->blitter_print({ 
                        String::utf8("* 융합체는 당신의 의도를 이해하지 못한다."),
                        String::utf8("* 당신이 계속 웃는 모습이 상당히 불편해 보인다.")
                    });
                else box->blitter_print({
                    String::utf8("* 융합체는 당신 뒤의 존재를 무서워하는거 같다"),
                });
                break;
            }
            case 2: { // 야유하기
                if(is_act[option] == 0)
                    box->blitter_print({ String::utf8("* ...뭐? 그런말 진짜 했구나") });
                else box->blitter_print({ String::utf8("* 보니까 융합체는 알아듣지도 못하는거 같다") });
                break;
            }
            case 3: { // 농담하기
                if(is_act[option] == 0) {
                    box->blitter_print({ 
                        String::utf8("* \"눈사람이 아이스크림을 먹으면 어떻게 될까?\""),
                        String::utf8("* 융합체가 미약하게 반응한다.")
                    });
                    is_mercy += 1;
                }else if (is_act[option] == 1) {
                    box->blitter_print({ 
                        String::utf8("* \"눈사람이 '너무 춥다'고 불평하면 어떻게 돼?\""),
                        String::utf8("* 융합체의 얼굴이 잠시 변형되더니..."),
                        String::utf8("* ...약간 미소 짓는 것처럼 보인다.")
                    });
                    is_mercy += 1;
                }else if (is_act[option] == 2) {
                    box->blitter_print({ 
                        String::utf8("* \"스노우드레이크는 항상 말했지...\""),
                        String::utf8("* 융합체가 갑자기 격렬하게 반응한다."),
                    });
                    is_mercy += 1;
                }
                break;
            }
        }
        is_act[option] += 1;
    }
    sys->executeTrue([this]() { return !global->get_battle_text_box(); },
    [this]() {
        if(is_mercy > 2) {
            set_current_state(1);
            Dictionary state = get_stats();
            state["def"] = -9999;
            set_stats(state);
        }
        emit_signal("on_act_end");
    });
}