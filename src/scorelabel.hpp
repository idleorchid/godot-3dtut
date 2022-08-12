#ifndef SCORELABEL_H
#define SCORELABEL_H

#include <Godot.hpp>
#include <Label.hpp>

class ScoreLabel : public godot::Label
{

    GODOT_CLASS(ScoreLabel, godot::Label)

    int _score = 0;

public:
    void _init(){};
    void _on_Mob_squashed();
    static void _register_methods();
};

#endif // SCORELABEL_H