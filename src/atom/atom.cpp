#include "atom.h"

static const sf::Color Circle_def_color = sf::Color::Red;
static const sf::Color Circle_strike_color = Orange;

static const sf::Color Square_def_color = sf::Color::Blue;
static const sf::Color Square_strike_color = sf::Color::Cyan;

//================================================================================

Atom::Atom (const Dot &pos, const Vector &dir, 
                    const double mass, const double velocity)
{
    if (mass < 0.0)
    {
        fprintf(stderr, "particle mass negative, construct failed");
        return;
    }

    this->pos_ = pos;
    this->dir_ = dir.Normal();
    this->mass_ = mass;

    this->velocity_ = velocity;

    return;
}


//================================================================================

void CircleAtom::Draw (sf::RenderWindow &window) const
{
    Dot shift_dot(pos_.GetX() - (double)Mol_Radius, 
                  pos_.GetY() - (double)Mol_Radius);

    DrawCircle(window, shift_dot, Mol_Radius, Circle_strike_color);

    shift_dot = Dot(pos_.GetX() - (double)Mol_Radius / 2.0, 
                    pos_.GetY() - (double)Mol_Radius / 2.0);

    DrawCircle(window, shift_dot, Mol_Radius / 2.0, Circle_def_color);
    
    return;
}

//================================================================================

void SquareAtom::Draw (sf::RenderWindow &window) const
{


    Dot left_up    = pos_ + Vector(-1.0, -1.0, 0.0) * (Mol_Side / 2.0);
    Dot right_down = pos_ + Vector(1.0, 1.0, 0.0)   * (Mol_Side / 2.0);
    
    DrawRectangle(window, left_up, right_down, Square_strike_color);

    left_up    = pos_ + Vector(-1.0, -1.0, 0.0) * (Mol_Side / 4.0);
    right_down = pos_ + Vector(1.0, 1.0, 0.0)   * (Mol_Side / 4.0);

    DrawRectangle(window, left_up, right_down, Square_def_color);

    return;
}


//================================================================================