#ifndef _BASE_COLOR4_HPP_
#define _BASE_COLOR4_HPP_

// ------------------------------------------------------------------------------------------------
#include "Config.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * ...
*/
struct Color4
{
    // --------------------------------------------------------------------------------------------
    typedef Uint8 Value;
    // --------------------------------------------------------------------------------------------
    static const Color4 NIL;
    static const Color4 MIN;
    static const Color4 MAX;
    // --------------------------------------------------------------------------------------------
    static SQChar Delim;
    // --------------------------------------------------------------------------------------------
    Value r, g, b, a;
    // --------------------------------------------------------------------------------------------
    Color4();
    Color4(Value s);
    Color4(Value r, Value g, Value b);
    Color4(Value r, Value g, Value b, Value a);
    // --------------------------------------------------------------------------------------------
    Color4(const Color3 & c);
    // --------------------------------------------------------------------------------------------
    Color4(const SQChar * name);
    Color4(const SQChar * str, SQChar delim);
    // --------------------------------------------------------------------------------------------
    Color4(const Color4 & c);
    Color4(Color4 && c);
    // --------------------------------------------------------------------------------------------
    ~Color4();
    // --------------------------------------------------------------------------------------------
    Color4 & operator = (const Color4 & c);
    Color4 & operator = (Color4 && c);
    // --------------------------------------------------------------------------------------------
    Color4 & operator = (Value s);
    Color4 & operator = (const SQChar * name);
    Color4 & operator = (const Color3 & c);
    // --------------------------------------------------------------------------------------------
    Color4 & operator += (const Color4 & c);
    Color4 & operator -= (const Color4 & c);
    Color4 & operator *= (const Color4 & c);
    Color4 & operator /= (const Color4 & c);
    Color4 & operator %= (const Color4 & c);
    Color4 & operator &= (const Color4 & c);
    Color4 & operator |= (const Color4 & c);
    Color4 & operator ^= (const Color4 & c);
    Color4 & operator <<= (const Color4 & c);
    Color4 & operator >>= (const Color4 & c);
    // --------------------------------------------------------------------------------------------
    Color4 & operator += (Value s);
    Color4 & operator -= (Value s);
    Color4 & operator *= (Value s);
    Color4 & operator /= (Value s);
    Color4 & operator %= (Value s);
    Color4 & operator &= (Value s);
    Color4 & operator |= (Value s);
    Color4 & operator ^= (Value s);
    Color4 & operator <<= (Value s);
    Color4 & operator >>= (Value s);
    // --------------------------------------------------------------------------------------------
    Color4 & operator ++ ();
    Color4 & operator -- ();
    // --------------------------------------------------------------------------------------------
    Color4 operator ++ (int);
    Color4 operator -- (int);
    // --------------------------------------------------------------------------------------------
    Color4 operator + (const Color4 & c) const;
    Color4 operator - (const Color4 & c) const;
    Color4 operator * (const Color4 & c) const;
    Color4 operator / (const Color4 & c) const;
    Color4 operator % (const Color4 & c) const;
    Color4 operator & (const Color4 & c) const;
    Color4 operator | (const Color4 & c) const;
    Color4 operator ^ (const Color4 & c) const;
    Color4 operator << (const Color4 & c) const;
    Color4 operator >> (const Color4 & c) const;
    // --------------------------------------------------------------------------------------------
    Color4 operator + (Value s) const;
    Color4 operator - (Value s) const;
    Color4 operator * (Value s) const;
    Color4 operator / (Value s) const;
    Color4 operator % (Value s) const;
    Color4 operator & (Value s) const;
    Color4 operator | (Value s) const;
    Color4 operator ^ (Value s) const;
    Color4 operator << (Value s) const;
    Color4 operator >> (Value s) const;
    // --------------------------------------------------------------------------------------------
    Color4 operator + () const;
    Color4 operator - () const;
    // --------------------------------------------------------------------------------------------
    Color4 operator ~ () const;
    // --------------------------------------------------------------------------------------------
    bool operator == (const Color4 & c) const;
    bool operator != (const Color4 & c) const;
    bool operator < (const Color4 & c) const;
    bool operator > (const Color4 & c) const;
    bool operator <= (const Color4 & c) const;
    bool operator >= (const Color4 & c) const;
    // --------------------------------------------------------------------------------------------
    SQInteger Cmp(const Color4 & c) const;
    // --------------------------------------------------------------------------------------------
    const SQChar * ToString() const;
    // --------------------------------------------------------------------------------------------
    void Set(Value ns);
    void Set(Value nr, Value ng, Value nb);
    void Set(Value nr, Value ng, Value nb, Value na);
    // --------------------------------------------------------------------------------------------
    void Set(const Color4 & c);
    void Set(const Color3 & c);
    // --------------------------------------------------------------------------------------------
    void Set(const SQChar * name, SQChar delim);
    // --------------------------------------------------------------------------------------------
    void SetCol(const SQChar * name);
    // --------------------------------------------------------------------------------------------
    SQUint32 GetRGB() const;
    void SetRGB(SQUint32 p);
    // --------------------------------------------------------------------------------------------
    SQUint32 GetRGBA() const;
    void SetRGBA(SQUint32 p);
    // --------------------------------------------------------------------------------------------
    SQUint32 GetARGB() const;
    void SetARGB(SQUint32 p);
    // --------------------------------------------------------------------------------------------
    void Generate();
    void Generate(Value min, Value max);
    void Generate(Value rmin, Value rmax, Value gmin, Value gmax, Value bmin, Value bmax, Value amin, Value amax);
    // --------------------------------------------------------------------------------------------
    void Clear() { r = 0, g = 0, b = 0, a = 0; }
    // --------------------------------------------------------------------------------------------
    void Random();
    // --------------------------------------------------------------------------------------------
    void Inverse();
};

} // Namespace:: SqMod

#endif // _BASE_COLOR4_HPP_
