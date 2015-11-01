#ifndef _BASE_VECTOR2F_HPP_
#define _BASE_VECTOR2F_HPP_

// ------------------------------------------------------------------------------------------------
#include "Config.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * ...
*/
struct Vector2f
{
    // --------------------------------------------------------------------------------------------
    typedef SQFloat Value;
    // --------------------------------------------------------------------------------------------
    static const Vector2f NIL;
    static const Vector2f MIN;
    static const Vector2f MAX;
    // --------------------------------------------------------------------------------------------
    static SQChar Delim;
    // --------------------------------------------------------------------------------------------
    Value x, y;
    // --------------------------------------------------------------------------------------------
    Vector2f();
    Vector2f(Value s);
    Vector2f(Value xv, Value yv);
    // --------------------------------------------------------------------------------------------
    Vector2f(const Vector2i & v);
    Vector2f(const Vector2u & v);
    // --------------------------------------------------------------------------------------------
    Vector2f(const SQChar * values, SQChar delim);
    // --------------------------------------------------------------------------------------------
    Vector2f(const Vector2f & v);
    Vector2f(Vector2f && v);
    // --------------------------------------------------------------------------------------------
    ~Vector2f();
    // --------------------------------------------------------------------------------------------
    Vector2f & operator = (const Vector2f & v);
    Vector2f & operator = (Vector2f && v);
    // --------------------------------------------------------------------------------------------
    Vector2f & operator = (Value s);
    Vector2f & operator = (const SQChar * values);
    Vector2f & operator = (const Vector2i & v);
    Vector2f & operator = (const Vector2u & v);
    // --------------------------------------------------------------------------------------------
    Vector2f & operator += (const Vector2f & v);
    Vector2f & operator -= (const Vector2f & v);
    Vector2f & operator *= (const Vector2f & v);
    Vector2f & operator /= (const Vector2f & v);
    Vector2f & operator %= (const Vector2f & v);
    // --------------------------------------------------------------------------------------------
    Vector2f & operator += (Value s);
    Vector2f & operator -= (Value s);
    Vector2f & operator *= (Value s);
    Vector2f & operator /= (Value s);
    Vector2f & operator %= (Value s);
    // --------------------------------------------------------------------------------------------
    Vector2f & operator ++ ();
    Vector2f & operator -- ();
    // --------------------------------------------------------------------------------------------
    Vector2f operator ++ (int);
    Vector2f operator -- (int);
    // --------------------------------------------------------------------------------------------
    Vector2f operator + (const Vector2f & v) const;
    Vector2f operator - (const Vector2f & v) const;
    Vector2f operator * (const Vector2f & v) const;
    Vector2f operator / (const Vector2f & v) const;
    Vector2f operator % (const Vector2f & v) const;
    // --------------------------------------------------------------------------------------------
    Vector2f operator + (Value s) const;
    Vector2f operator - (Value s) const;
    Vector2f operator * (Value s) const;
    Vector2f operator / (Value s) const;
    Vector2f operator % (Value s) const;
    // --------------------------------------------------------------------------------------------
    Vector2f operator + () const;
    Vector2f operator - () const;
    // --------------------------------------------------------------------------------------------
    bool operator == (const Vector2f & v) const;
    bool operator != (const Vector2f & v) const;
    bool operator < (const Vector2f & v) const;
    bool operator > (const Vector2f & v) const;
    bool operator <= (const Vector2f & v) const;
    bool operator >= (const Vector2f & v) const;
    // --------------------------------------------------------------------------------------------
    SQInteger Cmp(const Vector2f & v) const;
    // --------------------------------------------------------------------------------------------
    const SQChar * ToString() const;
    // --------------------------------------------------------------------------------------------
    void Set(Value ns);
    void Set(Value nx, Value ny);
    // --------------------------------------------------------------------------------------------
    void Set(const Vector2f & v);
    void Set(const Vector2i & v);
    void Set(const Vector2u & v);
    // --------------------------------------------------------------------------------------------
    void Set(const SQChar * values, SQChar delim);
    // --------------------------------------------------------------------------------------------
    void Generate();
    void Generate(Value min, Value max);
    void Generate(Value xmin, Value xmax, Value ymin, Value ymax);
    // --------------------------------------------------------------------------------------------
    void Clear() { x = 0.0, y = 0.0; }
    // --------------------------------------------------------------------------------------------
    Vector2f Abs() const;
};

} // Namespace:: SqMod

#endif // _BASE_VECTOR2F_HPP_
