#include "mob.hpp"
#include <RandomNumberGenerator.hpp>
#include <math.h>

void Mob::initialize(godot::Vector3 startPosition, godot::Vector3 playerPosition)
{
    look_at_from_position(startPosition, playerPosition, godot::Vector3::UP);

    godot::Ref<godot::RandomNumberGenerator> random = godot::RandomNumberGenerator::_new();
    random->randomize();
    rotate_y(random->randi_range(-M_PI / 4, M_PI / 4));

    float randomSpeed = random->randi_range(minSpeed, maxSpeed);
    _velocity = godot::Vector3::FORWARD * randomSpeed;
    _velocity = _velocity.rotated(godot::Vector3::UP, get_rotation().y);
}
void Mob::_physics_process(const float delta)
{
    move_and_slide(_velocity);
}

void Mob::_onVisibilityNotifier_screen_exited()
{
    queue_free();
}

void Mob::_register_methods()
{
    godot::register_property<Mob, int>("minSpeed", &Mob::minSpeed, 10);
    godot::register_property<Mob, int>("maxSpeed", &Mob::maxSpeed, 18);
    godot::register_method("_physics_process", &Mob::_physics_process);
    godot::register_method("initialize", &Mob::initialize);
    godot::register_method("_onVisibilityNotifier_screen_exited", &Mob::_onVisibilityNotifier_screen_exited);
}