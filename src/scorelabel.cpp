#include "scorelabel.hpp"

void ScoreLabel::_on_Mob_squashed()
{
    _score++;
    set_text("Score: " + godot::String::num_int64(_score));
}

void ScoreLabel::_register_methods()
{
    godot::register_method("_on_Mob_squashed", &ScoreLabel::_on_Mob_squashed);
}