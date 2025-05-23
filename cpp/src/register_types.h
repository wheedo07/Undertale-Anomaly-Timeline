#ifndef RegisterTYPE_H
#define RegisterTYPE_H
#include<godot_cpp/core/class_db.hpp>
#include "mainNode/mainNode.h"
#include "mainNode/title.h"
#include "mainNode/dropText.h"
#include "trigger/text_trigger.h"
#include "trigger/move_trigger.h"

// attackNode
#include "mainAttacks/sans_1/attack_sans1.h"
#include "mainAttacks/amalgamates/attack_amalgamates.h"

// overworld Node
#include "overworld/coreNode/coreNode.h"
#include "overworld/laboratoryNode/laboratoryNode.h"
#include "overworld/trueLaboratory/trueLaboratory.h"

// enemy Node
#include "enemy/sans_1/enemy_sans1.h"
#include "enemy/amalgamates/enemy_amalgamates.h"

// Bullets Node
#include "bullets/nofacedog/nofacedog.h"
#include "bullets/freakbullet/freakbullet.h"
using namespace godot;

void register_init();

#endif