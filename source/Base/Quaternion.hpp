#ifndef _BASE_QUATERNION_HPP_
#define _BASE_QUATERNION_HPP_

// ------------------------------------------------------------------------------------------------
#include "Config.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * ...
*/
struct Quaternion
{
    // --------------------------------------------------------------------------------------------
    typedef SQFloat Value;
    // --------------------------------------------------------------------------------------------
    static const Quaternion NIL;
    static const Quaternion MIN;
    static const Quaternion MAX;
    // --------------------------------------------------------------------------------------------
    static SQChar Delim;
    // --------------------------------------------------------------------------------------------
    Value x, y, z, w;
    // --------------------------------------------------------------------------------------------
    Quaternion();
    Quaternion(Value s);
    Quaternion(Value xv, Value yv, Value zv);
    Quaternion(Value xv, Value yv, Value zv, Value wv);
    // --------------------------------------------------------------------------------------------
    Quaternion(const Vector3 & v);
    Quaternion(const Vector4 & v);
    // --------------------------------------------------------------------------------------------
    Quaternion(const SQChar * values, SQChar delim);
    // --------------------------------------------------------------------------------------------
    Quaternion(const Quaternion & q);
    Quaternion(Quaternion && q);
    // --------------------------------------------------------------------------------------------
    ~Quaternion();
    // --------------------------------------------------------------------------------------------
    Quaternion & operator = (const Quaternion & q);
    Quaternion & operator = (Quaternion && q);
    // --------------------------------------------------------------------------------------------
    Quaternion & operator = (Value s);
    Quaternion & operator = (const Vector3 & q);
    Quaternion & operator = (const Vector4 & q);
    // --------------------------------------------------------------------------------------------
    Quaternion & operator += (const Quaternion & q);
    Quaternion & operator -= (const Quaternion & q);
    Quaternion & operator *= (const Quaternion & q);
    Quaternion & operator /= (const Quaternion & q);
    Quaternion & operator %= (const Quaternion & q);
    // --------------------------------------------------------------------------------------------
    Quaternion & operator += (Value s);
    Quaternion & operator -= (Value s);
    Quaternion & operator *= (Value s);
    Quaternion & operator /= (Value s);
    Quaternion & operator %= (Value s);
    // --------------------------------------------------------------------------------------------
    Quaternion & operator ++ ();
    Quaternion & operator -- ();
    // --------------------------------------------------------------------------------------------
    Quaternion operator ++ (int);
    Quaternion operator -- (int);
    // --------------------------------------------------------------------------------------------
    Quaternion operator + (const Quaternion & q) const;
    Quaternion operator - (const Quaternion & q) const;
    Quaternion operator * (const Quaternion & q) const;
    Quaternion operator / (const Quaternion & q) const;
    Quaternion operator % (const Quaternion & q) const;
    // --------------------------------------------------------------------------------------------
    Quaternion operator + (Value s) const;
    Quaternion operator - (Value s) const;
    Quaternion operator * (Value s) const;
    Quaternion operator / (Value s) const;
    Quaternion operator % (Value s) const;
    // --------------------------------------------------------------------------------------------
    Quaternion operator + () const;
    Quaternion operator - () const;
    // --------------------------------------------------------------------------------------------
    bool operator == (const Quaternion & q) const;
    bool operator != (const Quaternion & q) const;
    bool operator < (const Quaternion & q) const;
    bool operator > (const Quaternion & q) const;
    bool operator <= (const Quaternion & q) const;
    bool operator >= (const Quaternion & q) const;
    // --------------------------------------------------------------------------------------------
    SQInteger Cmp(const Quaternion & q) const;
    // --------------------------------------------------------------------------------------------
    const SQChar * ToString() const;
    // --------------------------------------------------------------------------------------------
    void Set(Value ns);
    void Set(Value nx, Value ny, Value nz);
    void Set(Value nx, Value ny, Value nz, Value nw);
    // --------------------------------------------------------------------------------------------
    void Set(const Quaternion & q);
    void Set(const Vector3 & v);
    void Set(const Vector4 & v);
    // --------------------------------------------------------------------------------------------
    void Set(const SQChar * values, SQChar delim);
    // --------------------------------------------------------------------------------------------
    void Generate();
    void Generate(Value min, Value max);
    void Generate(Value xmin, Value xmax, Value ymin, Value ymax, Value zmin, Value zmax, Value wmin, Value wmax);
    // --------------------------------------------------------------------------------------------
    void Clear() { x = 0.0, y = 0.0, z = 0.0, w = 0.0; }
    // --------------------------------------------------------------------------------------------
    Quaternion Abs() const;
};

} // Namespace:: SqMod

#endif // _BASE_QUATERNION_HPP_
