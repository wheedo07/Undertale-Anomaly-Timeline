#include "../trueLaboratory.h"
#include "env.h"

void TrueLaboratory::ready_3() {
    bool real_knife = global->get_flag("real_knife");
    bool heart_locket = global->get_flag("heart_locket");
    if(real_knife) get_node_internal("trigger/real_knife")->queue_free();
    if(heart_locket) get_node_internal("trigger/heart_locket")->queue_free();
}