#ifndef _GAS_MODEL_H_
#define _GAS_MODEL_H_

#include "../graphic/button/button.h"
#include "../atom/atoms_manager/atoms_manager.h"

class GasModel
{       
    public:
        GasModel(const AtomsManager &atoms_manager);

        ~GasModel() = default;

        void Show (sf::RenderWindow &window);

    private:
        void DrawEnvironment(sf::RenderWindow &window) const;

        AtomsManager    atoms_manager_;
        ButtonsManager  buttons_manager_;
};

//==============================================================================

class NewAtom : public Action
{
    public:
        NewAtom(const AtomsType type, AtomsManager *ptr):type_(type), atoms_manager_(ptr) {};
        ~NewAtom() = default;

        bool operator() () const
        {
            atoms_manager_->AddAtom(type_);
            return false;
        } 

    private:
        AtomsType type_;
        AtomsManager *atoms_manager_;
};

//==============================================================================

class MovePiston : public Action
{
    public:
        MovePiston(const double delta, AtomsManager *ptr):delta_(delta), atoms_manager_(ptr) {};
        ~MovePiston() = default;

        bool operator() () const
        {
            double hieght = atoms_manager_->GetPristonHieght();
            hieght += delta_;

            hieght = std::max(std::min(hieght, atoms_manager_->GetHieght()), 0.0);
            atoms_manager_->SetPristonHieght(hieght);

            return false;
        } 

    private:
        double delta_;
        AtomsManager *atoms_manager_;
};

//==============================================================================

#endif