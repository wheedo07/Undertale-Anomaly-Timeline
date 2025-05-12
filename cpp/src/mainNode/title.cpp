#include "title.h"
#include "env.h"
#include "engine/Menus/option_selectable.h"
#include<godot_cpp/core/class_db.hpp>
#include<godot_cpp/variant/utility_functions.hpp>
#include<godot_cpp/classes/scene_tree.hpp>
#include<godot_cpp/variant/callable.hpp>
#include<godot_cpp/classes/engine.hpp>
#define OptionSize 3

Title::Title() {
    current_pos = 0;
    title_music = nullptr;
    is = false;
}

Title::~Title() {}

void Title::_bind_methods() {
    ClassDB::bind_method(D_METHOD("refresh_thing", "action"), &Title::refresh_thing, DEFVAL(0));
    ClassDB::bind_method(D_METHOD("_on_completed_start"), &Title::_on_completed_start);
    
    ClassDB::bind_method(D_METHOD("set_current_pos", "pos"), &Title::set_current_pos);
    ClassDB::bind_method(D_METHOD("get_current_pos"), &Title::get_current_pos);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_pos"), "set_current_pos", "get_current_pos");
}

void Title::_ready() {
    if(!global || isEditor) return;
    start = false;
    options = get_children();

    Object::cast_to<OptionSelectable>(options[current_pos])->set_selected(true);

    title_music = Object::cast_to<AudioStreamPlayer>(get_node_internal("../title_mus"));
    undertale = Object::cast_to<Sprite2D>(get_node_internal("../Undertale"));
    anomalyTimeline = Object::cast_to<Sprite2D>(get_node_internal("../Anomaly-Timeline"));
    global->get_Music()->set_stream(title_music->get_stream());
    global->get_Music()->play();

    Vector2 screen_size = get_viewport_rect().size;
    undertale->set_position(Vector2(-screen_size.x, undertale->get_position().y));
    anomalyTimeline->set_position(Vector2(screen_size.x * 2, anomalyTimeline->get_position().y));

    Ref<Tween> undertale_tween = create_tween();
    undertale_tween->set_ease(Tween::EASE_OUT);
    undertale_tween->set_trans(Tween::TRANS_BACK);
    undertale_tween->tween_property(undertale, "position", Vector2(320, 75), 1.8);
    
    Ref<Tween> anomaly_tween = create_tween();
    anomaly_tween->connect("finished", Callable(this, "_on_completed_start"), CONNECT_ONE_SHOT);
    anomaly_tween->set_ease(Tween::EASE_OUT);
    anomaly_tween->set_trans(Tween::TRANS_BACK);
    anomaly_tween->tween_interval(0.2);
    anomaly_tween->tween_property(anomalyTimeline, "position", Vector2(320, 140), 1.8);
}

void Title::set_current_pos(int pos) {
    current_pos = ((pos % OptionSize) + OptionSize) % OptionSize;
}

int Title::get_current_pos() const {
    return current_pos;
}

void Title::_input(const Ref<InputEvent>& event) {
    if(!start) return;
    
    if (event->is_action_pressed("ui_up")) {
        refresh_thing(-1);
    }
    
    if (event->is_action_pressed("ui_down")) {
        refresh_thing(1);
    }
    
    if (event->is_action_pressed("ui_accept") && !is) {
        global->get_Music()->stop();
        CameraFx* camera = global->get_scene_container()->get_camera();
        is = true;
        switch (current_pos) {
            case 0: { // 시작
                    camera->blind(0.6);
                    camera->connect("finished_tween", Callable(this, "_on_completed_start"), CONNECT_ONE_SHOT);
                }
                break;
                
            case 1: { // 인트로
                    camera->blind(0.6);
                    camera->connect("finished_tween", Callable(global->get_scene_container(), "change_scene_to_file").bind("res://Intro/intro.tscn"), CONNECT_ONE_SHOT);
                }
                break;
                
            case 2: // 종료
                get_tree()->quit();
                break;
        }
    }
}

void Title::_on_completed_start() {
    if (!global) return;

    if(start) {
        if (global->get_first()) {
            global->get_scene_container()->change_scene_to_file("res://Intro/name_selection.tscn");
        } else {
            global->get_scene_container()->change_scene_to_file("res://Menus/save_loader.tscn");
        }
    }else start = true;
}

void Title::refresh_thing(int action) {
    audio_player->play("choice");
    
    Object::cast_to<OptionSelectable>(options[current_pos])->set_selected(false);

    current_pos += action;
    set_current_pos(current_pos);
    
    Object::cast_to<OptionSelectable>(options[current_pos])->set_selected(true);
}