#ifndef TITLE_H
#define TITLE_H

#include<godot_cpp/classes/control.hpp>
#include<godot_cpp/classes/input_event.hpp>
#include<godot_cpp/classes/audio_stream_player.hpp>
#include<godot_cpp/classes/sprite2d.hpp>
#include<godot_cpp/variant/node_path.hpp>
namespace godot {
    class Title : public Control {
        GDCLASS(Title, Control)
        
        protected:
            static void _bind_methods();
        
        private:
            int current_pos;
            bool is, start;
            TypedArray<Node> options;

            AudioStreamPlayer* title_music;
            Sprite2D* undertale;
            Sprite2D* anomalyTimeline;

            void _on_completed_start();
        
        public:
            Title();
            ~Title();

            void _ready() override;
            void _input(const Ref<InputEvent>& event) override;

            void refresh_thing(int action = 0);
            int get_current_pos() const;

            void set_current_pos(int pos);
    };
}

#endif