#include "laboratoryNode.h"
#include "env.h"
#include "engine/Overworld/Characters/enemy_overworld.h"

LaboratoryNode::LaboratoryNode() {}

LaboratoryNode::~LaboratoryNode() {}

void LaboratoryNode::_bind_methods() {
    ClassDB::bind_method(D_METHOD("init"), &LaboratoryNode::init);
    ClassDB::bind_method(D_METHOD("character_talk"), &LaboratoryNode::character_talk);
    ClassDB::bind_method(D_METHOD("main2_event"), &LaboratoryNode::main2_event);
    ClassDB::bind_method(D_METHOD("finished_on"), &LaboratoryNode::finished_on);
}

void LaboratoryNode::ready() {
    event_sound = Object::cast_to<AudioStreamPlayer>(get_node_internal("event/sound"));
    event_main2 = Object::cast_to<AudioStreamPlayer>(get_node_internal("event/main2"));
    camera->blind(0.3);
    camera->connect("finished_tween", Callable(this, "init"), CONNECT_ONE_SHOT);
}

void LaboratoryNode::init() {
    EnemyOverworld* sans = Object::cast_to<EnemyOverworld>(get_node_internal("Sans"));

    if(!global->get_flag("main2")) {
        global->set_player_move(false);
        sans->start_walking(Vector2(0, -1));
        sans->start_walking();
        
        player->start_walking(Vector2i(-1, 0));
        auto isFun = [this]() { return !global->get_player_text_box(); };
        sys->sequence({
            {[this, sans]() {
                player->start_walking();
                player->set_walk_speed(80);

                sans->start_walking(Vector2i(1, 0));
                sans->start_walking();
                sans->show_alert();
            }, 1.5f},
            {[this]() {
                if(global->get_flag("sans_1_death")) {
                    summontextbox()->character(false, Character::SANS, sys->dia()->from({
                        String::utf8("* 헤헤"),
                        String::utf8("* 계속해볼까?"),
                    })->set_expressions(Array::make(1, 5)));
                }else summontextbox()->character(false, Character::SANS, sys->dia()->from({
                    String::utf8("* 헤. 따라오고 있었어?"),
                    String::utf8("* 여기까지 오느라 바빴나 보네"),
                    String::utf8("* 그 손에 묻은 먼지는 꽤 많아 보이는데... 몬스터를 많이 만났나 봐..?"),
                    String::utf8("* 어째서 왜? 여전히 이런 길을 선택한 거지? 호기심? 지루함? 아니면..."),
                    String::utf8("* 그저 할 수 있으니까?"),
                })->set_expressions(Array::make(1, 0, 18, 4, 5))
                ->set_speed(Array::make(0.08, 0.08, 0.08, 0.1)));
            }, 0.4f},
            {[this]() {
                if(global->get_flag("sans_1_death")) return;
                summontextbox()->generic(sys->dia()->from({
                    String::utf8("* (연구소는 평소와 다르게 음산하다...)")
                }));
            }, isFun},
            {[this]() {
                if(global->get_flag("sans_1_death")) return;
                summontextbox()->character(false, Character::SANS, sys->dia()->from({
                    String::utf8("* 뭐, 중요하진 않아."),
                    String::utf8("* 우리 모두 자신의 선택에 책임을 져야 하니까"),
                    String::utf8("* 네 '재미'가 여기서 끝나길 바랐지만... 어쩔 수 없네"),
                    String::utf8("* 마지막으로 kid 한가지 조언을 할게 너를 위해서기도 해"),
                    String::utf8("* 이제 그만두는게 좋을거야")
                })->set_expressions(Array::make(4, 4, 3, 9, 17)));
            }, isFun},
            {[this]() {
                sys->load_battle("res://Game/encounters/tres/sans_1.tres",  Vector2(324, 323));
            }, isFun}
        });
    }else {
        summontextbox()->character(false, Character::SANS, sys->dia()->from({
            String::utf8("* ..."),
            String::utf8("* 잠깐 있어봐"),
        })->set_expressions(Array::make(2, 18)));
        sys->executeTrue([this]() { return !global->get_player_text_box(); },
        [this, sans]() {
            audio_player->play("teleport");
            camera->blind(0.2, 1, 0.3);
            sans->set_position(Vector2(-420, 233));
            sans->start_walking(Vector2i(0, -1));
            sans->start_walking();
            camera->connect("finished_tween", Callable(global, "set_player_move").bind(true), CONNECT_ONE_SHOT);
            camera->connect("finished_tween", Callable(camera, "Void"), CONNECT_ONE_SHOT);
        });
    }
}

void LaboratoryNode::character_talk() {
    camera->Void(0, 5, 0.005, 0.1, 2);
    audio_player->play("beep");
    TextBox* textbox = summontextbox();
    textbox->set_key(false);
    textbox->character(false, Character::SANS, sys->dia()->from({
        String::utf8("어..? 잠깐만.. 뭔가 이상한..")
    })->set_speed(Array::make(0.2))->set_expressions(Array::make(22)));
    sys->sleep([this, textbox]() { textbox->on_text_click_played(); }, 3.8);
    sys->executeTrue([this]() { return !global->get_player_text_box(); },
    [this]() {
        audio_player->stop_audio("beep");
        global->set_player_in_menu(true);
        camera->blind(0, 1, 3.5);
        camera->connect("finished_tween", Callable(this, "main2_event"), CONNECT_ONE_SHOT);
    });
}

void LaboratoryNode::main2_event() {
    audio_player->loop_play("glitch");
    camera->glitch(4, 0.1);

    event_main2->play();
    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load("res://Game/encounters/body/gaster.tscn");
    gaster = Object::cast_to<Node2D>(scene->instantiate());
    camera->blinder->add_child(gaster);
    gaster->set_position(Vector2(330, 200));
    sys->sequence({
        {[this]() {
            gaster->get_node_internal("head")->call("set_frame", 1);
            camera->glitch(0.15, 0.4);
        }, 4.0f},
        {[this]() {
            gaster->queue_free();
            camera->Void(0, 5, 0.02, 0.1, 3);
            special_1 = Object::cast_to<Sprite2D>(get_node_internal("event/special_1")->duplicate());
            camera->blinder->add_child(special_1);
            special_1->set_visible(true);
            special_1->set_position(Vector2(400, 50));
            special_1->set_modulate(Color(1, 1, 1, 0.0));
            special_1->set_scale(Vector2(0.1, 0.1));

            tween = create_tween()->set_parallel();
            tween->tween_property(special_1, "scale", Vector2(1.5, 1.5), 7.0)->set_ease(Tween::EASE_OUT)->set_trans(Tween::TRANS_CUBIC);
            tween->tween_property(special_1, "modulate", Color(1, 1, 1, 1.0), 3.0)->set_ease(Tween::EASE_IN)->set_trans(Tween::TRANS_SINE);
        }, 3.0f},
        {[this]() {
            event_sound->connect("finished", Callable(this, "finished_on"), CONNECT_ONE_SHOT);
            event_main2->stop();
            event_sound->play();
            camera->glitch(0, 0.8);
        }, 3.2f}
    });
}

void LaboratoryNode::finished_on() {
    if(tween->is_valid()) tween->kill();
    special_1->queue_free();
    camera->kill();
    audio_player->stop_audio("glitch");
    hide();
    global->get_scene_container()->reload_camera();
    sys->sleep([this]() {
        scene_changer->load_general_scene("res://Game/overworld/trueLaboratory/1.tscn");
    }, 1.5);
}