#ifndef AttackAmalgamates_H
#define AttackAmalgamates_H

#include "engine/Battle/Attacks/attacks.h"
#include "src/enemy/amalgamates/enemy_amalgamates.h"
namespace godot {
    class AttackAmalgamates : public AttackBase {
        GDCLASS(AttackAmalgamates, AttackBase);

        protected:
            static void _bind_methods();

        private:
            AmalgamatesType type;

        public:
            AttackAmalgamates();
            ~AttackAmalgamates();

            void set_type(AmalgamatesType value);

            void ready() override;
            void start_attack() override;
    };
}

#endif