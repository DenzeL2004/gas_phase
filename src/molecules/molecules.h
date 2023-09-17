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

        virtual float   GetSize() const {return 0.0;};
        Dot     GetPos()  const {return pos_;};
        Vector  GetDir()  const {return dir_;};

        void Move() 
        {
            pos_ += dir_; 
            return;
        }

        void SetDir(const Vector &dir) 
        {
            dir_ = dir; 
            return;
        }

    protected:
        Dot pos_;
        Vector dir_;

};

class CircleMolecule : public Molecule
{   
    public:

        CircleMolecule (const Vector &pos, const Vector &dir):Molecule(pos, dir){} 

        void Draw (sf::RenderWindow &window) const override;

        float GetSize() const override {return Mol_Radius;};

    private:
        static constexpr float Mol_Radius = 24.4f; 
};

class SquareMolecule : public Molecule
{   
    public:

        SquareMolecule (const Vector &pos, const Vector &dir):Molecule(pos, dir){} 

        void Draw (sf::RenderWindow &window) const override;

        float GetSize() const override {return Mol_Side / 2.f;};

    private:
        static constexpr float Mol_Side = 50.0f;
};

enum MoleculesType
{
    MOL_CIRCLE = 1,
    MOL_SQUARE = 2
};

#endif //_MOLECULES_H_