#ifndef FreakBullet_H
#define FreakBullet_H

#include "engine/Battle/Bullets/defaultbullet.h"
#include<godot_cpp/classes/animated_sprite2d.hpp>
namespace godot {
    class Freakbullet : public DefaultBullet {
        GDCLASS(Freakbullet, DefaultBullet);

        protected:
            static void _bind_methods();

        private:
            AnimatedSprite2D* sprite;
        
        public:
            Freakbullet();
            ~Freakbullet();

            void ready() override;

            void play();
    };
};

#endif