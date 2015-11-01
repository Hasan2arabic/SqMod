#include "Misc/Model.hpp"
#include "Base/Vector3.hpp"
#include "Entity.hpp"
#include "Register.hpp"
#include "Core.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
const CModel CModel::NIL;

// ------------------------------------------------------------------------------------------------
CModel::CModel()
    : m_ID(SQMOD_UNKNOWN)
{

}

CModel::CModel(SQInt32 id)
    : m_ID(VALID_ENTITYGETEX(id, Max))
{

}

CModel::CModel(const SQChar * name, SQInt32 id)
    : m_ID(GetWeaponID(name))
{
    if (VALID_ENTITYGETEX(m_ID, Max))
    {
        m_ID = id;
    }
}

// ------------------------------------------------------------------------------------------------
CModel::CModel(const CModel & m)
    : m_ID(m.m_ID)
    , m_Tag(m.m_Tag)
    , m_Data(m.m_Data)
{

}

CModel::CModel(CModel && m)
    : m_ID(m.m_ID)
    , m_Tag(m.m_Tag)
    , m_Data(m.m_Data)
{

}

// ------------------------------------------------------------------------------------------------
CModel::~CModel()
{

}

// ------------------------------------------------------------------------------------------------
CModel & CModel::operator = (const CModel & m)
{
    m_ID = m.m_ID;
    m_Tag = m.m_Tag;
    m_Data = m.m_Data;

    return *this;
}

CModel & CModel::operator = (CModel && m)
{
    m_ID = m.m_ID;
    m_Tag = m.m_Tag;
    m_Data = m.m_Data;

    return *this;
}

// ------------------------------------------------------------------------------------------------
CModel & CModel::operator = (SQInt32 id)
{
    m_ID = VALID_ENTITYGETEX(id, Max);

    return *this;
}

// ------------------------------------------------------------------------------------------------
bool CModel::operator == (const CModel & m) const
{
    return (m_ID == m.m_ID);
}

bool CModel::operator != (const CModel & m) const
{
    return (m_ID != m.m_ID);
}

bool CModel::operator < (const CModel & m) const
{
    return (m_ID < m.m_ID);
}

bool CModel::operator > (const CModel & m) const
{
    return (m_ID < m.m_ID);
}

bool CModel::operator <= (const CModel & m) const
{
    return (m_ID <= m.m_ID);
}

bool CModel::operator >= (const CModel & m) const
{
    return (m_ID >= m.m_ID);
}

// ------------------------------------------------------------------------------------------------
SQInteger CModel::Cmp(const CModel & m) const
{
    if (m_ID == m.m_ID)
    {
        return 0;
    }
    else if (m_ID > m.m_ID)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

// ------------------------------------------------------------------------------------------------
const SQChar * CModel::ToString() const
{
    return GetModelName(m_ID);
}

// ------------------------------------------------------------------------------------------------
SQInteger CModel::GetID() const
{
    return m_ID;
}

void CModel::SetID(SQInt32 id)
{
    m_ID = VALID_ENTITYGETEX(id, Max);
}

// ------------------------------------------------------------------------------------------------
CModel & CModel::SetnGet(SQInt32 id)
{
    m_ID = VALID_ENTITYGETEX(id, Max);

    return *this;
}

// ------------------------------------------------------------------------------------------------
const SQChar * CModel::GetGlobalTag() const
{
    return GlobalTag(m_ID);
}

void CModel::SetGlobalTag(const SQChar * tag) const
{
    GlobalTag(m_ID, tag);
}

// ------------------------------------------------------------------------------------------------
SqObj & CModel::GetGlobalData() const
{
    return GlobalData(m_ID);
}

void CModel::SetGlobalData(SqObj & data) const
{
    GlobalData(m_ID, data);
}

// ------------------------------------------------------------------------------------------------
const SQChar * CModel::GetLocalTag() const
{
    return m_Tag.c_str();
}

void CModel::SetLocalTag(const SQChar * tag)
{
    m_Tag = tag;
}

// ------------------------------------------------------------------------------------------------
SqObj & CModel::GetLocalData()
{
    return m_Data;
}

void CModel::SetLocalData(SqObj & data)
{
    m_Data = data;
}

// ------------------------------------------------------------------------------------------------
bool CModel::IsValid() const
{
    return (VALID_ENTITYEX(m_ID, Max));
}

// ------------------------------------------------------------------------------------------------
const SQChar * CModel::GetName() const
{
    return GetModelName(m_ID);
}

// ------------------------------------------------------------------------------------------------
void CModel::SetName(const SQChar * name)
{
    SQMOD_UNUSED_VAR(name);
    m_ID = -1; /* @TODO Implement! */
}

// ------------------------------------------------------------------------------------------------
bool CModel::IsWeapon() const
{
    return IsModelWeapon(m_ID);
}

bool CModel::IsActuallyWeapon() const
{
    return IsModelActuallyWeapon(m_ID);
}

// ------------------------------------------------------------------------------------------------
Reference< CObject > CModel::Object(SQInt32 world, const Vector3 & pos, SQInt32 alpha, SQInt32 header, \
                                    SqObj & payload) const
{
    return _Core->NewObject(m_ID, world, pos.x, pos.y, pos.z, alpha, header, payload);
}

Reference< CObject > CModel::Object(SQInt32 world, SQFloat x, SQFloat y, SQFloat z, SQInt32 alpha, \
                                    SQInt32 header, SqObj & payload) const
{
    return _Core->NewObject(m_ID, world, x, y, z, alpha, header, payload);
}

// ------------------------------------------------------------------------------------------------
Reference< CPickup > CModel::Pickup(SQInt32 world, SQInt32 quantity, const Vector3 & pos, SQInt32 alpha, \
                                    bool automatic, SQInt32 header, SqObj & payload) const
{
    return _Core->NewPickup(m_ID, world, quantity, pos.x, pos.y, pos.z, alpha, automatic, header, payload);
}

Reference< CPickup > CModel::Pickup(SQInt32 world, SQInt32 quantity, SQFloat x, SQFloat y, SQFloat z, \
                                    SQInt32 alpha, bool automatic, SQInt32 header, SqObj & payload) const
{
    return _Core->NewPickup(m_ID, world, quantity, x, y, z, alpha, automatic, header, payload);
}

// ================================================================================================
bool Register_CModel(HSQUIRRELVM vm)
{
    // Output debugging information
    LogDbg("Beginning registration of <CModel> type");
    // Attempt to register the specified type
    Sqrat::RootTable(vm).Bind(_SC("CModel"), Sqrat::Class< CModel >(vm, _SC("CModel"))
        /* Constructors */
        .Ctor()
        .Ctor< SQInt32 >()
        .Ctor< const SQChar *, SQInt32 >()
        /* Metamethods */
        .Func(_SC("_cmp"), &CModel::Cmp)
        .Func(_SC("_tostring"), &CModel::ToString)
        /* Properties */
        .Prop(_SC("id"), &CModel::GetID, &CModel::SetID)
        .Prop(_SC("gtag"), &CModel::GetGlobalTag, &CModel::SetGlobalTag)
        .Prop(_SC("gdata"), &CModel::GetGlobalData, &CModel::SetGlobalData)
        .Prop(_SC("ltag"), &CModel::GetLocalTag, &CModel::SetLocalTag)
        .Prop(_SC("ldata"), &CModel::GetLocalData, &CModel::SetLocalData)
        .Prop(_SC("valid"), &CModel::IsValid)
        .Prop(_SC("name"), &CModel::GetName, &CModel::SetName)
        .Prop(_SC("weapon"), &CModel::IsWeapon)
        .Prop(_SC("truly_weapon"), &CModel::IsActuallyWeapon)
        /* Functions */
        .Func(_SC("setng"), &CModel::SetnGet)
        /* Overloads */
        .Overload< Reference< CObject > (CModel::*)(SQInt32, const Vector3 &, SQInt32, SQInt32, SqObj &) const >
            (_SC("object"), &CModel::Object)
        .Overload< Reference< CObject > (CModel::*)(SQInt32, SQFloat, SQFloat, SQFloat, SQInt32, SQInt32, SqObj &) const >
            (_SC("object"), &CModel::Object)
        .Overload< Reference< CPickup > (CModel::*)(SQInt32, SQInt32, const Vector3 &, SQInt32, bool, SQInt32, SqObj &) const >
            (_SC("pickup"), &CModel::Pickup)
        .Overload< Reference< CPickup > (CModel::*)(SQInt32, SQInt32, SQFloat, SQFloat, SQFloat, SQInt32, bool, SQInt32, SqObj &) const >
            (_SC("pickup"), &CModel::Pickup)
    );
    // Output debugging information
    LogDbg("Registration of <CModel> type was successful");
    // Registration succeeded
    return true;
}

} // Namespace:: SqMod
