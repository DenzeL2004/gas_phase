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
                      piston_height_(piston_height), wall_temperature_(temperature), cnt_strokes_(0), atoms_()
                      {this->GetPreasure(); return;}

        ~AtomsManager ()
        {
            size_t size = atoms_.size();
            for (size_t it = 0; it < size; it++)
            {
                if (atoms_[it] != nullptr)
                    delete atoms_[it];
            }
                return;
        }

        void AddAtom (const AtomsType type, const double mass);

        void Show         (sf::RenderWindow &window) const;

        void AtomsMovment ();

        Dot GetLeftUp    () const {return left_up_;}

        double GetWidth  () const {return right_down_.GetX() - left_up_.GetX();}
        double GetHieght () const {return right_down_.GetY() - left_up_.GetY();}
        
        double GetWallTemperature   () const {return wall_temperature_;}
        double GetPristonHieght     () const {return piston_height_;}

        double GetPreasure    (); 
        double GetTemperature () const; 
        

        void SetPristonHieght (const double hieght)
        {
            piston_height_ = hieght;
            return;
        }

        void SetWallTemperature (const double wall_temperature)
        {
            wall_temperature_ = wall_temperature;
            return;
        }

        bool CheckCollision (const Atom *lhs, const Atom *rhs)
        {
            Vector dist = lhs->GetPos() - rhs->GetPos();

            return (dist.Len() < lhs->GetSize() || dist.Len() < rhs->GetSize()) &&
                    lhs->GetVelocity() > reaction_velocity && rhs->GetVelocity() > reaction_velocity;
        }

    private:

        void DrawEnvironment (sf::RenderWindow &window) const;

        void DrawAtoms       (sf::RenderWindow &window) const;

        bool CheckInFlask    (const Atom &mol) const;

        void CorrectMolPos   (Atom &mol) const;

        void Collision ();

        

        void MakeReaction           (const Atom *rhs, const Atom *lhs);

        void ReactionCircleCircle   (const Atom *lhs, const Atom *rhs);
        void ReactionCircleSquare   (const Atom *lhs, const Atom *rhs);
        void ReactionSquareCircle   (const Atom *lhs, const Atom *rhs);
        void ReactionSquareSquare   (const Atom *lhs, const Atom *rhs);



        Dot left_up_, right_down_;
        double piston_height_;
        double wall_temperature_;
        size_t cnt_strokes_;

        std::vector<Atom*> atoms_;
};


#endif //_ATOMS_MANAGER_H_