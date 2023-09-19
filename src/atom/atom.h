#ifndef _ATOM_H_
#define _ATOM_H_

#include "../vector/vector.h"
#include "../graphic/graphic.h"

class Atom
{
    public:

        Atom (const Dot &pos, const Vector &dir, 
                  const double mass, const double velocity);


        virtual ~Atom() = default;

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

class CircleAtom : public Atom
{   
    public:

        CircleAtom (const Dot &pos, const Vector &dir, 
                        const double velocity):Atom(pos, dir, Mol_mass, velocity){} 

        void Draw (sf::RenderWindow &window) const override;

        float GetSize() const override {return Mol_Radius;};


    private:
        static constexpr float  Mol_Radius = 25.4f;
        static constexpr double Mol_mass = 1.0; 
};

class SquareAtom : public Atom
{   
    public:

        SquareAtom (const Dot &pos, const Vector &dir, 
                        const double velocity):Atom(pos, dir, Mol_mass, velocity){} 

        void Draw (sf::RenderWindow &window) const override;

        float GetSize() const override {return Mol_Side / 2.f;};

    private:
        static constexpr float  Mol_Side = 50.0f;
        static constexpr double Mol_mass = 2.0f; 
};

enum AtomsType
{
    ATOM_CIRCLE = 1,
    ATOM_SQUARE = 2
};

#endif //_AtomS_H_