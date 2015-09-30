#include "Misc/Skin.hpp"
#include "Register.hpp"
#include "Entity.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
const CSkin CSkin::NIL = CSkin();

// ------------------------------------------------------------------------------------------------
CSkin::CSkin() noexcept
    : m_ID(SQMOD_UNKNOWN), m_Name()
{

}

CSkin::CSkin(SQInt32 id) noexcept
    : m_ID(VALID_ENTITYGETEX(id, Max)), m_Name(GetSkinName(id))
{

}

CSkin::CSkin(const SQChar * name, SQInt32 id) noexcept
    : CSkin(IsSkinValid(GetSkinID(name)) ? GetSkinID(name) : id)
{

}

// ------------------------------------------------------------------------------------------------
CSkin::CSkin(const CSkin & s) noexcept
    : m_ID(s.m_ID)
    , m_Name(s.m_Name)
    , m_Tag(s.m_Tag)
    , m_Data(s.m_Data)
{

}

CSkin::CSkin(CSkin && s) noexcept
    : m_ID(s.m_ID)
    , m_Name(s.m_Name)
    , m_Tag(s.m_Tag)
    , m_Data(s.m_Data)
{

}

// ------------------------------------------------------------------------------------------------
CSkin::~CSkin()
{

}

// ------------------------------------------------------------------------------------------------
CSkin & CSkin::operator = (const CSkin & s) noexcept
{
    m_ID = s.m_ID;
    m_Name = s.m_Name;
    m_Tag = s.m_Tag;
    m_Data = s.m_Data;

    return *this;
}

CSkin & CSkin::operator = (CSkin && s) noexcept
{
    m_ID = s.m_ID;
    m_Name = s.m_Name;
    m_Tag = s.m_Tag;
    m_Data = s.m_Data;

    return *this;
}

// ------------------------------------------------------------------------------------------------
CSkin & CSkin::operator = (SQInt32 id) noexcept
{
    if (m_ID != id)
    {
        m_Name = GetSkinName(id);
        m_ID = id;
    }

    return *this;
}

// ------------------------------------------------------------------------------------------------
bool CSkin::operator == (const CSkin & s) const noexcept
{
    return (m_ID == s.m_ID);
}

bool CSkin::operator != (const CSkin & s) const noexcept
{
    return (m_ID != s.m_ID);
}

bool CSkin::operator < (const CSkin & s) const noexcept
{
    return (m_ID < s.m_ID);
}

bool CSkin::operator > (const CSkin & s) const noexcept
{
    return (m_ID < s.m_ID);
}

bool CSkin::operator <= (const CSkin & s) const noexcept
{
    return (m_ID <= s.m_ID);
}

bool CSkin::operator >= (const CSkin & s) const noexcept
{
    return (m_ID >= s.m_ID);
}

// ------------------------------------------------------------------------------------------------
SQInteger CSkin::Cmp(const CSkin & s) const noexcept
{
    return m_ID == s.m_ID ? 0 : (m_ID > s.m_ID ? 1 : -1);
}

// ------------------------------------------------------------------------------------------------
SQInteger CSkin::GetID() const noexcept
{
    return m_ID;
}

void CSkin::SetID(SQInt32 id) noexcept
{
    if (m_ID != id)
    {
        m_Name = GetSkinName(id);
        m_ID = id;
    }
}

// ------------------------------------------------------------------------------------------------
CSkin & CSkin::SetnGet(SQInt32 id) noexcept
{
    if (m_ID != id)
    {
        m_Name = GetSkinName(id);
        m_ID = id;
    }

    return *this;
}

// ------------------------------------------------------------------------------------------------
const SQChar * CSkin::GetGlobalTag() const noexcept
{
    return GlobalTag(m_ID);
}

void CSkin::SetGlobalTag(const SQChar * tag) const noexcept
{
    GlobalTag(m_ID, tag);
}

// ------------------------------------------------------------------------------------------------
SqObj & CSkin::GetGlobalData() const noexcept
{
    return GlobalData(m_ID);
}

void CSkin::SetGlobalData(SqObj & data) const noexcept
{
    GlobalData(m_ID, data);
}

// ------------------------------------------------------------------------------------------------
const SQChar * CSkin::GetLocalTag() const noexcept
{
    return m_Tag.c_str();
}

void CSkin::SetLocalTag(const SQChar * tag) noexcept
{
    m_Tag = tag;
}

// ------------------------------------------------------------------------------------------------
SqObj & CSkin::GetLocalData() noexcept
{
    return m_Data;
}

void CSkin::SetLocalData(SqObj & data) noexcept
{
    m_Data = data;
}

// ------------------------------------------------------------------------------------------------
bool CSkin::IsValid() const noexcept
{
    return (m_ID > 0);
}

// ------------------------------------------------------------------------------------------------
const SQChar * CSkin::GetName() const noexcept
{
    return m_Name.c_str();
}

// ------------------------------------------------------------------------------------------------
void CSkin::SetName(const SQChar * name) noexcept
{
    m_ID = GetSkinID(name);
    m_Name = GetSkinName(m_ID);
}

// ------------------------------------------------------------------------------------------------
void CSkin::Apply(const Reference< CPlayer > & player) const noexcept
{
    if (player)
    {
        _Func->SetPlayerSkin(player, m_ID);
    }
    else if (!player)
    {
        LogErr(_SC("Attempting to <set player skin> using an invalid argument: {0:d}"), _SCI32(player));
    }
    else
    {
        LogErr(_SC("Attempting to <set player skin> using an invalid instance: {0:d}"), m_ID);
    }
}

// ================================================================================================
bool Register_CSkin(HSQUIRRELVM vm)
{
    // Output debugging information
    LogDbg("Beginning registration of <CSkin> type");
    // Attempt to register the specified type
    Sqrat::RootTable(vm).Bind(_SC("CSkin"), Sqrat::Class< CSkin >(vm, _SC("CSkin"))
        .Ctor()
        .Ctor< SQInt32 >()
        .Ctor< const SQChar *, SQInt32 >()

        .Func(_SC("_cmp"), &CSkin::Cmp)

        .Prop(_SC("id"), &CSkin::GetID, &CSkin::SetID)
        .Prop(_SC("gtag"), &CSkin::GetGlobalTag, &CSkin::SetGlobalTag)
        .Prop(_SC("gdata"), &CSkin::GetGlobalData, &CSkin::SetGlobalData)
        .Prop(_SC("ltag"), &CSkin::GetLocalTag, &CSkin::SetLocalTag)
        .Prop(_SC("ldata"), &CSkin::GetLocalData, &CSkin::SetLocalData)
        .Prop(_SC("valid"), &CSkin::IsValid)
        .Prop(_SC("name"), &CSkin::GetName, &CSkin::SetName)

        .Func(_SC("setng"), &CSkin::SetnGet)

        .Func(_SC("apply"), &CSkin::Apply)
    );
    // Output debugging information
    LogDbg("Registration of <CSkin> type was successful");
    // Registration succeeded
    return true;
}

} // Namespace:: SqMod
