#ifndef _MOLECULES_H_
#define _MOLECULES_H_

#include "../vector/vector.h"
#include "../graphic/graphic.h"

class Molecule
{
    public:

        Molecule (const Dot &pos, const Vector &dir, 
                  const double mass, const double velocity);


        virtual ~Molecule() = default;

        virtual void Draw(sf::RenderWindow &window) const = 0;

        virtual float   GetSize() const {return 0.0;};

        Dot     GetPos()  const {return pos_;};
        Vector  GetDir()  const {return dir_;};
        double  GetMass() const {return mass_;};

        void Move() 
        {
            pos_ += dir_ * velocity_; 
            return;
        }

        void SetDir(const Vector &dir) 
        {
            dir_ = dir; 
            return;
        }

        void SetPos(const Dot &pos) 
        {
            pos_ = pos; 
            return;
        }

        void SetVelocity(const double temprature) 
        {
            
            velocity_ = sqrt((3 * temprature) / mass_);
            return;
        }

    protected:
        Dot pos_;
        Vector dir_;
        double mass_;
        double velocity_;
};

class CircleMolecule : public Molecule
{   
    public:

        CircleMolecule (const Dot &pos, const Vector &dir, 
                        const double velocity):Molecule(pos, dir, Mol_mass, velocity){} 

        void Draw (sf::RenderWindow &window) const override;

        float GetSize() const override {return Mol_Radius;};

    private:
        static constexpr float  Mol_Radius = 25.4f;
        static constexpr double Mol_mass = 1.0; 
};

class SquareMolecule : public Molecule
{   
    public:

        SquareMolecule (const Dot &pos, const Vector &dir, 
                        const double velocity):Molecule(pos, dir, Mol_mass, velocity){} 

        void Draw (sf::RenderWindow &window) const override;

        float GetSize() const override {return Mol_Side / 2.f;};

    private:
        static constexpr float  Mol_Side = 50.0f;
        static constexpr double Mol_mass = 2.0f; 
};

enum MoleculesType
{
    MOL_CIRCLE = 1,
    MOL_SQUARE = 2
};

#endif //_MOLECULES_H_