#include "molecules.h"

static const sf::Color Circle_def_color = sf::Color::Red;
static const sf::Color Square_def_color = sf::Color::Blue;

//================================================================================

void CircleMolecule::Draw (sf::RenderWindow &window) const
{
    Dot shift_dot(pos_.GetX() - (double)Mol_Radius, 
                  pos_.GetY() - (double)Mol_Radius);
    DrawCircle(window, shift_dot, Mol_Radius, Circle_def_color);
    
    return;
}

//================================================================================

void SquareMolecule::Draw (sf::RenderWindow &window) const
{

    float  scale = Mol_Side / 2.0;

    Dot left_up    = pos_ + Vector(-1.0, -1.0, 0.0) * scale;
    Dot right_down = pos_ + Vector(1.0, 1.0, 0.0) * scale;
    
    DrawRectangle(window, left_up, right_down, Square_def_color);

    return;
}


//================================================================================