#include "atoms_manager.h"

//================================================================================

static const size_t Dir_variation = 40u;
static const double Start_atom_velocity = 1.0;

void AtomsManager::AddAtom (const AtomsType type)
{
    Atom *obj = nullptr;  

    double coord_x = (double)((rand() % Dir_variation) - Dir_variation / 2);
    double coord_y = (double)((rand() % Dir_variation) - Dir_variation / 2);

    Vector dir(coord_x, coord_y);

    switch (type)
    {
        case ATOM_CIRCLE:
        {
            obj = new CircleAtom((left_up_ + right_down_) / 2.0, dir, Start_atom_velocity);    
            break;
        }

        case ATOM_SQUARE:
        {
            obj = new SquareAtom((left_up_ + right_down_) / 2.0, dir, Start_atom_velocity);
            break;
        }

        default:
            break;
    }

    Atoms_.push_back(obj);

    return;
}

//================================================================================

void AtomsManager::Show (sf::RenderWindow &window) const
{
    this->DrawEnvironment(window);
    this->DrawAtoms(window);

    return;
}

//================================================================================

void  AtomsManager::DrawEnvironment (sf::RenderWindow &window) const
{
    DrawRectangle(window, left_up_, Dot(right_down_.GetX(), left_up_.GetY() + piston_height_), Brown);

    DrawLine(window, left_up_, Dot(right_down_.GetX(), left_up_.GetY()), sf::Color::White);
    DrawLine(window, left_up_, Dot(left_up_.GetX(), right_down_.GetY()), sf::Color::White);

    DrawLine(window, right_down_, Dot(right_down_.GetX(), left_up_.GetY()), sf::Color::White);
    DrawLine(window, right_down_, Dot(left_up_.GetX(), right_down_.GetY()), sf::Color::White);

    return;

}

void AtomsManager::DrawAtoms (sf::RenderWindow &window) const
{
    for (size_t it = 0; it < Atoms_.size(); it++)
    {
        if (Atoms_[it] != nullptr)
        {
            if (this->CheckInFlask(*Atoms_[it]))
            {
                Atoms_[it]->Draw(window);
            }
        }
    }

    return;
}


//================================================================================

bool AtomsManager::CheckInFlask (const Atom &mol) const
{
    double size = (double)mol.GetSize();

    double left_border  = left_up_.GetX()    + size;
    double right_border = right_down_.GetX() - size;

    double up_border   = left_up_.GetY()    + piston_height_ + size;
    double down_border = right_down_.GetY() - size;
    
    Dot pos = mol.GetPos();

    bool res = (left_border < pos.GetX() && pos.GetX() < right_border && 
                up_border   < pos.GetY() && pos.GetY() < down_border);

    return res;
}


//================================================================================

void AtomsManager::AtomsMovment () const
{
    for (size_t it = 0; it < Atoms_.size(); it++)
    {
        if (Atoms_[it] != nullptr)
        {
            Atoms_[it]->Move();
            
            if (!this->CheckInFlask(*Atoms_[it]))
            {
                this->CorrectMolPos(*Atoms_[it]);

            }
        }
    }

    return;
}

//================================================================================

void AtomsManager::CorrectMolPos  (Atom &mol) const
{
    double size = (double)mol.GetSize();

    double new_x = mol.GetPos().GetX();
    double new_y = mol.GetPos().GetY();

    double left_border  = left_up_.GetX() + size;
    double right_border = right_down_.GetX() - size;

    double up_border   = left_up_.GetY() + piston_height_ + size;
    double down_border = right_down_.GetY() - size;

    Vector new_dir = mol.GetDir() * -1.0;

    if (left_border > new_x)
    {
        new_x = left_border + 1.0;
        new_dir = new_dir.Reflection(Vector(0.0, left_up_.GetY() - right_down_.GetY()));
    }

    if (right_border < new_x)
    {
        new_x = right_border - 1.0;
        new_dir = new_dir.Reflection(Vector(0.0, right_down_.GetY() - left_up_.GetY()));
    }


    if (up_border > new_y)
    {
        new_y = up_border + 1.0;
        new_dir = new_dir.Reflection(Vector(right_down_.GetX() - left_up_.GetX(), 0.0));
    }

    if (down_border < new_y) 
    {
        new_y = down_border - 1.0;
        new_dir = new_dir.Reflection(Vector(left_up_.GetX() - right_down_.GetX(), 0.0));
    }

   if (new_dir == mol.GetDir()) new_dir *= -1.0;

    mol.SetPos(Dot(new_x, new_y));
    mol.SetDir(new_dir);
    mol.SetVelocity(temperature_);

    return;
}

//================================================================================