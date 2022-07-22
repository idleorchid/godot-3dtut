#include "player.hpp"

void Player::_ready()
{
    _input = godot::Input::get_singleton();
    _pivot = get_node<godot::Spatial>("Pivot");
}

void Player::_physics_process(const float delta)
{
    godot::Vector3 direction = godot::Vector3::ZERO;
    if (_input->is_action_pressed("move_right"))
    {
        direction.x += 1;
    }
    if (_input->is_action_pressed("move_left"))
    {
        direction.x -= 1;
    }
    if (_input->is_action_pressed("move_back"))
    {
        direction.z += 1;
    }
    if (_input->is_action_pressed("move_forward"))
    {
        direction.z -= 1;
    }

    if (direction != godot::Vector3::ZERO)
    {
        direction = direction.normalized();
        _pivot->look_at(get_translation() + direction, godot::Vector3::UP);
    }
    _velocity.x = direction.x * speed;
    _velocity.z = direction.z * speed;
    _velocity.y -= fallAcceleration * delta;
    _velocity = move_and_slide(_velocity, godot::Vector3::UP);
}

void Player::_register_methods()
{
    godot::register_property<Player, int>("speed", &Player::speed, 14);
    godot::register_property<Player, int>("fallAcceleration", &Player::fallAcceleration, 75);
    godot::register_method("_physics_process", &Player::_physics_process);
    godot::register_method("_ready", &Player::_ready);
}