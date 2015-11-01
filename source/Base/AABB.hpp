#ifndef _BASE_AABB_HPP_
#define _BASE_AABB_HPP_

// ------------------------------------------------------------------------------------------------
#include "Config.hpp"
#include "Base/Vector3.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * ...
*/
struct AABB
{
    // --------------------------------------------------------------------------------------------
    typedef SQFloat Value;
    // --------------------------------------------------------------------------------------------
    static const AABB NIL;
    static const AABB MIN;
    static const AABB MAX;
    // --------------------------------------------------------------------------------------------
    static SQChar Delim;
    // --------------------------------------------------------------------------------------------
    Vector3 min, max;
    // --------------------------------------------------------------------------------------------
    AABB();
    AABB(Value s);
    AABB(Value x, Value y, Value z);
    AABB(Value xmin, Value ymin, Value zmin, Value xmax, Value ymax, Value zmax);
    // --------------------------------------------------------------------------------------------
    AABB(const Vector3 & b);
    AABB(const Vector3 & vmin, const Vector3 & vmax);
    // --------------------------------------------------------------------------------------------
    AABB(const Vector4 & b);
    AABB(const Vector4 & vmin, const Vector4 & vmax);
    // --------------------------------------------------------------------------------------------
    AABB(const SQChar * values, SQChar delim);
    // --------------------------------------------------------------------------------------------
    AABB(const AABB & b);
    AABB(AABB && b);
    // --------------------------------------------------------------------------------------------
    ~AABB();
    // --------------------------------------------------------------------------------------------
    AABB & operator = (const AABB & b);
    AABB & operator = (AABB && b);
    // --------------------------------------------------------------------------------------------
    AABB & operator = (Value s);
    AABB & operator = (const Vector3 & v);
    AABB & operator = (const Vector4 & v);
    // --------------------------------------------------------------------------------------------
    AABB & operator += (const AABB & b);
    AABB & operator -= (const AABB & b);
    AABB & operator *= (const AABB & b);
    AABB & operator /= (const AABB & b);
    AABB & operator %= (const AABB & b);
    // --------------------------------------------------------------------------------------------
    AABB & operator += (Value s);
    AABB & operator -= (Value s);
    AABB & operator *= (Value s);
    AABB & operator /= (Value s);
    AABB & operator %= (Value s);
    // --------------------------------------------------------------------------------------------
    AABB & operator ++ ();
    AABB & operator -- ();
    // --------------------------------------------------------------------------------------------
    AABB operator ++ (int);
    AABB operator -- (int);
    // --------------------------------------------------------------------------------------------
    AABB operator + (const AABB & b) const;
    AABB operator - (const AABB & b) const;
    AABB operator * (const AABB & b) const;
    AABB operator / (const AABB & b) const;
    AABB operator % (const AABB & b) const;
    // --------------------------------------------------------------------------------------------
    AABB operator + (Value s) const;
    AABB operator - (Value s) const;
    AABB operator * (Value s) const;
    AABB operator / (Value s) const;
    AABB operator % (Value s) const;
    // --------------------------------------------------------------------------------------------
    AABB operator + () const;
    AABB operator - () const;
    // --------------------------------------------------------------------------------------------
    bool operator == (const AABB & b) const;
    bool operator != (const AABB & b) const;
    bool operator < (const AABB & b) const;
    bool operator > (const AABB & b) const;
    bool operator <= (const AABB & b) const;
    bool operator >= (const AABB & b) const;
    // --------------------------------------------------------------------------------------------
    SQInteger Cmp(const AABB & b) const;
    // --------------------------------------------------------------------------------------------
    const SQChar * ToString() const;
    // --------------------------------------------------------------------------------------------
    void Set(Value ns);
    void Set(Value nx, Value ny, Value nz);
    void Set(Value xmin, Value ymin, Value zmin, Value xmax, Value ymax, Value zmax);
    // --------------------------------------------------------------------------------------------
    void Set(const AABB & b);
    // --------------------------------------------------------------------------------------------
    void Set(const Vector3 & v);
    void Set(const Vector3 & nmin, const Vector3 & nmax);
    // --------------------------------------------------------------------------------------------
    void Set(const Vector4 & v);
    void Set(const Vector4 & nmin, const Vector4 & nmax);
    // --------------------------------------------------------------------------------------------
    void Set(const SQChar * values, SQChar delim);
    // --------------------------------------------------------------------------------------------
    void Clear() { min.Clear(); max.Clear(); }
    // --------------------------------------------------------------------------------------------
    AABB Abs() const;
};

} // Namespace:: SqMod

#endif // _BASE_AABB_HPP_
