#ifndef _BASE_COLOR3_HPP_
#define _BASE_COLOR3_HPP_

// ------------------------------------------------------------------------------------------------
#include "Config.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * ...
*/
struct Color3
{
    // --------------------------------------------------------------------------------------------
    typedef Uint8 Value;
    // --------------------------------------------------------------------------------------------
    static const Color3 NIL;
    static const Color3 MIN;
    static const Color3 MAX;
    // --------------------------------------------------------------------------------------------
    static SQChar Delim;
    // --------------------------------------------------------------------------------------------
    Value r, g, b;
    // --------------------------------------------------------------------------------------------
    Color3();
    Color3(Value s);
    Color3(Value r, Value g, Value b);
    // --------------------------------------------------------------------------------------------
    Color3(const Color4 & c);
    // --------------------------------------------------------------------------------------------
    Color3(const SQChar * name);
    Color3(const SQChar * str, SQChar delim);
    // --------------------------------------------------------------------------------------------
    Color3(const Color3 & c);
    Color3(Color3 && c);
    // --------------------------------------------------------------------------------------------
    ~Color3();
    // --------------------------------------------------------------------------------------------
    Color3 & operator = (const Color3 & c);
    Color3 & operator = (Color3 && c);
    // --------------------------------------------------------------------------------------------
    Color3 & operator = (Value s);
    Color3 & operator = (const SQChar * name);
    Color3 & operator = (const Color4 & c);
    // --------------------------------------------------------------------------------------------
    Color3 & operator += (const Color3 & c);
    Color3 & operator -= (const Color3 & c);
    Color3 & operator *= (const Color3 & c);
    Color3 & operator /= (const Color3 & c);
    Color3 & operator %= (const Color3 & c);
    Color3 & operator &= (const Color3 & c);
    Color3 & operator |= (const Color3 & c);
    Color3 & operator ^= (const Color3 & c);
    Color3 & operator <<= (const Color3 & c);
    Color3 & operator >>= (const Color3 & c);
    // --------------------------------------------------------------------------------------------
    Color3 & operator += (Value s);
    Color3 & operator -= (Value s);
    Color3 & operator *= (Value s);
    Color3 & operator /= (Value s);
    Color3 & operator %= (Value s);
    Color3 & operator &= (Value s);
    Color3 & operator |= (Value s);
    Color3 & operator ^= (Value s);
    Color3 & operator <<= (Value s);
    Color3 & operator >>= (Value s);
    // --------------------------------------------------------------------------------------------
    Color3 & operator ++ ();
    Color3 & operator -- ();
    // --------------------------------------------------------------------------------------------
    Color3 operator ++ (int);
    Color3 operator -- (int);
    // --------------------------------------------------------------------------------------------
    Color3 operator + (const Color3 & c) const;
    Color3 operator - (const Color3 & c) const;
    Color3 operator * (const Color3 & c) const;
    Color3 operator / (const Color3 & c) const;
    Color3 operator % (const Color3 & c) const;
    Color3 operator & (const Color3 & c) const;
    Color3 operator | (const Color3 & c) const;
    Color3 operator ^ (const Color3 & c) const;
    Color3 operator << (const Color3 & c) const;
    Color3 operator >> (const Color3 & c) const;
    // --------------------------------------------------------------------------------------------
    Color3 operator + (Value s) const;
    Color3 operator - (Value s) const;
    Color3 operator * (Value s) const;
    Color3 operator / (Value s) const;
    Color3 operator % (Value s) const;
    Color3 operator & (Value s) const;
    Color3 operator | (Value s) const;
    Color3 operator ^ (Value s) const;
    Color3 operator << (Value s) const;
    Color3 operator >> (Value s) const;
    // --------------------------------------------------------------------------------------------
    Color3 operator + () const;
    Color3 operator - () const;
    // --------------------------------------------------------------------------------------------
    Color3 operator ~ () const;
    // --------------------------------------------------------------------------------------------
    bool operator == (const Color3 & c) const;
    bool operator != (const Color3 & c) const;
    bool operator < (const Color3 & c) const;
    bool operator > (const Color3 & c) const;
    bool operator <= (const Color3 & c) const;
    bool operator >= (const Color3 & c) const;
    // --------------------------------------------------------------------------------------------
    SQInteger Cmp(const Color3 & c) const;
    // --------------------------------------------------------------------------------------------
    const SQChar * ToString() const;
    // --------------------------------------------------------------------------------------------
    void Set(Value ns);
    void Set(Value nr, Value ng, Value nb);
    // --------------------------------------------------------------------------------------------
    void Set(const Color3 & c);
    void Set(const Color4 & c);
    // --------------------------------------------------------------------------------------------
    void Set(const SQChar * str, SQChar delim);
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
    void Generate(Value rmin, Value rmax, Value gmin, Value gmax, Value bmin, Value bmax);
    // --------------------------------------------------------------------------------------------
    void Clear() { r = 0, g = 0, b = 0; }
    // --------------------------------------------------------------------------------------------
    void Random();
    // --------------------------------------------------------------------------------------------
    void Inverse();
};

} // Namespace:: SqMod

#endif // _BASE_COLOR3_HPP_
