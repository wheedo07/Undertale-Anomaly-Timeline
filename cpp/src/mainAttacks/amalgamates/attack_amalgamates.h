#ifndef AttackAmalgamates_H
#define AttackAmalgamates_H

#include "engine/Battle/Attacks/attacks.h"
#include "src/bullets/nofacedog/nofacedog.h"
#include "src/enemy/amalgamates/enemy_amalgamates.h"
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

            void attack_endogeny_1();
            void attack_endogeny_2();

        public:
            AttackAmalgamates();
            ~AttackAmalgamates();

            void set_type(AmalgamatesType value, int id);

            void ready() override;
            void start_attack() override;

            DefaultBullet* create_dogmissle(Masking type);
            Nofacedog* create_nofacedog(Masking type, int mode);
    };
}

#endif