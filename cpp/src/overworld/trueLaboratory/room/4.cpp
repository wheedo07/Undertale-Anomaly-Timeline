#include "../trueLaboratory.h"
#include "env.h"

void TrueLaboratory::potato_trigger() {
    TextBox* textbox = summontextbox();
    textbox->connect("selected_option", Callable(this, "potato_select"), CONNECT_ONE_SHOT);
    textbox->generic(sys->dia()->from({
        String::utf8("* ( 감자칩을 25G 에 삽니까? )")
    }), { String::utf8("산다"), String::utf8("안삼") });
}

void TrueLaboratory::potato_select(int index) {
    if(index != 0) return;
    sys->executeTrue([this]() { return !global->get_player_text_box(); },
    [this]() {
        int gold = global->get_player_gold();
        gold-=25;
        if(gold >= 0) {
            if(global->get_items().size() == 8) {
                summontextbox()->generic(sys->dia()->from({
                    String::utf8("* 당신의 인벤토리가 가득찼다")
                }));
            }else {
                summontextbox()->generic(sys->dia()->from({
                    String::utf8("* ( 자판기에서 감자칩이 나왔다. )")
                }));
                global->set_player_gold(gold);
                Array items = global->get_items();
                items.append(8);
                global->set_items(items);
            }
        }else summontextbox()->generic(sys->dia()->from({
            String::utf8("* ( 돈이 부족하다.. )")
        }));
    });
}