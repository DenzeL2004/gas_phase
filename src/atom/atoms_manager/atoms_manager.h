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
                      piston_height_(piston_height), wall_temperature_(temperature), cnt_strokes_(0), Atoms_(){}

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

        void Show         (sf::RenderWindow &window) const;

        void AtomsMovment ();

        Dot GetLeftUp    () const {return left_up_;}

        double GetWidth  () const {return right_down_.GetX() - left_up_.GetX();}
        double GetHieght () const {return right_down_.GetY() - left_up_.GetY();}
        
        //double GetTemperature   () const {return temperature_;}
        double GetPristonHieght () const {return piston_height_;}

        double GetPreasure (); 
        

        void SetPristonHieght (const double hieght)
        {
            piston_height_ = hieght;
            return;
        }

    private:

        void DrawEnvironment (sf::RenderWindow &window) const;

        void DrawAtoms  (sf::RenderWindow &window) const;

        bool CheckInFlask   (const Atom &mol) const;

        void CorrectMolPos  (Atom &mol) const;


        Dot left_up_, right_down_;
        double piston_height_;
        double wall_temperature_;
        size_t cnt_strokes_;

        std::vector<Atom*> Atoms_;
};



#endif //_ATOMS_MANAGER_H_