#include "molecules_manager.h"

//================================================================================

void MoleculesManager::AddMolecule (const MoleculesType type)
{
    Molecule *obj = nullptr;  

    switch (type)
    {
        case MOL_CIRCLE:
        {
            obj = new CircleMolecule((left_up_ + right_down_) / 2.0, Defaulte_mol_dir);    
            break;
        }

        case MOL_SQUARE:
        {
            obj = new SquareMolecule((left_up_ + right_down_) / 2.0, Defaulte_mol_dir);
            break;
        }

        default:
            break;
    }

    molecules_.push_back(obj);

    return;
}

//================================================================================

void MoleculesManager::Show (sf::RenderWindow &window) const
{
    this->DrawEnvironment(window);
    this->DrawMolecules(window);

    return;
}

//================================================================================

void  MoleculesManager::DrawEnvironment (sf::RenderWindow &window) const
{
    DrawRectangle(window, left_up_, Dot(right_down_.GetX(), left_up_.GetY() + piston_height_), Brown);


    DrawLine(window, left_up_, Dot(right_down_.GetX(), left_up_.GetY()), sf::Color::White);
    DrawLine(window, left_up_, Dot(left_up_.GetX(), right_down_.GetY()), sf::Color::White);

    DrawLine(window, right_down_, Dot(right_down_.GetX(), left_up_.GetY()), sf::Color::White);
    DrawLine(window, right_down_, Dot(left_up_.GetX(), right_down_.GetY()), sf::Color::White);

    return;

}

void MoleculesManager::DrawMolecules (sf::RenderWindow &window) const
{
    for (size_t it = 0; it < molecules_.size(); it++)
    {
        if (molecules_[it] != nullptr)
        {
            if (this->CheckInFlask(*molecules_[it]))
            {
                molecules_[it]->Draw(window);
            }
        }
    }

    return;
}


//================================================================================

bool MoleculesManager::CheckInFlask (const Molecule &mol) const
{
    double size = (double)mol.GetSize();

    double left_border  = left_up_.GetX() + 2.0 * size;
    double right_border = right_down_.GetX() -  2.0 * size;

    double up_border   = left_up_.GetY() + piston_height_ + size;
    double down_border = right_down_.GetY() - 2.0 * size;
    
    Dot pos = mol.GetPos();

    bool res = (left_border < pos.GetX() && pos.GetX() < right_border && 
                up_border   < pos.GetY() && pos.GetY() < down_border);

    return res;
}


//================================================================================

void MoleculesManager::MoleculesMovment () const
{
    for (size_t it = 0; it < molecules_.size(); it++)
    {
        if (molecules_[it] != nullptr)
        {
            molecules_[it]->Move();
        }
    }

    return;
}