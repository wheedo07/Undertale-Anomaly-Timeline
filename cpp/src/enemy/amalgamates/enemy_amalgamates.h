#ifndef Enemy_Amalgamates_H
#define Enemy_Amalgamates_H

#include "engine/Battle/enemy.h"
#include "engine/Battle/battle_system.h"
namespace godot {
    enum AmalgamatesType {
        Endogeny,
        Memoryhead,
        Snowdrake,
        LemonBread,
        ReaperBird
    };

    class AttackAmalgamates;
    class Enemy_Amalgamates : public Enemy {
        GDCLASS(Enemy_Amalgamates, Enemy);

        protected:
            static void _bind_methods();

        private:
            AmalgamatesType type;
            Ref<PackedScene> attackScene;

            void set_amalgamates(AmalgamatesType value);
            AmalgamatesType get_amalgamates() const;

        public:
            Enemy_Amalgamates();
            ~Enemy_Amalgamates();

            void ready() override;
            void _on_get_turn() override;

            AttackAmalgamates* create_attack();
    };
}
VARIANT_ENUM_CAST(godot::AmalgamatesType);

#endif