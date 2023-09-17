#ifndef _MOLECULES_H_
#define _MOLECULES_H_

#include "../vector/vector.h"
#include "../graphic/graphic.h"

class Molecule
{
    public:

        Molecule (const Vector &pos, const Vector &dir): pos_(pos), dir_(dir){} 

        virtual ~Molecule() = default;

        virtual void Draw(sf::RenderWindow &window) const = 0;

    protected:
        Vector pos_;
        Vector dir_;

};

class CircleMolecule : public Molecule
{   
    public:

        CircleMolecule (const Vector &pos, const Vector &dir):Molecule(pos, dir){} 

        void Draw (sf::RenderWindow &window) const override;

    private:
        static constexpr float Mol_Radius = 14.4f; 
};

class SquareMolecule : public Molecule
{   
    public:

        SquareMolecule (const Vector &pos, const Vector &dir):Molecule(pos, dir){} 

        void Draw (sf::RenderWindow &window) const override;

    private:
        static constexpr float Mol_Side = 20.0f;
};

enum MoleculesType
{
    MOL_CIRCLE = 1,
    MOL_SQUARE = 2
};

#endif //_MOLECULES_H_