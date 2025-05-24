#ifndef AttackAmalgamates_H
#define AttackAmalgamates_H

#include "engine/Battle/Attacks/attacks.h"
#include "src/enemy/amalgamates/enemy_amalgamates.h"
#include "src/bullets/nofacedog/nofacedog.h"
#include "src/bullets/freakbullet/freakbullet.h"
namespace godot {
    class AttackAmalgamates : public AttackBase {
        GDCLASS(AttackAmalgamates, AttackBase);

        protected:
            static void _bind_methods();

        private:
            int id;
            AmalgamatesType type;
            Ref<PackedScene> scene_dogmissle;
            Ref<PackedScene> scene_nofacedog;
            Ref<PackedScene> scene_freakbullet;
            Ref<PackedScene> scene_clawbullet;

            // Endogeny
            void attack_endogeny_1();
            void attack_endogeny_2();

            // Memoryhead
            void attack_memoryhead();

            // Snowdrake
            void attack_snowdrake_1();
            void attack_snowdrake_2();

        public:
            AttackAmalgamates();
            ~AttackAmalgamates();

            void set_type(AmalgamatesType value, int id);

            void ready() override;
            void start_attack() override;

            DefaultBullet* create_dogmissle(Masking type);
            Nofacedog* create_nofacedog(Masking type, int mode);
            Freakbullet* create_freakbullet(Masking type);
            DefaultBullet* create_clawbullet(Masking type);
    };
}

#endif