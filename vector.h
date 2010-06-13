#ifndef __VECTOR_H
#define __VECTOR_H

#include <math.h>

typedef float scalar_t;  // skalar


class LVector
{
public:
     scalar_t x;
     scalar_t y;
     scalar_t z;  

public:

     LVector(scalar_t a = 0, scalar_t b = 0, scalar_t c = 0) : x(a), y(b), z(c) {}
     LVector(const LVector &vec) : x(vec.x), y(vec.y), z(vec.z) {}

     const LVector &operator=(const LVector &vec)
     {
          x = vec.x;
          y = vec.y;
          z = vec.z;

          return *this;
     }

     const bool operator==(const LVector &vec) const
     {
          return ((x == vec.x) && (y == vec.y) && (z == vec.z));
     }

     const bool operator!=(const LVector &vec) const
     {
          return !(*this == vec);
     }

     const LVector operator+(const LVector &vec) const
     {
          return LVector(x + vec.x, y + vec.y, z + vec.z);
     }

     const LVector operator+() const
     {    
          return LVector(*this);
     }

     const LVector& operator+=(const LVector& vec)
     {    x += vec.x;
          y += vec.y;
          z += vec.z;
          return *this;
     }

     const LVector operator-(const LVector& vec) const
     {    
          return LVector(x - vec.x, y - vec.y, z - vec.z);
     }
     
     const LVector operator-() const
     {    
          return LVector(-x, -y, -z);
     }

     const LVector &operator-=(const LVector& vec)
     {
          x -= vec.x;
          y -= vec.y;
          z -= vec.z;

          return *this;
     }

     const LVector &operator*=(const scalar_t &s)
     {
          x *= s;
          y *= s;
          z *= s;
          
          return *this;
     }

     const LVector &operator/=(const scalar_t &s)
     {
          const float recip = 1/s; // dla efektywnoœci

          x *= recip;
          y *= recip;
          z *= recip;

          return *this;
     }

     const LVector operator*(const scalar_t &s) const
     {
          return LVector(x*s, y*s, z*s);
     }

     friend inline const LVector operator*(const scalar_t &s, const LVector &vec)
     {
          return vec*s;
     }

/*   friend inline const LVector operator*(const LVector &vec, const scalar_t &s)
     {
          return LVector(vec.x*s, vec.y*s, vec.z*s);
     }

*/   // dzielenie wektora przez skalar
     const LVector operator/(scalar_t s) const
     {
       s = 1/s;

       return LVector(s*x, s*y, s*z);
     }
     
     const LVector CrossProduct(const LVector &vec) const
     {
       return LVector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
     }

     const LVector operator^(const LVector &vec) const
     {
          return LVector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
     }


     const scalar_t DotProduct(const LVector &vec) const
     {
          return x*vec.x + y*vec.x + z*vec.z;
     }

     
     const scalar_t operator%(const LVector &vec) const
     {
          return x*vec.x + y*vec.x + z*vec.z;
     }


     const scalar_t Length() const
     {
          return (scalar_t)sqrt((double)(x*x + y*y + z*z));
     }

     const LVector UnitVector() const
     {
          return (*this) / Length();
     }

     void normalize()
     {
          (*this) /= Length();
     }

     const scalar_t operator!() const
     {
          return sqrtf(x*x + y*y + z*z);
     }

     const LVector operator | (const scalar_t length) const
     {
          return *this * (length / !(*this));
     }

     const LVector& operator |= (const float length)
     {
          return *this = *this | length;
     }

     const float inline Angle(const LVector& normal) const
     {
          return acosf(*this % normal);
     }

     const LVector inline Reflection(const LVector& normal) const
     {    
          const LVector vec(*this | 1);     // normalizuje wektor
          return (vec - normal * 2.0 * (vec % normal)) * !*this;
     }

     LVector vectorMultiply(LVector vecA, LVector vecB )
     {
       return LVector(vecA.y * vecB.z - vecA.z * vecB.y,
		      vecA.z * vecB.x - vecA.x * vecB.z,
		      vecA.x * vecB.y - vecA.y * vecB.x);
     }

};

#endif
