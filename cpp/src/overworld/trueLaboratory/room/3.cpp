#include "../trueLaboratory.h"
#include "env.h"

void TrueLaboratory::ready_3() {
    bool real_knife = global->get_flag("real_knife");
    bool heart_locket = global->get_flag("heart_locket");
    if(real_knife) get_node_internal("trigger/real_knife")->queue_free();
    if(heart_locket) get_node_internal("trigger/heart_locket")->queue_free();
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