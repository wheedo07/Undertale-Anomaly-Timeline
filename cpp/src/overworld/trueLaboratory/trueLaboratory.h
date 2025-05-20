#ifndef TrueLaboratory_H
#define TrueLaboratory_H
#include "engine/Overworld/overworld.h"
#include "engine/Overworld/Characters/enemy_overworld.h"
namespace godot {
    class TrueLaboratory : public Overworld {
        GDCLASS(TrueLaboratory, Overworld);

        protected:
            static void _bind_methods();

        private:
            void flowey_move();

            // True 1
            void ready_1();
            void move_1();

            // True 3
            void ready_3();
            void took_item();

            // True 4
            void potato_trigger();
            void potato_select(int index);

        public:
            TrueLaboratory();
            ~TrueLaboratory();

            void ready() override;
    };
}

#endif