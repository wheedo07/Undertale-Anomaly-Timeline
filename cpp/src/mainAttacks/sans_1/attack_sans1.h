#ifndef AttackSans1_H
#define AttackSans1_H

#include "engine/Battle/Attacks/attacks.h"
#include "engine/Battle/Bullets/custom/bone.h"
#include "engine/Battle/Bullets/custom/bone_spike.h"
#include "engine/Battle/Bullets/custom/blaster.h"
#include "engine/Battle/Bullets/battle_platform.h"
namespace godot {
    class AttackSans1 : public AttackBase {
        GDCLASS(AttackSans1, AttackBase);

        protected:
            static void _bind_methods();

        private:
            Ref<PackedScene> bone;
            Ref<PackedScene> bone_spike;
            Ref<PackedScene> blaster;
            Ref<PackedScene> platform;

            void turn_0();
            void turn_1();
            void turn_2();

        public:
            AttackSans1();
            ~AttackSans1();

            void ready() override;
            void start_attack() override;

            Bone* create_bone(Masking type);
            BoneSpike* create_boneSpike(Masking type);
            Blaster* create_blaster(Masking type);
            BattlePlatform* create_platform(Masking type);
    };
}

#endif