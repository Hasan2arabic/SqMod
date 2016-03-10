// ------------------------------------------------------------------------------------------------
#include "Base/Color4.hpp"
#include "Base/Color3.hpp"
#include "Base/Shared.hpp"
#include "Library/Random.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
const Color4 Color4::NIL = Color4();
const Color4 Color4::MIN = Color4(NumLimit< Color4::Value >::Min);
const Color4 Color4::MAX = Color4(NumLimit< Color4::Value >::Max);

// ------------------------------------------------------------------------------------------------
SQChar Color4::Delim = ',';

// ------------------------------------------------------------------------------------------------
SQInteger Color4::Typename(HSQUIRRELVM vm)
{
    static SQChar name[] = _SC("Color4");
    sq_pushstring(vm, name, sizeof(name));
    return 1;
}

// ------------------------------------------------------------------------------------------------
Color4::Color4()
    : r(0), g(0), b(0), a(0)
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
Color4::Color4(Value sv)
    : r(sv), g(sv), b(sv), a(0)
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
Color4::Color4(Value rv, Value gv, Value bv)
    : r(rv), g(gv), b(bv), a(0)
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
Color4::Color4(Value rv, Value gv, Value bv, Value av)
    : r(rv), g(gv), b(bv), a(av)
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
Color4 & Color4::operator = (Value s)
{
    r = s;
    g = s;
    b = s;
    a = s;
    return *this;
}

Color4 & Color4::operator = (CSStr name)
{
    Set(GetColor(name));
    return *this;
}

Color4 & Color4::operator = (const Color3 & c)
{
    r = c.r;
    g = c.g;
    b = c.b;
    return *this;
}

// ------------------------------------------------------------------------------------------------
Color4 & Color4::operator += (const Color4 & c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;
    return *this;
}

Color4 & Color4::operator -= (const Color4 & c)
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    a -= c.a;
    return *this;
}

Color4 & Color4::operator *= (const Color4 & c)
{
    r *= c.r;
    g *= c.g;
    b *= c.b;
    a *= c.a;
    return *this;
}

Color4 & Color4::operator /= (const Color4 & c)
{
    r /= c.r;
    g /= c.g;
    b /= c.b;
    a /= c.a;
    return *this;
}

Color4 & Color4::operator %= (const Color4 & c)
{
    r %= c.r;
    g %= c.g;
    b %= c.b;
    a %= c.a;
    return *this;
}

Color4 & Color4::operator &= (const Color4 & c)
{
    r &= c.r;
    g &= c.g;
    b &= c.b;
    a &= c.a;
    return *this;
}

Color4 & Color4::operator |= (const Color4 & c)
{
    r |= c.r;
    g |= c.g;
    b |= c.b;
    a |= c.a;
    return *this;
}

Color4 & Color4::operator ^= (const Color4 & c)
{
    r ^= c.r;
    g ^= c.g;
    b ^= c.b;
    a ^= c.a;
    return *this;
}

Color4 & Color4::operator <<= (const Color4 & c)
{
    r <<= c.r;
    g <<= c.g;
    b <<= c.b;
    a <<= c.a;
    return *this;
}

Color4 & Color4::operator >>= (const Color4 & c)
{
    r >>= c.r;
    g >>= c.g;
    b >>= c.b;
    a >>= c.a;
    return *this;
}

// ------------------------------------------------------------------------------------------------
Color4 & Color4::operator += (Value s)
{
    r += s;
    g += s;
    b += s;
    a += s;
    return *this;
}

Color4 & Color4::operator -= (Value s)
{
    r -= s;
    g -= s;
    b -= s;
    a -= s;
    return *this;
}

Color4 & Color4::operator *= (Value s)
{
    r *= s;
    g *= s;
    b *= s;
    a *= s;
    return *this;
}

Color4 & Color4::operator /= (Value s)
{
    r /= s;
    g /= s;
    b /= s;
    a /= s;
    return *this;
}

Color4 & Color4::operator %= (Value s)
{
    r %= s;
    g %= s;
    b %= s;
    a %= s;
    return *this;
}

Color4 & Color4::operator &= (Value s)
{
    r &= s;
    g &= s;
    b &= s;
    a &= s;
    return *this;
}

Color4 & Color4::operator |= (Value s)
{
    r |= s;
    g |= s;
    b |= s;
    a |= s;
    return *this;
}

Color4 & Color4::operator ^= (Value s)
{
    r ^= s;
    g ^= s;
    b ^= s;
    a ^= s;
    return *this;
}

Color4 & Color4::operator <<= (Value s)
{
    r <<= s;
    g <<= s;
    b <<= s;
    a <<= s;
    return *this;
}

Color4 & Color4::operator >>= (Value s)
{
    r >>= s;
    g >>= s;
    b >>= s;
    a >>= s;
    return *this;
}

// ------------------------------------------------------------------------------------------------
Color4 & Color4::operator ++ ()
{
    ++r;
    ++g;
    ++b;
    ++a;
    return *this;
}

Color4 & Color4::operator -- ()
{
    --r;
    --g;
    --b;
    --a;
    return *this;
}

// ------------------------------------------------------------------------------------------------
Color4 Color4::operator ++ (int)
{
    Color4 state(*this);
    ++r;
    ++g;
    ++b;
    ++a;
    return state;
}

Color4 Color4::operator -- (int)
{
    Color4 state(*this);
    --r;
    --g;
    --b;
    --a;
    return state;
}

// ------------------------------------------------------------------------------------------------
Color4 Color4::operator + (const Color4 & c) const
{
    return Color4(r + c.r, g + c.g, b + c.b, a + c.a);
}

Color4 Color4::operator - (const Color4 & c) const
{
    return Color4(r - c.r, g - c.g, b - c.b, a - c.a);
}

Color4 Color4::operator * (const Color4 & c) const
{
    return Color4(r * c.r, g * c.g, b * c.b, a * c.a);
}

Color4 Color4::operator / (const Color4 & c) const
{
    return Color4(r / c.r, g / c.g, b / c.b, a / c.a);
}

Color4 Color4::operator % (const Color4 & c) const
{
    return Color4(r % c.r, g % c.g, b % c.b, a % c.a);
}

Color4 Color4::operator & (const Color4 & c) const
{
    return Color4(r & c.r, g & c.g, b & c.b, a & c.a);
}

Color4 Color4::operator | (const Color4 & c) const
{
    return Color4(r | c.r, g | c.g, b | c.b, a | c.a);
}

Color4 Color4::operator ^ (const Color4 & c) const
{
    return Color4(r ^ c.r, g ^ c.g, b ^ c.b, a ^ c.a);
}

Color4 Color4::operator << (const Color4 & c) const
{
    return Color4(r << c.r, g << c.g, b << c.b, a << c.a);
}

Color4 Color4::operator >> (const Color4 & c) const
{
    return Color4(r >> c.r, g >> c.g, b >> c.b, a >> c.a);
}

// ------------------------------------------------------------------------------------------------
Color4 Color4::operator + (Value s) const
{
    return Color4(r + s, g + s, b + s, a + s);
}

Color4 Color4::operator - (Value s) const
{
    return Color4(r - s, g - s, b - s, a - s);
}

Color4 Color4::operator * (Value s) const
{
    return Color4(r * s, g * s, b * s, a * s);
}

Color4 Color4::operator / (Value s) const
{
    return Color4(r / s, g / s, b / s, a / s);
}

Color4 Color4::operator % (Value s) const
{
    return Color4(r % s, g % s, b % s, a % s);
}

Color4 Color4::operator & (Value s) const
{
    return Color4(r & s, g & s, b & s, a & s);
}

Color4 Color4::operator | (Value s) const
{
    return Color4(r | s, g | s, b | s, a | s);
}

Color4 Color4::operator ^ (Value s) const
{
    return Color4(r ^ s, g ^ s, b ^ s, a ^ s);
}

Color4 Color4::operator << (Value s) const
{
    return Color4(r << s, g << s, b << s, a << s);
}

Color4 Color4::operator >> (Value s) const
{
    return Color4(r >> s, g >> s, b >> s, a >> s);
}

// ------------------------------------------------------------------------------------------------
Color4 Color4::operator + () const
{
    return Color4(r, g, b, a);
}

Color4 Color4::operator - () const
{
    return Color4(0, 0, 0, 0);
}

// ------------------------------------------------------------------------------------------------
Color4 Color4::operator ~ () const
{
    return Color4(~r, ~g, ~b, ~a);
}

// ------------------------------------------------------------------------------------------------
bool Color4::operator == (const Color4 & c) const
{
    return (r == c.r) && (g == c.g) && (b == c.b) && (a == c.a);
}

bool Color4::operator != (const Color4 & c) const
{
    return (r != c.r) && (g != c.g) && (b != c.b) && (a != c.a);
}

bool Color4::operator < (const Color4 & c) const
{
    return (r < c.r) && (g < c.g) && (b < c.b) && (a < c.a);
}

bool Color4::operator > (const Color4 & c) const
{
    return (r > c.r) && (g > c.g) && (b > c.b) && (a > c.a);
}

bool Color4::operator <= (const Color4 & c) const
{
    return (r <= c.r) && (g <= c.g) && (b <= c.b) && (a <= c.a);
}

bool Color4::operator >= (const Color4 & c) const
{
    return (r >= c.r) && (g >= c.g) && (b >= c.b) && (a >= c.a);
}

// ------------------------------------------------------------------------------------------------
Color4::operator Color3 () const
{
    return Color3(r, g, b);
}

// ------------------------------------------------------------------------------------------------
Int32 Color4::Cmp(const Color4 & o) const
{
    if (*this == o)
        return 0;
    else if (*this > o)
        return 1;
    else
        return -1;
}

// ------------------------------------------------------------------------------------------------
CSStr Color4::ToString() const
{
    return ToStrF("%u,%u,%u,%u", r, g, b, a);
}

// ------------------------------------------------------------------------------------------------
void Color4::Set(Value ns)
{
    r = ns;
    g = ns;
    b = ns;
    a = ns;
}

void Color4::Set(Value nr, Value ng, Value nb)
{
    r = nr;
    g = ng;
    b = nb;
}

void Color4::Set(Value nr, Value ng, Value nb, Value na)
{
    r = nr;
    g = ng;
    b = nb;
    a = na;
}

// ------------------------------------------------------------------------------------------------
void Color4::Set(const Color4 & c)
{
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}

void Color4::Set(const Color3 & c)
{
    r = c.r;
    g = c.g;
    b = c.b;
    a = 0;
}

// ------------------------------------------------------------------------------------------------
void Color4::Set(CSStr str, SQChar delim)
{
    Set(GetColor4(str, delim));
}

// ------------------------------------------------------------------------------------------------
void Color4::SetCol(CSStr name)
{
    Set(GetColor(name));
}

// ------------------------------------------------------------------------------------------------
Uint32 Color4::GetRGB() const
{
    return Uint32(r << 16 | g << 8 | b);
}

void Color4::SetRGB(Uint32 p)
{
    r = static_cast< Value >((p >> 16) & 0xFF);
    g = static_cast< Value >((p >> 8) & 0xFF);
    b = static_cast< Value >((p) & 0xFF);
}

// ------------------------------------------------------------------------------------------------
Uint32 Color4::GetRGBA() const
{
    return Uint32(r << 24 | g << 16 | b << 8 | a);
}

void Color4::SetRGBA(Uint32 p)
{
    r = static_cast< Value >((p >> 24) & 0xFF);
    g = static_cast< Value >((p >> 16) & 0xFF);
    b = static_cast< Value >((p >> 8) & 0xFF);
    a = static_cast< Value >((p) & 0xFF);
}

// ------------------------------------------------------------------------------------------------
Uint32 Color4::GetARGB() const
{
    return Uint32(a << 24 | r << 16 | g << 8 | b);
}

void Color4::SetARGB(Uint32 p)
{
    a = static_cast< Value >((p >> 24) & 0xFF);
    r = static_cast< Value >((p >> 16) & 0xFF);
    g = static_cast< Value >((p >> 8) & 0xFF);
    b = static_cast< Value >((p) & 0xFF);
}

// ------------------------------------------------------------------------------------------------
void Color4::Generate()
{
    r = GetRandomUint8();
    g = GetRandomUint8();
    b = GetRandomUint8();
    a = GetRandomUint8();
}

void Color4::Generate(Value min, Value max)
{
    if (max < min)
        SqThrowF("max value is lower than min value");

    r = GetRandomUint8(min, max);
    g = GetRandomUint8(min, max);
    b = GetRandomUint8(min, max);
    a = GetRandomUint8(min, max);
}

void Color4::Generate(Value rmin, Value rmax, Value gmin, Value gmax, Value bmin, Value bmax, Value amin, Value amax)
{
    if (rmax < rmin || gmax < gmin || bmax < bmin || amax < amin)
        SqThrowF("max value is lower than min value");

    r = GetRandomUint8(rmin, rmax);
    g = GetRandomUint8(gmin, gmax);
    b = GetRandomUint8(bmin, bmax);
    a = GetRandomUint8(bmin, bmax);
}

// ------------------------------------------------------------------------------------------------
void Color4::Random()
{
    Set(GetRandomColor());
}

// ------------------------------------------------------------------------------------------------
void Color4::Inverse()
{
    r = static_cast< Value >(~r);
    g = static_cast< Value >(~g);
    b = static_cast< Value >(~b);
    a = static_cast< Value >(~a);
}

// ================================================================================================
void Register_Color4(HSQUIRRELVM vm)
{
    typedef Color4::Value Val;

    RootTable(vm).Bind(_SC("Color4"), Class< Color4 >(vm, _SC("Color4"))
        /* Constructors */
        .Ctor()
        .Ctor< Val >()
        .Ctor< Val, Val, Val >()
        .Ctor< Val, Val, Val, Val >()
        /* Static Members */
        .SetStaticValue(_SC("Delim"), &Color4::Delim)
        /* Member Variables */
        .Var(_SC("r"), &Color4::r)
        .Var(_SC("g"), &Color4::g)
        .Var(_SC("b"), &Color4::b)
        .Var(_SC("a"), &Color4::a)
        /* Properties */
        .Prop(_SC("rgb"), &Color4::GetRGB, &Color4::SetRGB)
        .Prop(_SC("rgba"), &Color4::GetRGBA, &Color4::SetRGBA)
        .Prop(_SC("argb"), &Color4::GetARGB, &Color4::SetARGB)
        .Prop(_SC("str"), &Color4::SetCol)
        /* Core Metamethods */
        .Func(_SC("_tostring"), &Color4::ToString)
        .SquirrelFunc(_SC("_typename"), &Color4::Typename)
        .Func(_SC("_cmp"), &Color4::Cmp)
        /* Metamethods */
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("_add"), &Color4::operator +)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("_sub"), &Color4::operator -)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("_mul"), &Color4::operator *)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("_div"), &Color4::operator /)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("_modulo"), &Color4::operator %)
        .Func<Color4 (Color4::*)(void) const>(_SC("_unm"), &Color4::operator -)
        /* Setters */
        .Overload<void (Color4::*)(Val)>(_SC("Set"), &Color4::Set)
        .Overload<void (Color4::*)(Val, Val, Val)>(_SC("Set"), &Color4::Set)
        .Overload<void (Color4::*)(Val, Val, Val, Val)>(_SC("Set"), &Color4::Set)
        .Overload<void (Color4::*)(const Color4 &)>(_SC("SetCol4"), &Color4::Set)
        .Overload<void (Color4::*)(const Color3 &)>(_SC("SetCol3"), &Color4::Set)
        .Overload<void (Color4::*)(CSStr, SQChar)>(_SC("SetStr"), &Color4::Set)
        /* Random Generators */
        .Overload<void (Color4::*)(void)>(_SC("Generate"), &Color4::Generate)
        .Overload<void (Color4::*)(Val, Val)>(_SC("Generate"), &Color4::Generate)
        .Overload<void (Color4::*)(Val, Val, Val, Val, Val, Val, Val, Val)>(_SC("Generate"), &Color4::Generate)
        /* Utility Methods */
        .Func(_SC("Clear"), &Color4::Clear)
        .Func(_SC("Random"), &Color4::Random)
        .Func(_SC("Inverse"), &Color4::Inverse)
        /* Operator Exposure */
        .Func<Color4 & (Color4::*)(const Color4 &)>(_SC("opAddAssign"), &Color4::operator +=)
        .Func<Color4 & (Color4::*)(const Color4 &)>(_SC("opSubAssign"), &Color4::operator -=)
        .Func<Color4 & (Color4::*)(const Color4 &)>(_SC("opMulAssign"), &Color4::operator *=)
        .Func<Color4 & (Color4::*)(const Color4 &)>(_SC("opDivAssign"), &Color4::operator /=)
        .Func<Color4 & (Color4::*)(const Color4 &)>(_SC("opModAssign"), &Color4::operator %=)
        .Func<Color4 & (Color4::*)(const Color4 &)>(_SC("opAndAssign"), &Color4::operator &=)
        .Func<Color4 & (Color4::*)(const Color4 &)>(_SC("opOrAssign"), &Color4::operator |=)
        .Func<Color4 & (Color4::*)(const Color4 &)>(_SC("opXorAssign"), &Color4::operator ^=)
        .Func<Color4 & (Color4::*)(const Color4 &)>(_SC("opShlAssign"), &Color4::operator <<=)
        .Func<Color4 & (Color4::*)(const Color4 &)>(_SC("opShrAssign"), &Color4::operator >>=)

        .Func<Color4 & (Color4::*)(Color4::Value)>(_SC("opAddAssignS"), &Color4::operator +=)
        .Func<Color4 & (Color4::*)(Color4::Value)>(_SC("opSubAssignS"), &Color4::operator -=)
        .Func<Color4 & (Color4::*)(Color4::Value)>(_SC("opMulAssignS"), &Color4::operator *=)
        .Func<Color4 & (Color4::*)(Color4::Value)>(_SC("opDivAssignS"), &Color4::operator /=)
        .Func<Color4 & (Color4::*)(Color4::Value)>(_SC("opModAssignS"), &Color4::operator %=)
        .Func<Color4 & (Color4::*)(Color4::Value)>(_SC("opAndAssignS"), &Color4::operator &=)
        .Func<Color4 & (Color4::*)(Color4::Value)>(_SC("opOrAssignS"), &Color4::operator |=)
        .Func<Color4 & (Color4::*)(Color4::Value)>(_SC("opXorAssignS"), &Color4::operator ^=)
        .Func<Color4 & (Color4::*)(Color4::Value)>(_SC("opShlAssignS"), &Color4::operator <<=)
        .Func<Color4 & (Color4::*)(Color4::Value)>(_SC("opShrAssignS"), &Color4::operator >>=)

        .Func<Color4 & (Color4::*)(void)>(_SC("opPreInc"), &Color4::operator ++)
        .Func<Color4 & (Color4::*)(void)>(_SC("opPreDec"), &Color4::operator --)
        .Func<Color4 (Color4::*)(int)>(_SC("opPostInc"), &Color4::operator ++)
        .Func<Color4 (Color4::*)(int)>(_SC("opPostDec"), &Color4::operator --)

        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("opAdd"), &Color4::operator +)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("opSub"), &Color4::operator -)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("opMul"), &Color4::operator *)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("opDiv"), &Color4::operator /)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("opMod"), &Color4::operator %)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("opAnd"), &Color4::operator &)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("opOr"), &Color4::operator |)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("opShl"), &Color4::operator ^)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("opShl"), &Color4::operator <<)
        .Func<Color4 (Color4::*)(const Color4 &) const>(_SC("opShr"), &Color4::operator >>)

        .Func<Color4 (Color4::*)(Color4::Value) const>(_SC("opAddS"), &Color4::operator +)
        .Func<Color4 (Color4::*)(Color4::Value) const>(_SC("opSubS"), &Color4::operator -)
        .Func<Color4 (Color4::*)(Color4::Value) const>(_SC("opMulS"), &Color4::operator *)
        .Func<Color4 (Color4::*)(Color4::Value) const>(_SC("opDivS"), &Color4::operator /)
        .Func<Color4 (Color4::*)(Color4::Value) const>(_SC("opModS"), &Color4::operator %)
        .Func<Color4 (Color4::*)(Color4::Value) const>(_SC("opAndS"), &Color4::operator &)
        .Func<Color4 (Color4::*)(Color4::Value) const>(_SC("opOrS"), &Color4::operator |)
        .Func<Color4 (Color4::*)(Color4::Value) const>(_SC("opShlS"), &Color4::operator ^)
        .Func<Color4 (Color4::*)(Color4::Value) const>(_SC("opShlS"), &Color4::operator <<)
        .Func<Color4 (Color4::*)(Color4::Value) const>(_SC("opShrS"), &Color4::operator >>)

        .Func<Color4 (Color4::*)(void) const>(_SC("opUnPlus"), &Color4::operator +)
        .Func<Color4 (Color4::*)(void) const>(_SC("opUnMinus"), &Color4::operator -)
        .Func<Color4 (Color4::*)(void) const>(_SC("opCom"), &Color4::operator ~)

        .Func<bool (Color4::*)(const Color4 &) const>(_SC("opEqual"), &Color4::operator ==)
        .Func<bool (Color4::*)(const Color4 &) const>(_SC("opNotEqual"), &Color4::operator !=)
        .Func<bool (Color4::*)(const Color4 &) const>(_SC("opLessThan"), &Color4::operator <)
        .Func<bool (Color4::*)(const Color4 &) const>(_SC("opGreaterThan"), &Color4::operator >)
        .Func<bool (Color4::*)(const Color4 &) const>(_SC("opLessEqual"), &Color4::operator <=)
        .Func<bool (Color4::*)(const Color4 &) const>(_SC("opGreaterEqual"), &Color4::operator >=)
    );
}

} // Namespace:: SqMod
