#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <Input.hpp>
#include <KinematicBody.hpp>
#include <Vector3.hpp>
#include <Spatial.hpp>

class Player : public godot::KinematicBody
{
    GODOT_CLASS(Player, godot::KinematicBody)

    godot::Vector3 _velocity = godot::Vector3::ZERO;
    godot::Input *_input;
    godot::Spatial *_pivot;

public:
    int speed = 14;
    int fallAcceleration = 75;

    void _init(){};
    void _ready();
    void _physics_process(const float delta);

    static void _register_methods();
};

#endif // PLAYER_H