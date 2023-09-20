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

static const double reaction_velocity = 3.0; 

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
            velocity_ = sqrt( temprature / mass_);
            return;
        }

        bool CheckCollision (const Atom &other)
        {
            Vector dist = other.pos_ - pos_;

            return (dist.Len() < this->GetSize() || dist.Len() < other.GetSize()) &&
                    velocity_ > reaction_velocity && other.velocity_ > reaction_velocity;
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
                        const double velocity, const double mass = Mol_mass):Atom(pos, dir, mass, velocity, ATOM_CIRCLE){} 

        void Draw (sf::RenderWindow &window) const override;

        float GetSize() const override {return Mol_Radius;};

    private:
        static constexpr float  Mol_Radius = 25.5f;
        static constexpr double Mol_mass = 1.0; 
};

class SquareAtom : public Atom
{   
    public:

        SquareAtom (const Dot &pos, const Vector &dir, 
                        const double velocity, const double mass = Mol_mass):Atom(pos, dir, mass, velocity, ATOM_SQUARE){}  

        void Draw (sf::RenderWindow &window) const override;

        float GetSize() const override {return Mol_Side / 2.f;};

    private:
        static constexpr float  Mol_Side = 50.0f;
        static constexpr double Mol_mass = 2.0f; 
};



#endif //_AtomS_H_