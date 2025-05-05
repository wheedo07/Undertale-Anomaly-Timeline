#include "trueLaboratory.h"
#include "env.h"

void TrueLaboratory::ready_1() {
    int main2 = global->get_flag("main2");
    EnemyOverworld* flowey = Object::cast_to<EnemyOverworld>(get_node_internal("Flowey"));
    if(main2 == 1) {
        flowey->set_frame(1);
        camera->blind(0.5, 0.9);
        player->set_frame(1);
        
        sys->time_loop(Array(),[this](double delta, TimeAccumPtr acc) {
            double* time = acc[0];
            *time += delta;
            
            Vector2 originalPos = player->get_position();
            if (*time >= 1.5 && *time < 10.0) {
                float elapsedShakeTime = *time - 1.5;
                float totalShakeTime = 8.5;
                float progress = elapsedShakeTime / totalShakeTime;
                
                float amplitudeMultiplier = sin(progress * Math_PI); 
                float amplitude = 2.5f * amplitudeMultiplier;
                
                float frequencyCurve;
                if (progress < 0.7) {
                    frequencyCurve = progress * 1.4;
                } else {
                    frequencyCurve = 0.98 - (progress - 0.7) * 0.5;
                }
                
                float frequency = 1.5f + 5.5f * frequencyCurve;
                
                float offsetX = amplitude * sin(elapsedShakeTime * frequency * Math_PI);
                
                player->set_position(Vector2(originalPos.x + offsetX, originalPos.y));
            }
        }, 10);
        sys->sleep([this, flowey]() {
            player->set_frame(0);
            camera->blind(0.25, 0);
            flowey->connect("animation_finished", Callable(flowey, "hide"), CONNECT_ONE_SHOT);
            flowey->connect("animation_finished", Callable(this, "flowey_move"), CONNECT_ONE_SHOT);
            flowey->play_anim("dig");
        }, 10.2);
    }else if(main2 == 2) {
        flowey->queue_free();
    }
}

void TrueLaboratory::move_1() {
    EnemyOverworld* flowey = Object::cast_to<EnemyOverworld>(get_node_internal("Flowey"));
    int main2 = global->get_flag("main2");
    if(main2 == 1) {
        flowey->set_position(Vector2(player->get_position().x, -27));
        flowey->show();
        flowey->play_anim("dig", 0.5, true);
        flowey->connect("animation_finished", Callable(flowey, "set_frame").bind(0), CONNECT_ONE_SHOT);
        flowey->connect("animation_finished", Callable(player, "force_direction").bind(Vector2(0, -1)), CONNECT_ONE_SHOT);
        sys->sleep([this, flowey]() {
            summontextbox()->character(Character::FLOWEY, sys->dia()->from(
                PackedStringArray({
                    String::utf8("* 오, 드디어 일어났네"),
                    String::utf8("* 기절한 얼굴로 널 바라보는 것도 지루했거든"),
                    String::utf8("* 뭐… 그게 중요한 건 아니지"),
                    String::utf8("* 지금 중요한 건... 누가 널 여기로 보냈는지야"),
                    String::utf8("* 여긴 꺼림칙한 과학자의 연구소야"),
                    String::utf8("* 가스터 박사... 들어본 적 있지?"),
                    String::utf8("* 아마 걘 널 오래 전부터 지켜보고 있었어"),
                    String::utf8("* 샌즈 녀석이 가스터를 부른거야 뭔가를 꾸미고 있어. 널 멈추기 위해서"),
                    String::utf8("* 그리고 그는 영혼이 없어도 존재하는 방법을 찾고 있었어"),
                    String::utf8("* 그리고 아이러니하게도, 그게 실제로 성공해버렸지 뭐야"),
                    String::utf8("* 이제 그는 그 '방법'으로, 모든 시간선을 고정시키려 해"),
                    String::utf8("* 누굴 희생해서? 당연히 너 같은, 의지가 강한 실험체를"),
                    String::utf8("* 그러니까, 제안 하나 할게"),
                    String::utf8("* 동맹을 맺자, ") + global->get_player_name() + String::utf8(". 지금은 그들이 더 위험해"),
                })
            )->set_expressions(Array::make(2, 0, 3, 4, 5, 5, 4, 5, 1, 7, 7, 8, 7, 2)),
            Array::make(String::utf8("예"), String::utf8("아니요")));

            auto isFun = [this]() { return !global->get_player_text_box(); };
            sys->sequence({
                {[this]() {
                    summontextbox()->character(Character::FLOWEY, sys->dia()->from(
                        PackedStringArray({
                            String::utf8("* 사실 뭘 선택하든간에"),
                            String::utf8("* 그냥 동맹할 생각이였어"),
                        })
                    ));
                }, isFun},
                {[this]() {
                    summontextbox()->character(Character::FLOWEY_EVIL, sys->dia()->from(
                        PackedStringArray({
                            String::utf8("* 잊었어? 여기는 죽거나 죽이거나 이잖아!")
                        })
                    ));
                }, isFun},
                {[this, flowey]() {
                    camera->Void(0, 0.3, 0.003, 0.2, 0.3);
                    AudioStreamPlayer* voice = Object::cast_to<AudioStreamPlayer>(flowey->get_node_internal("voice"));
                    global->set_flags("main2", 2);
                    flowey->connect("animation_finished", Callable(this, "flowey_move"), CONNECT_ONE_SHOT);
                    voice->connect("finished", Callable(flowey, "play_anim").bind("dig"), CONNECT_ONE_SHOT);
                    voice->play();
                }, isFun}
            });
        }, 1.3);
    }else if(main2 == 2) {
        camera->Void();
        flowey->queue_free();
    }
}