#ifndef NofaceDog_H
#define NofaceDog_H

#include "engine/Battle/Bullets/defaultbullet.h"
namespace godot {
    class Nofacedog : public DefaultBullet {
        GDCLASS(Nofacedog, DefaultBullet);

        protected:
            static void _bind_methods();

        public:
            Nofacedog();
            ~Nofacedog();

            void ready() override;
    };
};

#endif