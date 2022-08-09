#ifndef MAIN_H
#define MAIN_H

#include <Godot.hpp>
#include <Node.hpp>
#include <PackedScene.hpp>
#include <PathFollow.hpp>
#include <RandomNumberGenerator.hpp>

#include "player.hpp"
#include "mob.hpp"

class Main : public godot::Node
{
    GODOT_CLASS(Main, godot::Node)

    Player *_player;
    godot::PathFollow *_mob_spawn_location;
    godot::Ref<godot::RandomNumberGenerator> _random;

public:
    godot::Ref<godot::PackedScene> mob_scene;

    void _init(){};
    void _ready();
    void _on_MobTimer_timeout();

    static void _register_methods();
};
#endif // MAIN_H