#ifndef NofaceDog_H
#define NofaceDog_H

#include "engine/Battle/Bullets/defaultbullet.h"
#include<godot_cpp/classes/animated_sprite2d.hpp>
#include<functional>
using namespace std;
namespace godot {
    class Nofacedog : public DefaultBullet {
        GDCLASS(Nofacedog, DefaultBullet);

        protected:
            static void _bind_methods();

        private:
            AnimatedSprite2D* sprite;
            function<void()> fun;
            int mode;

            void _animation_finished();

        public:
            Nofacedog();
            ~Nofacedog();

            void ready() override;

            void play(function<void()> fun=[]{});
            Nofacedog* set_mode(int type);
    };
};

#endif