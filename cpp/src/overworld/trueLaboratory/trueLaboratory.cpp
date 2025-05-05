#include "trueLaboratory.h"
#include "env.h"

TrueLaboratory::TrueLaboratory() {}

TrueLaboratory::~TrueLaboratory() {}

void TrueLaboratory::_bind_methods() {
    ClassDB::bind_method(D_METHOD("flowey_move"), &TrueLaboratory::flowey_move);
}

void TrueLaboratory::ready() {
    String name = get_name();
    if(name == "true_1") {
        ready_1();
    }
}

void TrueLaboratory::flowey_move() {
    String name = get_name();
    if(name == "true_1") {
        move_1();
    }
}