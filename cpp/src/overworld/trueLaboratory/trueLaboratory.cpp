#include "trueLaboratory.h"
#include "env.h"

TrueLaboratory::TrueLaboratory() {}

TrueLaboratory::~TrueLaboratory() {}

void TrueLaboratory::_bind_methods() {
    ClassDB::bind_method(D_METHOD("flowey_move"), &TrueLaboratory::flowey_move);
    ClassDB::bind_method(D_METHOD("took_item"), &TrueLaboratory::took_item);
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

void TrueLaboratory::took_item() {
    Array items = global->get_items();
    if(items.find(4) != -1 && get_node_or_null("trigger/real_knife")) {
        get_node_internal("trigger/real_knife")->queue_free();
        global->set_flags("real_knife", true);
    }else if(items.find(5) != -1 && get_node_or_null("trigger/heart_locket")) {
        get_node_internal("trigger/heart_locket")->queue_free();
        global->set_flags("heart_locket", true);
    }
}