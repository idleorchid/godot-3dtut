#include "main.hpp"

#include <Timer.hpp>

#include <string>
#include <iostream>

void Main::_ready()
{
    _player = get_node<Player>("Player");
    _random = (godot::Ref<godot::RandomNumberGenerator>)godot::RandomNumberGenerator::_new();
    _random->randomize();
}

void Main::_on_MobTimer_timeout()
{
    Node *mob = mob_scene->instance();
    _mob_spawn_location = get_node<godot::PathFollow>("SpawnPath/SpawnLocation");
    _mob_spawn_location->set_offset((real_t)_random->randi());

    Mob *mob_script = Object::cast_to<Mob>(mob);
    mob_script->initialize(_mob_spawn_location->get_translation(), _player->get_transform().origin);
    add_child(mob);
}

void Main::_on_Player_hit()
{
    godot::Timer *_mob_timer = get_node<godot::Timer>("MobTimer");
    _mob_timer->stop();
}

void Main::_register_methods()
{
    godot::register_property("mob_scene", &Main::mob_scene, (godot::Ref<godot::PackedScene>)nullptr);
    godot::register_method("_ready", &Main::_ready);
    godot::register_method("_on_MobTimer_timeout", &Main::_on_MobTimer_timeout);
    godot::register_method("_on_Player_hit", &Main::_on_Player_hit);
}