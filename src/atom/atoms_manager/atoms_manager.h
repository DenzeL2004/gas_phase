#ifndef _ATOMS_MANAGER_H_
#define _ATOMS_MANAGER_H_

#include "../atom.h"
#include "../../graphic/button/button.h"

const Dot Defaulte_mol_dir = Dot(-10.0, 03.0, 0.0); 

class AtomsManager
{

    public:

        AtomsManager (const Dot &left_up, const Dot &right_down, 
                          const double temperature, const double piston_height): 
                          left_up_(left_up), right_down_(right_down),
                          temperature_(temperature), piston_height_(piston_height), Atoms_(){}

        ~AtomsManager ()
        {
            for (size_t it = 0; it < Atoms_.size(); it++)
            {
                if (Atoms_[it] != nullptr)
                    delete Atoms_[it];
            }
                return;
        }

        void AddAtom (const AtomsType type);

        void Show        (sf::RenderWindow &window) const;

        void AtomsMovment () const;

    private:

        void DrawEnvironment (sf::RenderWindow &window) const;

        void DrawAtoms  (sf::RenderWindow &window) const;

        bool CheckInFlask   (const Atom &mol) const;

        void CorrectMolPos  (Atom &mol) const;


        Dot left_up_, right_down_;
        double temperature_,  piston_height_;

        std::vector<Atom*> Atoms_;
};

class NewCircleAtom : public Action
{
    public:
        NewCircleAtom(AtomsManager *ptr):atoms_manager_(ptr) {};
        ~NewCircleAtom() = default;

        bool operator() () const
        {
            atoms_manager_->AddAtom(ATOM_CIRCLE);
            return false;
        } 

    private:
        AtomsManager *atoms_manager_;
};

class NewSquareAtom : public Action
{
    public:
        NewSquareAtom(AtomsManager *ptr):atoms_manager_(ptr) {};
        ~NewSquareAtom() = default;

        bool operator() () const
        {
            atoms_manager_->AddAtom(ATOM_SQUARE);
            return false;
        } 

    private:
        AtomsManager *atoms_manager_;
};



#endif //_ATOMS_MANAGER_H_