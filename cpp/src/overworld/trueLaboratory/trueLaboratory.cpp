#include "trueLaboratory.h"
#include "env.h"

TrueLaboratory::TrueLaboratory() {}

TrueLaboratory::~TrueLaboratory() {}

void TrueLaboratory::_bind_methods() {
    ClassDB::bind_method(D_METHOD("flowey_move"), &TrueLaboratory::flowey_move);
    ClassDB::bind_method(D_METHOD("took_item"), &TrueLaboratory::took_item);
    ClassDB::bind_method(D_METHOD("potato_trigger"), &TrueLaboratory::potato_trigger);
    ClassDB::bind_method(D_METHOD("potato_select", "index"), &TrueLaboratory::potato_select);
}

void TrueLaboratory::ready() {
    String name = get_name();
    if(name == "true_1") {
        ready_1();
    }else if(name == "true_3") {
        ready_3();
    }
}

void TrueLaboratory::flowey_move() {
    String name = get_name();
    if(name == "true_1") {
        move_1();
    }
}