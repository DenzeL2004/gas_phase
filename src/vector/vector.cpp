#include "vector.h"

//=======================================================================

Vector& Vector::operator = (const Vector &other)
{
    this->x_ = other.x_;
    this->y_ = other.y_;
    this->z_ = other.z_;

    return *this;
}

//=======================================================================

Vector& Vector::operator += (const Vector &other)
{
    this->x_ += other.x_;
    this->y_ += other.y_;
    this->z_ += other.z_;

    return *this;
}

//=======================================================================

Vector& Vector::operator -= (const Vector &other)
{
    this->x_ -= other.x_;
    this->y_ -= other.y_;
    this->z_ -= other.z_;

    return *this;
}

//=======================================================================

Vector& Vector::operator *= (const double scale)
{
    this->x_ *= scale;
    this->y_ *= scale;
    this->z_ *= scale;

    return *this;
}

//=======================================================================

Vector& Vector::operator /= (const double scale)
{
    this->x_ /= scale;
    this->y_ /= scale;
    this->z_ /= scale;

    return *this;
}

//=======================================================================

Vector& Vector::operator *= (const Vector &other)
{
    x_ *= other.x_;
    y_ *= other.y_;
    z_ *= other.z_;

    return *this;
}

Vector operator * (const Vector &lhs, const Vector &rhs)
{
    Vector res = lhs;
    res *= rhs;

    return res;
}

//=======================================================================

double Vector::Len () const
{
    double len = this->Dot(*this);
    
    len = sqrt(len);

    return len;
}

//=======================================================================


Vector Vector::Normal () const
{
    Vector res(*this / this->Len());

    return res;
}


//=======================================================================

double Vector::Dot (const Vector &vec) const
{
    return  vec.x_ * this->x_ + 
            vec.y_ * this->y_ +
            vec.z_ * this->z_;
}

//=======================================================================

Vector operator + (const Vector &vec1, const Vector &vec2)
{
    Vector res = vec1;
    res += vec2;

    return res;
}

//=======================================================================

Vector operator - (const Vector &vec1, const Vector &vec2)
{
    Vector res = vec1;
    res -= vec2;
    
    return res;
}

//=======================================================================

Vector operator * (const Vector &vec, const double scale)
{
    Vector res = vec;
    res *= scale;

    return res;
}

Vector operator * (const double scale, const Vector &vec)
{
    Vector res = vec;
    res *= scale;

    return res;
}

//=======================================================================

Vector operator / (const Vector &vec, const double scale)
{
    Vector res = vec;
    res /= scale;

    return res;
}


//=======================================================================
