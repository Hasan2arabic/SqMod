#ifndef _BASE_CIRCLE_HPP_
#define _BASE_CIRCLE_HPP_

// ------------------------------------------------------------------------------------------------
#include "Config.hpp"
#include "Base/Vector2f.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * ...
*/
struct Circle
{
    // --------------------------------------------------------------------------------------------
    typedef SQFloat Value;
    // --------------------------------------------------------------------------------------------
    static const Circle NIL;
    static const Circle MIN;
    static const Circle MAX;
    // --------------------------------------------------------------------------------------------
    static SQChar Delim;
    // --------------------------------------------------------------------------------------------
    Vector2f    pos;
    Value       rad;
    // --------------------------------------------------------------------------------------------
    Circle();
    Circle(Value r);
    Circle(const Vector2f & p);
    Circle(const Vector2f & p, Value r);
    Circle(Value x, Value y, Value r);
    // --------------------------------------------------------------------------------------------
    Circle(const Circle & c);
    Circle(Circle && c);
    // --------------------------------------------------------------------------------------------
    ~Circle();
    // --------------------------------------------------------------------------------------------
    Circle & operator = (const Circle & c);
    Circle & operator = (Circle && c);
    // --------------------------------------------------------------------------------------------
    Circle & operator = (Value r);
    Circle & operator = (const Vector2f & p);
    // --------------------------------------------------------------------------------------------
    Circle & operator += (const Circle & c);
    Circle & operator -= (const Circle & c);
    Circle & operator *= (const Circle & c);
    Circle & operator /= (const Circle & c);
    Circle & operator %= (const Circle & c);
    // --------------------------------------------------------------------------------------------
    Circle & operator += (Value r);
    Circle & operator -= (Value r);
    Circle & operator *= (Value r);
    Circle & operator /= (Value r);
    Circle & operator %= (Value r);
    // --------------------------------------------------------------------------------------------
    Circle & operator += (const Vector2f & p);
    Circle & operator -= (const Vector2f & p);
    Circle & operator *= (const Vector2f & p);
    Circle & operator /= (const Vector2f & p);
    Circle & operator %= (const Vector2f & p);
    // --------------------------------------------------------------------------------------------
    Circle & operator ++ ();
    Circle & operator -- ();
    // --------------------------------------------------------------------------------------------
    Circle operator ++ (int);
    Circle operator -- (int);
    // --------------------------------------------------------------------------------------------
    Circle operator + (const Circle & c) const;
    Circle operator - (const Circle & c) const;
    Circle operator * (const Circle & c) const;
    Circle operator / (const Circle & c) const;
    Circle operator % (const Circle & c) const;
    // --------------------------------------------------------------------------------------------
    Circle operator + (Value r) const;
    Circle operator - (Value r) const;
    Circle operator * (Value r) const;
    Circle operator / (Value r) const;
    Circle operator % (Value r) const;
    // --------------------------------------------------------------------------------------------
    Circle operator + (const Vector2f & p) const;
    Circle operator - (const Vector2f & p) const;
    Circle operator * (const Vector2f & p) const;
    Circle operator / (const Vector2f & p) const;
    Circle operator % (const Vector2f & p) const;
    // --------------------------------------------------------------------------------------------
    Circle operator + () const;
    Circle operator - () const;
    // --------------------------------------------------------------------------------------------
    bool operator == (const Circle & c) const;
    bool operator != (const Circle & c) const;
    bool operator < (const Circle & c) const;
    bool operator > (const Circle & c) const;
    bool operator <= (const Circle & c) const;
    bool operator >= (const Circle & c) const;
    // --------------------------------------------------------------------------------------------
    SQInteger Cmp(const Circle & c) const;
    // --------------------------------------------------------------------------------------------
    const SQChar * ToString() const;
    // --------------------------------------------------------------------------------------------
    void Set(Value nr);
    void Set(const Circle & nc);
    void Set(const Vector2f & np);
    void Set(const Vector2f & np, Value nr);
    // --------------------------------------------------------------------------------------------
    void Set(Value nx, Value ny);
    void Set(Value nx, Value ny, Value nr);
    // --------------------------------------------------------------------------------------------
    void Set(const SQChar * values, SQChar delim);
    // --------------------------------------------------------------------------------------------
    void Generate();
    void Generate(Value min, Value max, bool r);
    void Generate(Value xmin, Value xmax, Value ymin, Value ymax);
    void Generate(Value xmin, Value xmax, Value ymin, Value ymax, Value rmin, Value rmax);
    // --------------------------------------------------------------------------------------------
    void Clear() { pos.Clear(); rad = 0.0; }
    // --------------------------------------------------------------------------------------------
    Circle Abs() const;
};

} // Namespace:: SqMod

#endif // _BASE_CIRCLE_HPP_
