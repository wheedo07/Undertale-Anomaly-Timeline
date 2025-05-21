#include "../trueLaboratory.h"
#include "env.h"

void TrueLaboratory::tigger_abs2() {
    if(global->get_flag("tigger_abs2")) return;
    EnemyOverworld* flowey = Object::cast_to<EnemyOverworld>(get_node_internal("Flowey"));
    flowey->connect("animation_finished", Callable(this, "flowey_move"), CONNECT_ONE_SHOT);
    flowey->set_position(Vector2(player->get_position().x-50, 65));
    flowey->show();
    flowey->play_anim("dig", 1, true);
}

void TrueLaboratory::move_2() {
    EnemyOverworld* flowey = Object::cast_to<EnemyOverworld>(get_node_internal("Flowey"));
    flowey->set_frame(0);
    TextBox* textbox = summontextbox();
    textbox->connect("typing_skip", Callable(this, "_on_typing_skip"));
    textbox->character(false, Character::FLOWEY, sys->dia()->from({
        String::utf8("* 하하하! 봤어? 넌 그냥, 부품이래"),
        String::utf8("* '그의 의지를 실험에 통합한다'고~ 너 지금 실험 대상이래!"),
        String::utf8("* 너는 그냥… 걔가 현실로 돌아가기 위한 ‘영혼 연료’인 거야"),
        String::utf8("* 의지? 반복? 그런 건 다 핑계일 뿐이지"),
        String::utf8("* 이제는 알겠지? 우리가 왜 동맹을 맺어야 했는지")
    }));
    sys->executeTrue([this]() { return skip_count >= 3; },
    [this, textbox]() {
        textbox->queue_free();
        summontextbox()->character(false, Character::FLOWEY_EVIL, sys->dia()->from({
            String::utf8("* 그리고 내 말 스킵좀 그만해라"),
            String::utf8("* 도와주려고 했더니만"),
        }));
    }); 
    sys->executeTrue([this]() { return !global->get_player_text_box(); },
    [this, flowey]() {
        flowey->play_anim("dig");
        flowey->connect("animation_finished", Callable(flowey, "queue_free"), CONNECT_ONE_SHOT);
        global->save_flag("tigger_abs2", true);
    });
}