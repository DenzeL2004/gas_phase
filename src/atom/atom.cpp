#include "atom.h"

static const sf::Color Circle_def_color = sf::Color::Red;
static const sf::Color Circle_strike_color = Orange;

static const sf::Color Square_def_color = sf::Color::Blue;
static const sf::Color Square_strike_color = sf::Color::Cyan;

//================================================================================

Atom::Atom (const Dot &pos, const Vector &dir, 
                    const double mass, const double velocity, const AtomsType type):
            type_(type), pos_(), dir_(), mass_(NAN), velocity_(NAN), radius_(0.f)
{
    if (mass < 0.0)
    {
        fprintf(stderr, "particle mass negative, construct failed");
        return;
    }

    pos_ = pos;
    dir_ = dir.Normal();
    mass_ = mass;

    radius_ = (float)mass * 10.f;

    velocity_ = velocity;

    return;
}


//================================================================================

void CircleAtom::Draw (sf::RenderWindow &window) const
{
    Dot shift_dot(pos_.GetX() - (double)radius_, 
                  pos_.GetY() - (double)radius_);

    DrawCircle(window, shift_dot, radius_, Circle_strike_color);

    shift_dot = Dot(pos_.GetX() - (double)radius_ / 2.0, 
                    pos_.GetY() - (double)radius_ / 2.0);

    DrawCircle(window, shift_dot, radius_ / 2.f, Circle_def_color);
    
    return;
}

//================================================================================

void SquareAtom::Draw (sf::RenderWindow &window) const
{


    Dot left_up    = pos_ + Vector(-1.0, -1.0, 0.0) * (radius_);
    Dot right_down = pos_ + Vector(1.0, 1.0, 0.0)   * (radius_ );
    
    DrawRectangle(window, left_up, right_down, Square_strike_color);

    left_up    = pos_ + Vector(-1.0, -1.0, 0.0) * (radius_ / 2.0);
    right_down = pos_ + Vector(1.0, 1.0, 0.0)   * (radius_ / 2.0);

    DrawRectangle(window, left_up, right_down, Square_def_color);

    return;
}


//================================================================================