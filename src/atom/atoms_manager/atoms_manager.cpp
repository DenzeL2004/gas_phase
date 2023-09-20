#include "atoms_manager.h"

//================================================================================

static const int Dir_variation = 100u;
static const double Start_atom_velocity = 1.0;

void AtomsManager::AddAtom (const AtomsType type, const double mass)
{
    Atom *obj = nullptr;  

    double coord_x = (double)(rand() % Dir_variation - Dir_variation / 2);
    double coord_y = (double)(rand() % Dir_variation - Dir_variation / 2);

    Vector dir(coord_x, coord_y);

    switch (type)
    {
        case ATOM_CIRCLE:
        {
            obj = new CircleAtom((left_up_ + right_down_) / 2.0, dir, Start_atom_velocity, mass);    
            break;
        }

        case ATOM_SQUARE:
        {
            obj = new SquareAtom((left_up_ + right_down_) / 2.0, dir, Start_atom_velocity, mass);
            break;
        }

        default:
            break;
    }

    atoms_.push_back(obj);

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
    size_t size = atoms_.size();

    for (size_t it = 0; it < size; it++)
    {
        if (atoms_[it] != nullptr)
        {
            if (this->CheckInFlask(*atoms_[it]))
            {
                atoms_[it]->Draw(window);
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

void AtomsManager::AtomsMovment ()
{
    size_t size = atoms_.size();

    for (size_t it = 0; it < size; it++)
    {
        if (atoms_[it] != nullptr)
        {
            atoms_[it]->Move();
            
            if (!this->CheckInFlask(*atoms_[it]))
            {
                cnt_strokes_++;
                this->CorrectMolPos(*atoms_[it]);
            }

            if (IsZero(atoms_[it]->GetVelocity()) && !IsZero(wall_temperature_))
                atoms_[it]->SetVelocity(wall_temperature_);
        }
    }

    this->Collision();

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
    mol.SetVelocity(wall_temperature_);

    return;
}

//================================================================================

double AtomsManager::GetPreasure()
{
    static sf::Clock clock;
    double delta_time = (double)clock.getElapsedTime().asSeconds();

    double preasure = (double)cnt_strokes_ / delta_time;

    cnt_strokes_ = 0;

    clock.restart();

    return preasure;   
}

//================================================================================

double AtomsManager::GetTemperature() const
{
    double temperature = 0;

    size_t size = atoms_.size();

    for (size_t it = 0; it < size; it++)
    {
        double velocity = atoms_[it]->GetVelocity();      
        double delta = atoms_[it]->GetMass() * velocity * velocity;

        temperature += delta;
    }

    temperature /= (double)size;

    return temperature;   
}

//================================================================================

void AtomsManager::Collision ()
{
    size_t size = atoms_.size();

    for (size_t it = 0; it < size; it++)
    {
        for (size_t jt = it + 1; jt < size; jt++)
        {
            if (atoms_[jt] == nullptr) continue;

            if (atoms_[it]->CheckCollision(*atoms_[jt]))
            {
                this->MakeReaction(atoms_[it], atoms_[jt]);
                delete atoms_[it];
                delete atoms_[jt];

                atoms_[it] = atoms_[jt] = nullptr;
                std::swap(atoms_[it], atoms_[atoms_.size() - 1]);
                std::swap(atoms_[jt], atoms_[atoms_.size() - 2]);

                atoms_.pop_back();
                atoms_.pop_back();

                break;
            }
        }
    }
    

    return;
}

void AtomsManager::MakeReaction (Atom *rhs, Atom *lhs)
{
    double mass = (rhs->GetMass() +  lhs->GetMass());
    size_t size = atoms_.size();

    if (rhs->type_ == ATOM_SQUARE && lhs->type_ == ATOM_SQUARE)
    {
        for (size_t it = 0; it < (size_t)mass; it++)
        {
            this->AddAtom(ATOM_CIRCLE, 1.0);
            
            atoms_[size]->SetPos((rhs->GetPos() + lhs->GetPos()) / 2);
            size++;
        }


        return;
    }
    
    this->AddAtom(ATOM_SQUARE, mass);
    atoms_[size]->SetPos((rhs->GetPos() + lhs->GetPos()) / 2);

    return;
}