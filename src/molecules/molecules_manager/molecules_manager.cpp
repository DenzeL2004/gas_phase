#include "molecules_manager.h"

//================================================================================

void MoleculesManager::AddMolecule (const MoleculesType type)
{
    Molecule *obj = nullptr;  

    Vector dir((double)(rand() % 10 - 5), (double)(rand() % 10 - 5));

    switch (type)
    {
        case MOL_CIRCLE:
        {
            obj = new CircleMolecule((left_up_ + right_down_) / 2.0, dir);    
            break;
        }

        case MOL_SQUARE:
        {
            obj = new SquareMolecule((left_up_ + right_down_) / 2.0, dir);
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

void MoleculesManager::MoleculesMovment () const
{
    for (size_t it = 0; it < molecules_.size(); it++)
    {
        if (molecules_[it] != nullptr)
        {
            molecules_[it]->Move();
            
            if (!this->CheckInFlask(*molecules_[it]))
            {
                this->CorrectMolPos(*molecules_[it]);

            }
        }
    }

    return;
}

//================================================================================

void MoleculesManager::CorrectMolPos  (Molecule &mol) const
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

    return;
}

//================================================================================