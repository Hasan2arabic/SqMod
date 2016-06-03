// ------------------------------------------------------------------------------------------------
#include "HTTP.hpp"
#include "Manager.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
SQInteger HTTP::Typename(HSQUIRRELVM vm)
{
    static const SQChar name[] = _SC("SqMgHTTP");
    sq_pushstring(vm, name, sizeof(name));
    return 1;
}

// ------------------------------------------------------------------------------------------------
Int32 HTTP::Cmp(const HTTP & o) const
{
    if (m_Handle == o.m_Handle)
    {
        return 0;
    }
    else if (m_Handle.HndPtr() > o.m_Handle.HndPtr())
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------


} // Namespace:: SqMod
