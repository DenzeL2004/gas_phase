#ifndef _ATOM_H_
#define _ATOM_H_

#include "../vector/vector.h"
#include "../graphic/graphic.h"

enum AtomsType
{
    ATOM_BASE   = 0,
    ATOM_CIRCLE = 1,
    ATOM_SQUARE = 2
};

class Atom
{
    public:

        Atom (const Dot &pos, const Vector &dir, 
                  const double mass, const double velocity, const AtomsType type);


        virtual ~Atom() = default;

        virtual void Draw(sf::RenderWindow &window) const = 0;

        virtual float GetSize() const = 0;

        Dot     GetPos()      const {return pos_;};
        Vector  GetDir()      const {return dir_;};
        double  GetMass()     const {return mass_;};
        double  GetVelocity() const {return velocity_;};


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

    const AtomsType type_;

    protected:
        Dot pos_;
        Vector dir_;
        double mass_;
        double velocity_;
};

class CircleAtom : public Atom
{   
    public:

        CircleAtom (const Dot &pos, const Vector &dir, 
                        const double velocity):Atom(pos, dir, Mol_mass, velocity, ATOM_CIRCLE){} 

        void Draw (sf::RenderWindow &window) const override;

        float GetSize() const override {return Mol_Radius;};

    private:
        static constexpr float  Mol_Radius = 12.5f;
        static constexpr double Mol_mass = 1.0; 
};

class SquareAtom : public Atom
{   
    public:

        SquareAtom (const Dot &pos, const Vector &dir, 
                        const double velocity):Atom(pos, dir, Mol_mass, velocity, ATOM_SQUARE){} 

        void Draw (sf::RenderWindow &window) const override;

        float GetSize() const override {return Mol_Side / 2.f;};

    private:
        static constexpr float  Mol_Side = 25.0f;
        static constexpr double Mol_mass = 2.0f; 
};



#endif //_AtomS_H_