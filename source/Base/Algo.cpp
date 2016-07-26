// ------------------------------------------------------------------------------------------------
#include "Base/Algo.hpp"

// ------------------------------------------------------------------------------------------------
#include "Entity/Blip.hpp"
#include "Entity/Checkpoint.hpp"
#include "Entity/Keybind.hpp"
#include "Entity/Object.hpp"
#include "Entity/Pickup.hpp"
#include "Entity/Player.hpp"
#include "Entity/Vehicle.hpp"

// ------------------------------------------------------------------------------------------------
#define SQMOD_VALID_NAME_STR(t) if (!t) { STHROWF("The specified name is invalid"); }

// ------------------------------------------------------------------------------------------------
namespace SqMod {
namespace Algo {

/* ------------------------------------------------------------------------------------------------
 * Used to fake a string so a raw buffer can be used with search algorithms.
*/
struct FakeString
{
    // --------------------------------------------------------------------------------------------
    SQChar          mBuffer[SQMOD_PLAYER_TMP_BUFFER]; // Buffer to hold the data.
    std::size_t     mSize; // The size of the data in the buffer.

    /* --------------------------------------------------------------------------------------------
     * Default constructor.
    */
    FakeString()
        : mBuffer(), mSize(0)
    {
        /* ... */
    }

    /* --------------------------------------------------------------------------------------------
     * Grab the player name from the server into the buffer.
    */
    void GrabName(int id)
    {
        // Clear any previous string (just in case)
        mBuffer[0] = '\0';
        mSize = 0;
        // Query the server for the name of the managed player
        if (_Func->GetPlayerName(id, mBuffer, sizeof(mBuffer)) == vcmpErrorNone)
        {
            mSize = std::strlen(mBuffer); // Calculate the name length
        }
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the size of the name.
    */
    std::size_t size() const
    {
        return mSize;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the string buffer.
    */
    CSStr c_str() const
    {
        return mBuffer;
    }

    /* --------------------------------------------------------------------------------------------
     * Find in buffer contents of another string.
    */
    std::size_t find(CSStr s) const
    {
        CCStr r = std::strstr(mBuffer, s);
        return (r == nullptr) ? String::npos : (r - mBuffer);
    }

    /* --------------------------------------------------------------------------------------------
     * Compare the buffer contents with another string.
    */
    int compare(CSStr s) const
    {
        return std::strcmp(mBuffer, s);
    }

    /* --------------------------------------------------------------------------------------------
     * Compare the buffer contents with another string.
    */
    int compare(std::size_t pos, std::size_t len, CSStr s) const
    {
        return std::strncmp(mBuffer + pos, s, len);
    }
};

/* ------------------------------------------------------------------------------------------------
 * Functor to retrieve the player name.
*/
struct PlayerName
{
    // --------------------------------------------------------------------------------------------
    FakeString mStr; // The string where the name is stored.

    /* --------------------------------------------------------------------------------------------
     * Function call operator.
    */
    const FakeString & operator () (const typename InstSpec< CPlayer >::Instance & inst)
    {
        mStr.GrabName(inst.mID);
        return mStr;
    }
};

// ------------------------------------------------------------------------------------------------
static const Object & Blip_FindBySprID(Int32 sprid)
{
    // Perform a range check on the specified identifier
    if (sprid < 0)
    {
        STHROWF("The specified sprite identifier is invalid: %d", sprid);
    }
    // Obtain the ends of the entity pool
    Core::Blips::const_iterator itr = Core::Get().GetBlips().cbegin();
    Core::Blips::const_iterator end = Core::Get().GetBlips().cend();
    // Process each entity in the pool
    for (; itr != end; ++itr)
    {
        // Does the identifier match the specified one?
        if (itr->mSprID == sprid)
        {
            return itr->mObj; // Stop searching and return this entity
        }
    }
    // Unable to locate a blip matching the specified identifier
    return NullObject();
}

/* ------------------------------------------------------------------------------------------------
 * Collect all players where the name matches or not the specified one.
*/
static inline Array Player_AllWhereNameEquals(bool neg, bool cs, CSStr name)
{
    SQMOD_VALID_NAME_STR(name)
    // Remember the current stack size
    const StackGuard sg;
    // Allocate an empty array on the stack
    sq_newarray(DefaultVM::Get(), 0);
    // Process each entity in the pool
    EachEquals(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
               ValidInstFunc< CPlayer >(), PlayerName(),
               AppendElemFunc< CPlayer >(), name, !neg, cs);
    // Return the array at the top of the stack
    return Var< Array >(DefaultVM::Get(), -1).value;
}

/* ------------------------------------------------------------------------------------------------
 * Collect all players where the name begins or not with the specified string.
*/
static inline Array Player_AllWhereNameBegins(bool neg, bool cs, CSStr name)
{
    SQMOD_VALID_NAME_STR(name)
    // Remember the current stack size
    const StackGuard sg;
    // Allocate an empty array on the stack
    sq_newarray(DefaultVM::Get(), 0);
    // Process each entity in the pool
    EachBegins(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                AppendElemFunc< CPlayer >(), name, strlen(name), !neg, cs);
    // Return the array at the top of the stack
    return Var< Array >(DefaultVM::Get(), -1).value;
}

/* ------------------------------------------------------------------------------------------------
 * Collect all players where the name ends or not with the specified string.
*/
static inline Array Player_AllWhereNameEnds(bool neg, bool cs, CSStr name)
{
    SQMOD_VALID_NAME_STR(name)
    // Remember the current stack size
    const StackGuard sg;
    // Allocate an empty array on the stack
    sq_newarray(DefaultVM::Get(), 0);
    // Process each entity in the pool
    EachEnds(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                AppendElemFunc< CPlayer >(), name, strlen(name), !neg, cs);
    // Return the array at the top of the stack
    return Var< Array >(DefaultVM::Get(), -1).value;
}

/* ------------------------------------------------------------------------------------------------
 * Collect all players where the name contains or not the specified string.
*/
static inline Array Player_AllWhereNameContains(bool neg, bool cs, CSStr name)
{
    SQMOD_VALID_NAME_STR(name)
    // Remember the current stack size
    const StackGuard sg;
    // Allocate an empty array on the stack
    sq_newarray(DefaultVM::Get(), 0);
    // Process each entity in the pool
    EachContains(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                AppendElemFunc< CPlayer >(), name, !neg, cs);
    // Return the array at the top of the stack
    return Var< Array >(DefaultVM::Get(), -1).value;
}

/* ------------------------------------------------------------------------------------------------
 * Retrieve the first player where the name matches or not the specified one.
*/
static inline Object Player_FirstWhereNameEquals(bool neg, bool cs, CSStr name)
{
    SQMOD_VALID_NAME_STR(name)
    // Create a new element receiver
    RecvElemFunc< CPlayer > recv;
    // Process each entity in the pool
    FirstEquals(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                std::reference_wrapper< RecvElemFunc< CPlayer > >(recv), name, !neg, cs);
    // Return the received element, if any
    return recv.mObj;
}

/* ------------------------------------------------------------------------------------------------
 * Retrieve the first player where the name begins or not with the specified string.
*/
static inline Object Player_FirstWhereNameBegins(bool neg, bool cs, CSStr name)
{
    SQMOD_VALID_NAME_STR(name)
    // Create a new element receiver
    RecvElemFunc< CPlayer > recv;
    // Process each entity in the pool
    FirstBegins(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                std::reference_wrapper< RecvElemFunc< CPlayer > >(recv), name, strlen(name), !neg, cs);
    // Return the received element, if any
    return recv.mObj;
}

/* ------------------------------------------------------------------------------------------------
 * Retrieve the first player where the name ends or not with the specified string.
*/
static inline Object Player_FirstWhereNameEnds(bool neg, bool cs, CSStr name)
{
    SQMOD_VALID_NAME_STR(name)
    // Create a new element receiver
    RecvElemFunc< CPlayer > recv;
    // Process each entity in the pool
    FirstEnds(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                std::reference_wrapper< RecvElemFunc< CPlayer > >(recv), name, strlen(name), !neg, cs);
    // Return the received element, if any
    return recv.mObj;
}

/* ------------------------------------------------------------------------------------------------
 * Retrieve the first player where the name contains or not the specified string.
*/
static inline Object Player_FirstWhereNameContains(bool neg, bool cs, CSStr name)
{
    SQMOD_VALID_NAME_STR(name)
    // Create a new element receiver
    RecvElemFunc< CPlayer > recv;
    // Process each entity in the pool
    FirstContains(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                std::reference_wrapper< RecvElemFunc< CPlayer > >(recv), name, !neg, cs);
    // Return the received element, if any
    return recv.mObj;
}

/* --------------------------------------------------------------------------------------------
 * Process all entities of this type where the name matches or not the specified one.
*/
static inline Uint32 Player_EachWhereNameEquals(bool neg, bool cs, CSStr name, Object & env, Function & func)
{
    SQMOD_VALID_NAME_STR(name)
    // Create a new element forwarder
    ForwardElemFunc< CPlayer > fwd(env, func);
    // Process each entity in the pool
    EachEquals(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                std::reference_wrapper< ForwardElemFunc< CPlayer > >(fwd), name, !neg, cs);
    // Return the forward count
    return fwd.mCount;
}

/* --------------------------------------------------------------------------------------------
 * Process all entities of this type where the name begins with the specified string.
*/
static inline Uint32 Player_EachWhereNameBegins(bool neg, bool cs, CSStr name, Object & env, Function & func)
{
    SQMOD_VALID_NAME_STR(name)
    // Create a new element forwarder
    ForwardElemFunc< CPlayer > fwd(env, func);
    // Process each entity in the pool
    EachBegins(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                std::reference_wrapper< ForwardElemFunc< CPlayer > >(fwd), name, strlen(name), !neg, cs);
    // Return the forward count
    return fwd.mCount;
}

/* --------------------------------------------------------------------------------------------
 * Process all entities of this type where the name ends or not with the specified string.
*/
static inline Uint32 Player_EachWhereNameEnds(bool neg, bool cs, CSStr name, Object & env, Function & func)
{
    SQMOD_VALID_NAME_STR(name)
    // Create a new element forwarder
    ForwardElemFunc< CPlayer > fwd(env, func);
    // Process each entity in the pool
    EachEnds(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                std::reference_wrapper< ForwardElemFunc< CPlayer > >(fwd), name, strlen(name), !neg, cs);
    // Return the forward count
    return fwd.mCount;
}

/* --------------------------------------------------------------------------------------------
 * Process all entities of this type where the name contains the specified string.
*/
static inline Uint32 Player_EachWhereNameContains(bool neg, bool cs, CSStr name, Object & env, Function & func)
{
    SQMOD_VALID_NAME_STR(name)
    // Create a new element forwarder
    ForwardElemFunc< CPlayer > fwd(env, func);
    // Process each entity in the pool
    EachContains(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                std::reference_wrapper< ForwardElemFunc< CPlayer > >(fwd), name, !neg, cs);
    // Return the forward count
    return fwd.mCount;
}

/* --------------------------------------------------------------------------------------------
 * Count all entities of this type where the name matches or not the specified one.
*/
static inline Uint32 Player_CountWhereNameEquals(bool neg, bool cs, CSStr name)
{
    SQMOD_VALID_NAME_STR(name)
    // Create a new element counter
    CountElemFunc< CPlayer > cnt;
    // Process each entity in the pool
    EachEquals(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                std::reference_wrapper< CountElemFunc< CPlayer > >(cnt), name, !neg, cs);
    // Return the count
    return cnt;
}

/* --------------------------------------------------------------------------------------------
 * Count all entities of this type where the name begins with the specified string.
*/
static inline Uint32 Player_CountWhereNameBegins(bool neg, bool cs, CSStr name)
{
    SQMOD_VALID_NAME_STR(name)
    // Create a new element counter
    CountElemFunc< CPlayer > cnt;
    // Process each entity in the pool
    EachBegins(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                std::reference_wrapper< CountElemFunc< CPlayer > >(cnt), name, strlen(name), !neg, cs);
    // Return the count
    return cnt;
}

/* --------------------------------------------------------------------------------------------
 * Count all entities of this type where the name ends or not with the specified string.
*/
static inline Uint32 Player_CountWhereNameEnds(bool neg, bool cs, CSStr name)
{
    SQMOD_VALID_NAME_STR(name)
    // Create a new element counter
    CountElemFunc< CPlayer > cnt;
    // Process each entity in the pool
    EachEnds(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                std::reference_wrapper< CountElemFunc< CPlayer > >(cnt), name, strlen(name), !neg, cs);
    // Return the count
    return cnt;
}

/* --------------------------------------------------------------------------------------------
 * Count all entities of this type where the name contains the specified string.
*/
static inline Uint32 Player_CountWhereNameContains(bool neg, bool cs, CSStr name)
{
    SQMOD_VALID_NAME_STR(name)
    // Create a new element counter
    CountElemFunc< CPlayer > cnt;
    // Process each entity in the pool
    EachContains(InstSpec< CPlayer >::CBegin(), InstSpec< CPlayer >::CEnd(),
                ValidInstFunc< CPlayer >(), PlayerName(),
                std::reference_wrapper< CountElemFunc< CPlayer > >(cnt), name, !neg, cs);
    // Return the count
    return cnt;
}

// ================================================================================================
void Register(HSQUIRRELVM vm)
{
    Table collect_ns(vm);

    collect_ns.Bind(_SC("Blip"), Table(vm)
        .Func(_SC("Active"), &Entity< CBlip >::AllActive)
        .Func(_SC("TagEquals"), &Entity< CBlip >::AllWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CBlip >::AllWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CBlip >::AllWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CBlip >::AllWhereTagContains)
    );

    collect_ns.Bind(_SC("Checkpoint"), Table(vm)
        .Func(_SC("Active"), &Entity< CCheckpoint >::AllActive)
        .Func(_SC("TagEquals"), &Entity< CCheckpoint >::AllWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CCheckpoint >::AllWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CCheckpoint >::AllWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CCheckpoint >::AllWhereTagContains)
    );

    collect_ns.Bind(_SC("Keybind"), Table(vm)
        .Func(_SC("Active"), &Entity< CKeybind >::AllActive)
        .Func(_SC("TagEquals"), &Entity< CKeybind >::AllWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CKeybind >::AllWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CKeybind >::AllWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CKeybind >::AllWhereTagContains)
    );

    collect_ns.Bind(_SC("Object"), Table(vm)
        .Func(_SC("Active"), &Entity< CObject >::AllActive)
        .Func(_SC("TagEquals"), &Entity< CObject >::AllWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CObject >::AllWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CObject >::AllWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CObject >::AllWhereTagContains)
    );

    collect_ns.Bind(_SC("Pickup"), Table(vm)
        .Func(_SC("Active"), &Entity< CPickup >::AllActive)
        .Func(_SC("TagEquals"), &Entity< CPickup >::AllWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CPickup >::AllWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CPickup >::AllWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CPickup >::AllWhereTagContains)
    );

    collect_ns.Bind(_SC("Player"), Table(vm)
        .Func(_SC("Active"), &Entity< CPlayer >::AllActive)
        .Func(_SC("TagEquals"), &Entity< CPlayer >::AllWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CPlayer >::AllWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CPlayer >::AllWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CPlayer >::AllWhereTagContains)
        .Func(_SC("NameEquals"), &Player_AllWhereNameEquals)
        .Func(_SC("NameBegins"), &Player_AllWhereNameBegins)
        .Func(_SC("NameEnds"), &Player_AllWhereNameEnds)
        .Func(_SC("NameContains"), &Player_AllWhereNameContains)
    );

    collect_ns.Bind(_SC("Vehicle"), Table(vm)
        .Func(_SC("Active"), &Entity< CVehicle >::AllActive)
        .Func(_SC("TagEquals"), &Entity< CVehicle >::AllWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CVehicle >::AllWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CVehicle >::AllWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CVehicle >::AllWhereTagContains)
    );

    RootTable(vm).Bind(_SC("SqCollect"), collect_ns);

    Table find_ns(vm);

    find_ns.Bind(_SC("Blip"), Table(vm)
        .Func(_SC("WithID"), &Entity< CBlip >::FindByID)
        .Func(_SC("TagEquals"), &Entity< CBlip >::FirstWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CBlip >::FirstWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CBlip >::FirstWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CBlip >::FirstWhereTagContains)
        .Func(_SC("WithSprID"), &Blip_FindBySprID)
    );

    find_ns.Bind(_SC("Checkpoint"), Table(vm)
        .Func(_SC("WithID"), &Entity< CCheckpoint >::FindByID)
        .Func(_SC("TagEquals"), &Entity< CCheckpoint >::FirstWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CCheckpoint >::FirstWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CCheckpoint >::FirstWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CCheckpoint >::FirstWhereTagContains)
    );

    find_ns.Bind(_SC("Keybind"), Table(vm)
        .Func(_SC("WithID"), &Entity< CKeybind >::FindByID)
        .Func(_SC("TagEquals"), &Entity< CKeybind >::FirstWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CKeybind >::FirstWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CKeybind >::FirstWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CKeybind >::FirstWhereTagContains)
    );

    find_ns.Bind(_SC("Object"), Table(vm)
        .Func(_SC("WithID"), &Entity< CObject >::FindByID)
        .Func(_SC("TagEquals"), &Entity< CObject >::FirstWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CObject >::FirstWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CObject >::FirstWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CObject >::FirstWhereTagContains)
    );

    find_ns.Bind(_SC("Pickup"), Table(vm)
        .Func(_SC("WithID"), &Entity< CPickup >::FindByID)
        .Func(_SC("TagEquals"), &Entity< CPickup >::FirstWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CPickup >::FirstWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CPickup >::FirstWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CPickup >::FirstWhereTagContains)
    );

    find_ns.Bind(_SC("Player"), Table(vm)
        .Func(_SC("WithID"), &Entity< CPlayer >::FindByID)
        .Func(_SC("TagEquals"), &Entity< CPlayer >::FirstWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CPlayer >::FirstWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CPlayer >::FirstWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CPlayer >::FirstWhereTagContains)
        .Func(_SC("NameEquals"), &Player_FirstWhereNameEquals)
        .Func(_SC("NameBegins"), &Player_FirstWhereNameBegins)
        .Func(_SC("NameEnds"), &Player_FirstWhereNameEnds)
        .Func(_SC("NameContains"), &Player_FirstWhereNameContains)
    );

    find_ns.Bind(_SC("Vehicle"), Table(vm)
        .Func(_SC("WithID"), &Entity< CVehicle >::FindByID)
        .Func(_SC("TagEquals"), &Entity< CVehicle >::FirstWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CVehicle >::FirstWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CVehicle >::FirstWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CVehicle >::FirstWhereTagContains)
    );

    RootTable(vm).Bind(_SC("SqFind"), find_ns);

    Table each_ns(vm);

    each_ns.Bind(_SC("Blip"), Table(vm)
        .Func(_SC("Active"), &Entity< CBlip >::EachActive)
        .Func(_SC("TagEquals"), &Entity< CBlip >::EachWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CBlip >::EachWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CBlip >::EachWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CBlip >::EachWhereTagContains)
    );

    each_ns.Bind(_SC("Checkpoint"), Table(vm)
        .Func(_SC("Active"), &Entity< CCheckpoint >::EachActive)
        .Func(_SC("TagEquals"), &Entity< CCheckpoint >::EachWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CCheckpoint >::EachWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CCheckpoint >::EachWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CCheckpoint >::EachWhereTagContains)
    );

    each_ns.Bind(_SC("Keybind"), Table(vm)
        .Func(_SC("Active"), &Entity< CKeybind >::EachActive)
        .Func(_SC("TagEquals"), &Entity< CKeybind >::EachWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CKeybind >::EachWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CKeybind >::EachWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CKeybind >::EachWhereTagContains)
    );

    each_ns.Bind(_SC("Object"), Table(vm)
        .Func(_SC("Active"), &Entity< CObject >::EachActive)
        .Func(_SC("TagEquals"), &Entity< CObject >::EachWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CObject >::EachWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CObject >::EachWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CObject >::EachWhereTagContains)
    );

    each_ns.Bind(_SC("Pickup"), Table(vm)
        .Func(_SC("Active"), &Entity< CPickup >::EachActive)
        .Func(_SC("TagEquals"), &Entity< CPickup >::EachWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CPickup >::EachWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CPickup >::EachWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CPickup >::EachWhereTagContains)
    );

    each_ns.Bind(_SC("Player"), Table(vm)
        .Func(_SC("Active"), &Entity< CPlayer >::EachActive)
        .Func(_SC("TagEquals"), &Entity< CPlayer >::EachWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CPlayer >::EachWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CPlayer >::EachWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CPlayer >::EachWhereTagContains)
        .Func(_SC("NameEquals"), &Player_EachWhereNameEquals)
        .Func(_SC("NameBegins"), &Player_EachWhereNameBegins)
        .Func(_SC("NameEnds"), &Player_EachWhereNameEnds)
        .Func(_SC("NameContains"), &Player_EachWhereNameContains)
    );

    each_ns.Bind(_SC("Vehicle"), Table(vm)
        .Func(_SC("Active"), &Entity< CVehicle >::EachActive)
        .Func(_SC("TagEquals"), &Entity< CVehicle >::EachWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CVehicle >::EachWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CVehicle >::EachWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CVehicle >::EachWhereTagContains)
    );

    RootTable(vm).Bind(_SC("SqForeach"), each_ns);

    Table count_ns(vm);

    count_ns.Bind(_SC("Blip"), Table(vm)
        .Func(_SC("Active"), &Entity< CBlip >::CountActive)
        .Func(_SC("TagEquals"), &Entity< CBlip >::CountWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CBlip >::CountWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CBlip >::CountWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CBlip >::CountWhereTagContains)
    );

    count_ns.Bind(_SC("Checkpoint"), Table(vm)
        .Func(_SC("Active"), &Entity< CCheckpoint >::CountActive)
        .Func(_SC("TagEquals"), &Entity< CCheckpoint >::CountWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CCheckpoint >::CountWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CCheckpoint >::CountWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CCheckpoint >::CountWhereTagContains)
    );

    count_ns.Bind(_SC("Keybind"), Table(vm)
        .Func(_SC("Active"), &Entity< CKeybind >::CountActive)
        .Func(_SC("TagEquals"), &Entity< CKeybind >::CountWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CKeybind >::CountWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CKeybind >::CountWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CKeybind >::CountWhereTagContains)
    );

    count_ns.Bind(_SC("Object"), Table(vm)
        .Func(_SC("Active"), &Entity< CObject >::CountActive)
        .Func(_SC("TagEquals"), &Entity< CObject >::CountWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CObject >::CountWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CObject >::CountWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CObject >::CountWhereTagContains)
    );

    count_ns.Bind(_SC("Pickup"), Table(vm)
        .Func(_SC("Active"), &Entity< CPickup >::CountActive)
        .Func(_SC("TagEquals"), &Entity< CPickup >::CountWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CPickup >::CountWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CPickup >::CountWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CPickup >::CountWhereTagContains)
    );

    count_ns.Bind(_SC("Player"), Table(vm)
        .Func(_SC("Active"), &Entity< CPlayer >::CountActive)
        .Func(_SC("TagEquals"), &Entity< CPlayer >::CountWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CPlayer >::CountWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CPlayer >::CountWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CPlayer >::CountWhereTagContains)
        .Func(_SC("NameEquals"), &Player_CountWhereNameEquals)
        .Func(_SC("NameBegins"), &Player_CountWhereNameBegins)
        .Func(_SC("NameEnds"), &Player_CountWhereNameEnds)
        .Func(_SC("NameContains"), &Player_CountWhereNameContains)
    );

    count_ns.Bind(_SC("Vehicle"), Table(vm)
        .Func(_SC("Active"), &Entity< CVehicle >::CountActive)
        .Func(_SC("TagEquals"), &Entity< CVehicle >::CountWhereTagEquals)
        .Func(_SC("TagBegins"), &Entity< CVehicle >::CountWhereTagBegins)
        .Func(_SC("TagEnds"), &Entity< CVehicle >::CountWhereTagEnds)
        .Func(_SC("TagContains"), &Entity< CVehicle >::CountWhereTagContains)
    );

    RootTable(vm).Bind(_SC("SqCount"), count_ns);
}

} // Namespace:: Algo

// ================================================================================================
void Register_Algo(HSQUIRRELVM vm)
{
    Algo::Register(vm);
}

} // Namespace:: SqMod
