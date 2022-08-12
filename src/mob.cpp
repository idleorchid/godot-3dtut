#include "mob.hpp"
#include <RandomNumberGenerator.hpp>
#include <AnimationPlayer.hpp>
#include <math.h>

void Mob::initialize(godot::Vector3 startPosition, godot::Vector3 playerPosition)
{
    look_at_from_position(startPosition, playerPosition, godot::Vector3::UP);

    godot::Ref<godot::RandomNumberGenerator> random = godot::RandomNumberGenerator::_new();
    random->randomize();
    rotate_y(random->randf_range(-M_PI / 4, M_PI / 4));

    float randomSpeed = random->randf_range(minSpeed, maxSpeed);
    _velocity = godot::Vector3::FORWARD * randomSpeed;

    _velocity = _velocity.rotated(godot::Vector3::UP, get_rotation().y);

    get_node<godot::AnimationPlayer>("AnimationPlayer")->set_speed_scale(randomSpeed / minSpeed);
}

void Mob::squash()
{
    emit_signal("squashed");
    queue_free();
}

void Mob::_physics_process(const float delta)
{
    move_and_slide(_velocity);
}

void Mob::_on_VisibilityNotifier_screen_exited()
{
    queue_free();
}

void Mob::_register_methods()
{
    godot::register_property<Mob, int>("minSpeed", &Mob::minSpeed, 10);
    godot::register_property<Mob, int>("maxSpeed", &Mob::maxSpeed, 18);
    godot::register_signal<Mob>((char *)"squashed");
    godot::register_method("_physics_process", &Mob::_physics_process);
    godot::register_method("initialize", &Mob::initialize);
    godot::register_method("squash", &Mob::squash);
    godot::register_method("_on_VisibilityNotifier_screen_exited", &Mob::_on_VisibilityNotifier_screen_exited);
}