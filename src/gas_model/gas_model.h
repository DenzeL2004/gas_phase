#ifndef _GAS_MODEL_H_
#define _GAS_MODEL_H_

#include "../graphic/button/button.h"
#include "../atom/atoms_manager/atoms_manager.h"

class GasModel
{       
    public:
        GasModel(const AtomsManager &atoms_manager):atoms_manager_(atoms_manager), buttons_manager_(){}

        ~GasModel() = default;

        
        void Show (sf::RenderWindow &window);

    private:
        void Example();

        void DrawEnvironment        (sf::RenderWindow &window);

        void DrawTemperatureChart   (sf::RenderWindow &window) const;

        void DrawPerssureGraphic    (sf::RenderWindow &window);

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
            atoms_manager_->AddAtom(type_, 1.0);
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

class ChangeDegree : public Action
{
    public:
        ChangeDegree(const double delta, AtomsManager *ptr):delta_(delta), atoms_manager_(ptr) {};
        ~ChangeDegree() = default;

        bool operator() () const
        {
            double temprature = atoms_manager_->GetWallTemperature();
            temprature += delta_;

            temprature = std::max(temprature, 0.0);
            atoms_manager_->SetWallTemperature(temprature);

            return false;
        } 

    private:
        double delta_;
        AtomsManager *atoms_manager_;
};

//==============================================================================

class ButtonState : public Action
{
    public:
        ButtonState(){};
        ~ButtonState() = default;

        bool operator() () const
        {   
            return true;
        } 
};

#endif