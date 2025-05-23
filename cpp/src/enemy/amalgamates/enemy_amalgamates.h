#ifndef Enemy_Amalgamates_H
#define Enemy_Amalgamates_H

#include "engine/Battle/enemy.h"
#include "engine/Battle/battle_system.h"
#include<godot_cpp/classes/shader_material.hpp>
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
	        int is_mercy;
	        PackedInt64Array is_act;
            AmalgamatesType type;
            Ref<PackedScene> attackScene;
            Ref<ShaderMaterial> shader;
            AnimatedSprite2D* sprite_body;

            void set_amalgamates(AmalgamatesType value);
            AmalgamatesType get_amalgamates() const;

            // Endogeny
            void endogeny_turn();
            void endogeny_act(int option);
            void endogeny_item(int option);

            // Memoryhead
            void memoryhead_turn();
            void memoryhead_act(int option);

        public:
            Enemy_Amalgamates();
            ~Enemy_Amalgamates();

            void ready() override;
            void _process(double delta) override;
            void _on_get_turn() override;
            void on_act_used(int option) override;
            void on_item_used(int option) override;
            void _on_end_turn() override;

            AttackAmalgamates* create_attack(int id=1);
    };
}
VARIANT_ENUM_CAST(godot::AmalgamatesType);

#endif
