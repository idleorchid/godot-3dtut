#ifndef MOB_H
#define MOB_H

#include <Godot.hpp>
#include <Input.hpp>
#include <KinematicBody.hpp>
#include <Vector3.hpp>
#include <Spatial.hpp>

class Mob : public godot::KinematicBody
{
    GODOT_CLASS(Mob, godot::KinematicBody)

    godot::Vector3 _velocity = godot::Vector3::ZERO;

public:
    int minSpeed = 10;
    int maxSpeed = 18;

    void _init(){};
    void initialize(godot::Vector3 startPosition, godot::Vector3 playerPosition);
    void _physics_process(const float delta);
    void _onVisibilityNotifier_screen_exited();
    static void _register_methods();
};

#endif // MOB_H