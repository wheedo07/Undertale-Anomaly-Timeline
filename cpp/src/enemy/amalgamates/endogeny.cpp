#include "enemy_amalgamates.h"
#include "src/mainAttacks/amalgamates/attack_amalgamates.h"
#include "env.h"

void Enemy_Amalgamates::endogeny_turn() {
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

void Enemy_Amalgamates::endogeny_item(int option) {
    switch(option) {
        case 0: { // 막대기
            if(is_act[0] < 1) {
                box->blitter_print({ 
                    String::utf8("* 엔도제니가 당신이 방금 장착한 막대기에 관심이 있는거 같다"), String::utf8("* 당신은 막대기를 던졌다"),
                    String::utf8("* 엔도제니가 막대기를 쫓아간다"), String::utf8("* 엔도제니가 막대기를 물어왔다"), String::utf8("* 한동안 이렇게 놀줬다")
                });
                is_act[0]+=1;
                is_mercy += 5;
            }else box->blitter_print({ String::utf8("* ..."),  String::utf8("* 더 이상 막대기에 관심이 없어 보인다") });
        }
    }
    sys->executeTrue([this]() { return !global->get_battle_text_box(); },
    [this]() {
        if(is_mercy >= 8) {
            set_current_state(1);
            Dictionary state = get_stats();
            state["def"] = 1;
            set_stats(state);
        }
        emit_signal("on_item_end");
    });
}

void Enemy_Amalgamates::endogeny_act(int option) {
    if(is_mercy < 8) {
        switch(option) {
            case 1: // 쓰다듬기
                if (is_act[option] < 3) {
                    if (is_mercy >= 4) {
                        box->blitter_print({ String::utf8("* 엔도제니가 당신의 손길을 즐기는 것 같다.") });
                        is_mercy += 2;
                    } else {
                        box->blitter_print({ String::utf8("* 엔도제니가 불안해하지만 천천히 접근을 허락한다.") });
                        is_mercy += 1;
                    }
                } else {
                    box->blitter_print({ String::utf8("* 엔도제니는 이미 충분히 쓰다듬어졌다.") });
                }
                break;
                
            case 2: // 부르기
                if (is_act[option] < 2) {
                    if (is_mercy >= 3) {
                        box->blitter_print({ String::utf8("* 엔도제니가 당신을 향해 고개를 돌렸다."), String::utf8("* 당신의 목소리에 반응하는 것 같다.") });
                        is_mercy += 1;
                    } else {
                        box->blitter_print({ String::utf8("* 엔도제니가 깜짝 놀라 경계한다."), String::utf8("* 아직은 당신을 신뢰하지 않는 것 같다.") });
                        is_mercy += 1;
                    }
                } else {
                    box->blitter_print({ String::utf8("* 엔도제니는 더 이상 부르는 것에 흥미가 없어 보인다.") });
                }
                break;
                
            case 3: // 놀아주기
                if (is_act[option] < 2) {
                    if (is_mercy >= 4) {
                        box->blitter_print({ String::utf8("* 엔도제니가 신나서 뛰어다닌다!"), String::utf8("* 정말 즐거워하는 것 같다!") });
                        is_mercy += 3;
                    } else {
                        box->blitter_print({ String::utf8("* 엔도제니가 조심스럽게 당신의 행동을 지켜본다."), String::utf8("* 아직은 경계하는 것 같다.") });
                        is_mercy += 1;
                    }
                } else {
                    box->blitter_print({ String::utf8("* 엔도제니는 지쳐 보인다. 지금은 쉬고 싶어하는 것 같다.") });
                }
                break;
                
            case 4: // 무시하기
                if (is_act[option] < 1) {
                    box->blitter_print({ String::utf8("* 엔도제니를 무시했다."), String::utf8("* 은근 슬퍼 보인다...") });
                }else {
                    box->blitter_print({ String::utf8("* 엔도제니를 계속 무시했다."), String::utf8("* 엔도제니가 당신을 지켜보고 있다...") });
                }
                break;
        }
        is_act[option] += 1;
        if(is_mercy < 0) is_mercy = 0;
    }
    sys->executeTrue([this]() { return !global->get_battle_text_box(); },
    [this]() {
        if(is_mercy >= 8) {
            set_current_state(1);
            Dictionary state = get_stats();
            state["def"] = 1;
            set_stats(state);
        }
        emit_signal("on_act_end");
    });
}