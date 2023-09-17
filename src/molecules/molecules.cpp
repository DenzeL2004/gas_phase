#include "molecules.h"

static const sf::Color Circle_def_color = sf::Color::Red;
static const sf::Color Square_def_color = sf::Color::Blue;

//================================================================================

void CircleMolecule::Draw (sf::RenderWindow &window) const
{
    DrawCircle(window, pos_, Mol_Radius, Circle_def_color);
    
    return;
}

//================================================================================

void SquareMolecule::Draw (sf::RenderWindow &window) const
{

    float  scale = Mol_Side / sqrt(2.f);

    Dot left_up    = pos_ + Vector(-1.0, 1.0, 0.0) * scale;
    Dot right_down = pos_ + Vector(1.0, -1.0, 0.0) * scale;
    
    DrawRectangle(window, left_up, right_down, Square_def_color);

    return;
}


//================================================================================