#ifndef _MOLECULES_MANAGER_H_
#define _MOLECULES_MANAGER_H_

#include "../molecules.h"

const Dot Defaulte_mol_dir = Dot(0.0, 1.0, 0.0); 

class MoleculesManager
{

    public:

        MoleculesManager (const Dot &left_up, const Dot &right_down, 
                          const double temperature, const double piston_height): 
                          left_up_(left_up), right_down_(right_down),
                          temperature_(temperature), piston_height_(piston_height), molecules_(){}

        ~MoleculesManager ()
        {
            for (size_t it = 0; it < molecules_.size(); it++)
            {
                if (molecules_[it] != nullptr)
                    delete molecules_[it];
            }
                return;
        }

        void AddMolecule (const MoleculesType type);

        void Show        (sf::RenderWindow &window) const;

        void MoleculesMovment () const;

    private:

        void DrawEnvironment (sf::RenderWindow &window) const;

        void DrawMolecules (sf::RenderWindow &window) const;

        bool CheckInFlask (const Molecule &mol) const;


        Dot left_up_, right_down_;
        double temperature_,  piston_height_;

        std::vector<Molecule*> molecules_;
};

#endif //_MOLECULES_MANAGER_H_