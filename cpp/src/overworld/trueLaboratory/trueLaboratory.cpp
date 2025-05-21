#include "trueLaboratory.h"
#include "env.h"

TrueLaboratory::TrueLaboratory() {
    skip_count = 0;
}

TrueLaboratory::~TrueLaboratory() {}

void TrueLaboratory::_bind_methods() {
    ClassDB::bind_method(D_METHOD("flowey_move"), &TrueLaboratory::flowey_move);
    ClassDB::bind_method(D_METHOD("_on_typing_skip", "count"), &TrueLaboratory::_on_typing_skip);
    ClassDB::bind_method(D_METHOD("took_item"), &TrueLaboratory::took_item);
    ClassDB::bind_method(D_METHOD("potato_trigger"), &TrueLaboratory::potato_trigger);
    ClassDB::bind_method(D_METHOD("potato_select", "index"), &TrueLaboratory::potato_select);
    ClassDB::bind_method(D_METHOD("tigger_abs2"), &TrueLaboratory::tigger_abs2);
}

void TrueLaboratory::ready() {
    String name = get_name();
    if(name == "true_1")
        ready_1();
    else if(name == "true_3")
        ready_3();
}

void TrueLaboratory::flowey_move() {
    String name = get_name();
    if(name == "true_1")
        move_1();
    else if(name == "true_2")
        move_2();
}

void TrueLaboratory::_on_typing_skip(int count) {
    skip_count = count;
}