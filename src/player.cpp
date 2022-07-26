#include "player.hpp"
#include <KinematicCollision.hpp>
#include <AnimationPlayer.hpp>
#include "mob.hpp"

#include <iostream>
#include <string>
#include <math.h>

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

        get_node<godot::AnimationPlayer>("AnimationPlayer")->set_speed_scale(4);
    }
    else
    {
        get_node<godot::AnimationPlayer>("AnimationPlayer")->set_speed_scale(1);
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

    _pivot->set_rotation(godot::Vector3(M_PI / 6.0f * _velocity.y / jumpImpulse, _pivot->get_rotation().y, _pivot->get_rotation().z));
}

void Player::die()
{
    emit_signal("hit");
    queue_free();
}

void Player::_on_MobDetector_body_entered(godot::Node *body)
{
    die();
}

void Player::_register_methods()
{
    godot::register_property<Player, int>("speed", &Player::speed, 14);
    godot::register_property<Player, int>("fallAcceleration", &Player::fallAcceleration, 75);
    godot::register_property<Player, int>("jumpImpulse", &Player::jumpImpulse, 20);
    godot::register_property<Player, int>("bounceImpulse", &Player::bounceImpulse, 16);
    godot::register_signal<Player>((char *)"hit");
    godot::register_method("_physics_process", &Player::_physics_process);
    godot::register_method("_on_MobDetector_body_entered", &Player::_on_MobDetector_body_entered);
    godot::register_method("_ready", &Player::_ready);
}