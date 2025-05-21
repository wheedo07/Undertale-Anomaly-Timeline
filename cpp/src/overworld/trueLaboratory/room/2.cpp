#include "../trueLaboratory.h"
#include "env.h"

void TrueLaboratory::tigger_abs2() {
    if(global->get_flag("tigger_abs2")) return;
    EnemyOverworld* flowey = Object::cast_to<EnemyOverworld>(get_node_internal("Flowey"));
    flowey->connect("animation_finished", Callable(this, "flowey_move"), CONNECT_ONE_SHOT);
    flowey->set_position(Vector2(player->get_position().x-50, 65));
    flowey->show();
    flowey->play_anim("dig_break");
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
        TextBox* textbox2 = summontextbox();
        textbox2->set_key(false);
        sys->sleep([this, textbox2]() { textbox2->set_key(true); }, 1.5);
        textbox2->character(false, Character::FLOWEY, sys->dia()->from({
            String::utf8("* ...방금 스킵했지?"),
            String::utf8("* 하하, 괜찮아~ 다음엔 안 놓치게 될 거야. 아마도"),
        }));
    }); 
    sys->executeTrue([this]() { return !global->get_player_text_box(); },
    [this, flowey]() {
        flowey->play_anim("dig");
        flowey->connect("animation_finished", Callable(flowey, "queue_free"), CONNECT_ONE_SHOT);
        global->save_flag("tigger_abs2", true);
    });
}