#include "player.hpp"
#include <KinematicCollision.hpp>
#include "mob.hpp"

#include <iostream>
#include <string>

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
    if (is_on_floor() && _input->is_action_just_pressed("jump"))
    {
        _velocity.y += jumpImpulse;
    }
    _velocity = move_and_slide(_velocity, godot::Vector3::UP);
    for (int i = 0; i < get_slide_count(); i++)
    {
        godot::KinematicCollision *collision = get_slide_collision(i).ptr();
        Mob *mob = Object::cast_to<Mob>(collision->get_collider());
        if (mob && mob->is_in_group("mob"))
        {
            if (godot::Vector3::UP.dot(collision->get_normal()) > 0.1)
            {
                mob->squash();
                _velocity.y = bounceImpulse;
            }
        }
    }
}

void Player::_register_methods()
{
    godot::register_property<Player, int>("speed", &Player::speed, 14);
    godot::register_property<Player, int>("fallAcceleration", &Player::fallAcceleration, 75);
    godot::register_property<Player, int>("jumpImpulse", &Player::jumpImpulse, 20);
    godot::register_property<Player, int>("bounceImpulse", &Player::bounceImpulse, 16);
    godot::register_method("_physics_process", &Player::_physics_process);
    godot::register_method("_ready", &Player::_ready);
}