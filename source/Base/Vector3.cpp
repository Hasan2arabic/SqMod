// ------------------------------------------------------------------------------------------------
#include "Base/Vector3.hpp"
#include "Base/Vector4.hpp"
#include "Base/Quaternion.hpp"
#include "Base/Shared.hpp"
#include "Library/Random.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
const Vector3 Vector3::NIL = Vector3(0);
const Vector3 Vector3::MIN = Vector3(NumLimit< Vector3::Value >::Min);
const Vector3 Vector3::MAX = Vector3(NumLimit< Vector3::Value >::Max);

// ------------------------------------------------------------------------------------------------
SQChar Vector3::Delim = ',';

// ------------------------------------------------------------------------------------------------
Vector3::Vector3()
    : x(0.0), y(0.0), z(0.0)
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
Vector3::Vector3(Value sv)
    : x(sv), y(sv), z(sv)
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
Vector3::Vector3(Value xv, Value yv, Value zv)
    : x(xv), y(yv), z(zv)
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
Vector3::Vector3(const Vector3 & o)
    : x(o.x), y(o.y), z(o.z)
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
Vector3::~Vector3()
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
Vector3 & Vector3::operator = (const Vector3 & o)
{
    x = o.x;
    y = o.y;
    z = o.z;
    return *this;
}

// ------------------------------------------------------------------------------------------------
Vector3 & Vector3::operator = (Value s)
{
    x = s;
    y = s;
    z = s;
    return *this;
}

Vector3 & Vector3::operator = (const Vector4 & v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vector3 & Vector3::operator = (const Quaternion & q)
{
    x = q.x;
    y = q.y;
    z = q.z;
    return *this;
}

// ------------------------------------------------------------------------------------------------
Vector3 & Vector3::operator += (const Vector3 & v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3 & Vector3::operator -= (const Vector3 & v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3 & Vector3::operator *= (const Vector3 & v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vector3 & Vector3::operator /= (const Vector3 & v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

Vector3 & Vector3::operator %= (const Vector3 & v)
{
    x = fmod(x, v.x);
    y = fmod(y, v.y);
    z = fmod(z, v.z);
    return *this;
}

// ------------------------------------------------------------------------------------------------
Vector3 & Vector3::operator += (Value s)
{
    x += s;
    y += s;
    z += s;
    return *this;
}

Vector3 & Vector3::operator -= (Value s)
{
    x -= s;
    y -= s;
    z -= s;
    return *this;
}

Vector3 & Vector3::operator *= (Value s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vector3 & Vector3::operator /= (Value s)
{
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

Vector3 & Vector3::operator %= (Value s)
{
    x = fmod(x, s);
    y = fmod(y, s);
    z = fmod(z, s);
    return *this;
}

// ------------------------------------------------------------------------------------------------
Vector3 & Vector3::operator ++ ()
{
    ++x;
    ++y;
    ++z;
    return *this;
}

Vector3 & Vector3::operator -- ()
{
    --x;
    --y;
    --z;
    return *this;
}

// ------------------------------------------------------------------------------------------------
Vector3 Vector3::operator ++ (int)
{
    Vector3 state(*this);
    ++x;
    ++y;
    ++z;
    return state;
}

Vector3 Vector3::operator -- (int)
{
    Vector3 state(*this);
    --x;
    --y;
    --z;
    return state;
}

// ------------------------------------------------------------------------------------------------
Vector3 Vector3::operator + (const Vector3 & v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator - (const Vector3 & v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator * (const Vector3 & v) const
{
    return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::operator / (const Vector3 & v) const
{
    return Vector3(x / v.x, y / v.y, z / v.z);
}

Vector3 Vector3::operator % (const Vector3 & v) const
{
    return Vector3(fmod(x, v.x), fmod(y, v.y), fmod(z, v.z));
}

// ------------------------------------------------------------------------------------------------
Vector3 Vector3::operator + (Value s) const
{
    return Vector3(x + s, y + s, z + s);
}

Vector3 Vector3::operator - (Value s) const
{
    return Vector3(x - s, y - s, z - s);
}

Vector3 Vector3::operator * (Value s) const
{
    return Vector3(x * s, y * s, z * s);
}

Vector3 Vector3::operator / (Value s) const
{
    return Vector3(x / s, y / s, z / s);
}

Vector3 Vector3::operator % (Value s) const
{
    return Vector3(fmod(x, s), fmod(y, s), fmod(z, s));
}

// ------------------------------------------------------------------------------------------------
Vector3 Vector3::operator + () const
{
    return Vector3(fabs(x), fabs(y), fabs(z));
}

Vector3 Vector3::operator - () const
{
    return Vector3(-x, -y, -z);
}

// ------------------------------------------------------------------------------------------------
bool Vector3::operator == (const Vector3 & v) const
{
    return EpsEq(x, v.x) && EpsEq(y, v.y) && EpsEq(z, v.z);
}

bool Vector3::operator != (const Vector3 & v) const
{
    return !EpsEq(x, v.x) && !EpsEq(y, v.y) && !EpsEq(z, v.z);
}

bool Vector3::operator < (const Vector3 & v) const
{
    return EpsLt(x, v.x) && EpsLt(y, v.y) && EpsLt(z, v.z);
}

bool Vector3::operator > (const Vector3 & v) const
{
    return EpsGt(x, v.x) && EpsGt(y, v.y) && EpsGt(z, v.z);
}

bool Vector3::operator <= (const Vector3 & v) const
{
    return EpsLtEq(x, v.x) && EpsLtEq(y, v.y) && EpsLtEq(z, v.z);
}

bool Vector3::operator >= (const Vector3 & v) const
{
    return EpsGtEq(x, v.x) && EpsGtEq(y, v.y) && EpsGtEq(z, v.z);
}

// ------------------------------------------------------------------------------------------------
Int32 Vector3::Cmp(const Vector3 & o) const
{
    if (*this == o)
        return 0;
    else if (*this > o)
        return 1;
    else
        return -1;
}

// ------------------------------------------------------------------------------------------------
CSStr Vector3::ToString() const
{
    return ToStringF("%f,%f,%f", x, y, z);
}

// ------------------------------------------------------------------------------------------------
void Vector3::Set(Value ns)
{
    x = ns;
    y = ns;
    z = ns;
}

void Vector3::Set(Value nx, Value ny, Value nz)
{
    x = nx;
    y = ny;
    z = nz;
}

// ------------------------------------------------------------------------------------------------
void Vector3::Set(const Vector3 & v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

void Vector3::Set(const Vector4 & v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

void Vector3::Set(const Quaternion & q)
{
    x = q.x;
    y = q.y;
    z = q.z;
}

// ------------------------------------------------------------------------------------------------
void Vector3::Set(CSStr values, SQChar delim)
{
    Set(GetVector3(values, delim));
}

// ------------------------------------------------------------------------------------------------
void Vector3::Generate()
{
    x = GetRandomFloat32();
    y = GetRandomFloat32();
    z = GetRandomFloat32();
}

void Vector3::Generate(Value min, Value max)
{
    if (EpsLt(max, min))
    {
        SqThrow("max value is lower than min value");
    }
    else
    {
        x = GetRandomFloat32(min, max);
        y = GetRandomFloat32(min, max);
        z = GetRandomFloat32(min, max);
    }
}

void Vector3::Generate(Value xmin, Value xmax, Value ymin, Value ymax, Value zmin, Value zmax)
{
    if (EpsLt(xmax, xmin) || EpsLt(ymax, ymin) || EpsLt(zmax, zmin))
    {
        SqThrow("max value is lower than min value");
    }
    else
    {
        x = GetRandomFloat32(xmin, xmax);
        y = GetRandomFloat32(ymin, ymax);
        z = GetRandomFloat32(zmin, zmax);
    }
}

// ------------------------------------------------------------------------------------------------
Vector3 Vector3::Abs() const
{
    return Vector3(fabs(x), fabs(y), fabs(z));
}

// ================================================================================================
void Register_Vector3(HSQUIRRELVM vm)
{
    typedef Vector3::Value Val;

    RootTable(vm).Bind(_SC("Vector3"), Class< Vector3 >(vm, _SC("Vector3"))
        /* Constructors */
        .Ctor()
        .Ctor< Val >()
        .Ctor< Val, Val, Val >()
        /* Static Members */
        .SetStaticValue(_SC("Delim"), &Vector3::Delim)
        /* Member Variables */
        .Var(_SC("x"), &Vector3::x)
        .Var(_SC("y"), &Vector3::y)
        .Var(_SC("z"), &Vector3::z)
        /* Properties */
        .Prop(_SC("abs"), &Vector3::Abs)
        /* Core Metamethods */
        .Func(_SC("_tostring"), &Vector3::ToString)
        .Func(_SC("_cmp"), &Vector3::Cmp)
        /* Metamethods */
        .Func<Vector3 (Vector3::*)(const Vector3 &) const>(_SC("_add"), &Vector3::operator +)
        .Func<Vector3 (Vector3::*)(const Vector3 &) const>(_SC("_sub"), &Vector3::operator -)
        .Func<Vector3 (Vector3::*)(const Vector3 &) const>(_SC("_mul"), &Vector3::operator *)
        .Func<Vector3 (Vector3::*)(const Vector3 &) const>(_SC("_div"), &Vector3::operator /)
        .Func<Vector3 (Vector3::*)(const Vector3 &) const>(_SC("_modulo"), &Vector3::operator %)
        .Func<Vector3 (Vector3::*)(void) const>(_SC("_unm"), &Vector3::operator -)
        /* Setters */
        .Overload<void (Vector3::*)(Val)>(_SC("Set"), &Vector3::Set)
        .Overload<void (Vector3::*)(Val, Val, Val)>(_SC("Set"), &Vector3::Set)
        .Overload<void (Vector3::*)(const Vector3 &)>(_SC("SetVec3"), &Vector3::Set)
        .Overload<void (Vector3::*)(const Vector4 &)>(_SC("SetVec4"), &Vector3::Set)
        .Overload<void (Vector3::*)(const Quaternion &)>(_SC("SetQuat"), &Vector3::Set)
        .Overload<void (Vector3::*)(CSStr, SQChar)>(_SC("SetStr"), &Vector3::Set)
        /* Random Generators */
        .Overload<void (Vector3::*)(void)>(_SC("Generate"), &Vector3::Generate)
        .Overload<void (Vector3::*)(Val, Val)>(_SC("Generate"), &Vector3::Generate)
        .Overload<void (Vector3::*)(Val, Val, Val, Val, Val, Val)>(_SC("Generate"), &Vector3::Generate)
        /* Utility Methods */
        .Func(_SC("Clear"), &Vector3::Clear)
        /* Operator Exposure */
        .Func<Vector3 & (Vector3::*)(const Vector3 &)>(_SC("opAddAssign"), &Vector3::operator +=)
        .Func<Vector3 & (Vector3::*)(const Vector3 &)>(_SC("opSubAssign"), &Vector3::operator -=)
        .Func<Vector3 & (Vector3::*)(const Vector3 &)>(_SC("opMulAssign"), &Vector3::operator *=)
        .Func<Vector3 & (Vector3::*)(const Vector3 &)>(_SC("opDivAssign"), &Vector3::operator /=)
        .Func<Vector3 & (Vector3::*)(const Vector3 &)>(_SC("opModAssign"), &Vector3::operator %=)

        .Func<Vector3 & (Vector3::*)(Vector3::Value)>(_SC("opAddAssignS"), &Vector3::operator +=)
        .Func<Vector3 & (Vector3::*)(Vector3::Value)>(_SC("opSubAssignS"), &Vector3::operator -=)
        .Func<Vector3 & (Vector3::*)(Vector3::Value)>(_SC("opMulAssignS"), &Vector3::operator *=)
        .Func<Vector3 & (Vector3::*)(Vector3::Value)>(_SC("opDivAssignS"), &Vector3::operator /=)
        .Func<Vector3 & (Vector3::*)(Vector3::Value)>(_SC("opModAssignS"), &Vector3::operator %=)

        .Func<Vector3 & (Vector3::*)(void)>(_SC("opPreInc"), &Vector3::operator ++)
        .Func<Vector3 & (Vector3::*)(void)>(_SC("opPreDec"), &Vector3::operator --)
        .Func<Vector3 (Vector3::*)(int)>(_SC("opPostInc"), &Vector3::operator ++)
        .Func<Vector3 (Vector3::*)(int)>(_SC("opPostDec"), &Vector3::operator --)

        .Func<Vector3 (Vector3::*)(const Vector3 &) const>(_SC("opAdd"), &Vector3::operator +)
        .Func<Vector3 (Vector3::*)(const Vector3 &) const>(_SC("opSub"), &Vector3::operator -)
        .Func<Vector3 (Vector3::*)(const Vector3 &) const>(_SC("opMul"), &Vector3::operator *)
        .Func<Vector3 (Vector3::*)(const Vector3 &) const>(_SC("opDiv"), &Vector3::operator /)
        .Func<Vector3 (Vector3::*)(const Vector3 &) const>(_SC("opMod"), &Vector3::operator %)

        .Func<Vector3 (Vector3::*)(Vector3::Value) const>(_SC("opAddS"), &Vector3::operator +)
        .Func<Vector3 (Vector3::*)(Vector3::Value) const>(_SC("opSubS"), &Vector3::operator -)
        .Func<Vector3 (Vector3::*)(Vector3::Value) const>(_SC("opMulS"), &Vector3::operator *)
        .Func<Vector3 (Vector3::*)(Vector3::Value) const>(_SC("opDivS"), &Vector3::operator /)
        .Func<Vector3 (Vector3::*)(Vector3::Value) const>(_SC("opModS"), &Vector3::operator %)

        .Func<Vector3 (Vector3::*)(void) const>(_SC("opUnPlus"), &Vector3::operator +)
        .Func<Vector3 (Vector3::*)(void) const>(_SC("opUnMinus"), &Vector3::operator -)

        .Func<bool (Vector3::*)(const Vector3 &) const>(_SC("opEqual"), &Vector3::operator ==)
        .Func<bool (Vector3::*)(const Vector3 &) const>(_SC("opNotEqual"), &Vector3::operator !=)
        .Func<bool (Vector3::*)(const Vector3 &) const>(_SC("opLessThan"), &Vector3::operator <)
        .Func<bool (Vector3::*)(const Vector3 &) const>(_SC("opGreaterThan"), &Vector3::operator >)
        .Func<bool (Vector3::*)(const Vector3 &) const>(_SC("opLessEqual"), &Vector3::operator <=)
        .Func<bool (Vector3::*)(const Vector3 &) const>(_SC("opGreaterEqual"), &Vector3::operator >=)
    );
}

} // Namespace:: SqMod
