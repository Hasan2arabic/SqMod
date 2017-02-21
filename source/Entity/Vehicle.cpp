// ------------------------------------------------------------------------------------------------
#include "Entity/Vehicle.hpp"
#include "Entity/Player.hpp"
#include "Base/Quaternion.hpp"
#include "Base/Vector2.hpp"
#include "Base/Vector3.hpp"
#include "Core.hpp"
#include "Tasks.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
SQMODE_DECL_TYPENAME(Typename, _SC("SqVehicle"))

// ------------------------------------------------------------------------------------------------
Vector2      CVehicle::s_Vector2;
Vector3      CVehicle::s_Vector3;
Quaternion   CVehicle::s_Quaternion;

// ------------------------------------------------------------------------------------------------
const Int32 CVehicle::Max = SQMOD_VEHICLE_POOL;

// ------------------------------------------------------------------------------------------------
SQInteger CVehicle::SqGetNull(HSQUIRRELVM vm)
{
    sq_pushobject(vm, Core::Get().GetNullVehicle().GetObject());
    return 1;
}

// ------------------------------------------------------------------------------------------------
LightObj & CVehicle::GetNull()
{
    return Core::Get().GetNullVehicle();
}

// ------------------------------------------------------------------------------------------------
CVehicle::CVehicle(Int32 id)
    : m_ID(VALID_ENTITYGETEX(id, SQMOD_VEHICLE_POOL))
    , m_Tag(ToStrF("%d", id)), m_Data(), m_CircularLocks(0)
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
CVehicle::~CVehicle()
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
const String & CVehicle::ToString() const
{
    return m_Tag;
}

// ------------------------------------------------------------------------------------------------
const String & CVehicle::GetTag() const
{
    return m_Tag;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetTag(const StackStrF & tag)
{
    if (tag.mLen > 0)
    {
        m_Tag.assign(tag.mPtr, tag.mLen);
    }
    else
    {
        m_Tag.clear();
    }
}

// ------------------------------------------------------------------------------------------------
CVehicle & CVehicle::ApplyTag(const StackStrF & tag)
{
    SetTag(tag);
    return *this;
}

// ------------------------------------------------------------------------------------------------
LightObj & CVehicle::GetData()
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return m_Data;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetData(LightObj & data)
{
    // Validate the managed identifier
    Validate();
    // Apply the specified value
    m_Data = data;
}

// ------------------------------------------------------------------------------------------------
bool CVehicle::Destroy(Int32 header, LightObj & payload)
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    return Core::Get().DelVehicle(m_ID, header, payload);
}

// ------------------------------------------------------------------------------------------------
LightObj & CVehicle::GetEvents() const
{
    // Validate the managed identifier
    Validate();
    // Return the associated event table
    return Core::Get().GetVehicle(m_ID).mEvents;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::CustomEvent(Int32 header, LightObj & payload) const
{
    // Validate the managed identifier
    Validate();
    // Perfrom the requested action
    Core::Get().EmitVehicleCustom(m_ID, header, payload);
}

// ------------------------------------------------------------------------------------------------
bool CVehicle::IsStreamedFor(CPlayer & player) const
{
    // Is the specified player even valid?
    if (!player.IsActive())
    {
        STHROWF("Invalid player argument: null");
    }
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->IsVehicleStreamedForPlayer(m_ID, player.GetID());
}

// ------------------------------------------------------------------------------------------------
bool CVehicle::GetOption(Int32 option_id) const
{
    // Attempt to obtain the current value of the specified option
    const bool value = _Func->GetVehicleOption(m_ID, static_cast< vcmpVehicleOption >(option_id));
    // Check for errors
    if (_Func->GetLastError() == vcmpErrorArgumentOutOfBounds)
    {
        STHROWF("Invalid option identifier: %d", option_id);
    }
    // Return the requested value
    return value;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetOption(Int32 option_id, bool toggle)
{
    // Attempt to obtain the current value of the specified option
    const bool value = _Func->GetVehicleOption(m_ID, static_cast< vcmpVehicleOption >(option_id));
    // Attempt to modify the current value of the specified option
    if (_Func->SetVehicleOption(m_ID, static_cast< vcmpVehicleOption >(option_id),
                                toggle) == vcmpErrorArgumentOutOfBounds)
    {
        STHROWF("Invalid option identifier: %d", option_id);
    }
    else if (!(m_CircularLocks & VEHICLECL_EMIT_VEHICLE_OPTION))
    {
        // Prevent this event from triggering while executed
        BitGuardU32 bg(m_CircularLocks, VEHICLECL_EMIT_VEHICLE_OPTION);
        // Now forward the event call
        Core::Get().EmitVehicleOption(m_ID, option_id, value, 0, NullLightObj());
    }
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetOptionEx(Int32 option_id, bool toggle, Int32 header, LightObj & payload)
{
    // Attempt to obtain the current value of the specified option
    const bool value = _Func->GetVehicleOption(m_ID, static_cast< vcmpVehicleOption >(option_id));
    // Attempt to modify the current value of the specified option
    if (_Func->SetVehicleOption(m_ID, static_cast< vcmpVehicleOption >(option_id),
                                toggle) == vcmpErrorArgumentOutOfBounds)
    {
        STHROWF("Invalid option identifier: %d", option_id);
    }
    else if (!(m_CircularLocks & VEHICLECL_EMIT_VEHICLE_OPTION))
    {
        // Prevent this event from triggering while executed
        BitGuardU32 bg(m_CircularLocks, VEHICLECL_EMIT_VEHICLE_OPTION);
        // Now forward the event call
        Core::Get().EmitVehicleOption(m_ID, option_id, value, header, payload);
    }
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetSyncSource() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetVehicleSyncSource(m_ID);
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetSyncType() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetVehicleSyncType(m_ID);
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetWorld() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetVehicleWorld(m_ID);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetWorld(Int32 world)
{
    // Validate the managed identifier
    Validate();
    // Grab the current value for this property
    const Int32 current = _Func->GetVehicleWorld(m_ID);
    // Don't even bother if it's the same value
    if (current == world)
    {
        return;
    }
    // Avoid property unwind from a recursive call
    _Func->SetVehicleWorld(m_ID, world);
    // Avoid infinite recursive event loops
    if (!(m_CircularLocks & VEHICLECL_EMIT_VEHICLE_WORLD))
    {
        // Prevent this event from triggering while executed
        BitGuardU32 bg(m_CircularLocks, VEHICLECL_EMIT_VEHICLE_WORLD);
        // Now forward the event call
        Core::Get().EmitVehicleWorld(m_ID, current, world);
    }
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetModel() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetVehicleModel(m_ID);
}

// ------------------------------------------------------------------------------------------------
LightObj & CVehicle::GetOccupant(Int32 slot) const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return Core::Get().GetPlayer(_Func->GetVehicleOccupant(m_ID, slot)).mObj;
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetOccupantID(Int32 slot) const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetVehicleOccupant(m_ID, slot);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::Respawn() const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->RespawnVehicle(m_ID);
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetImmunity() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetVehicleImmunityFlags(m_ID);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetImmunity(Int32 flags)
{
    // Validate the managed identifier
    Validate();
    // Grab the current value for this property
    const Int32 current = _Func->GetVehicleImmunityFlags(m_ID);
    // Avoid property unwind from a recursive call
    _Func->SetVehicleImmunityFlags(m_ID, flags);
    // Avoid infinite recursive event loops
    if (!(m_CircularLocks & VEHICLECL_EMIT_VEHICLE_IMMUNITY))
    {
        // Prevent this event from triggering while executed
        BitGuardU32 bg(m_CircularLocks, VEHICLECL_EMIT_VEHICLE_IMMUNITY);
        // Now forward the event call
        Core::Get().EmitVehicleImmunity(m_ID, current, flags);
    }
}

// ------------------------------------------------------------------------------------------------
void CVehicle::Explode() const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->ExplodeVehicle(m_ID);
}

// ------------------------------------------------------------------------------------------------
bool CVehicle::IsWrecked() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->IsVehicleWrecked(m_ID);
}

// ------------------------------------------------------------------------------------------------
const Vector3 & CVehicle::GetPosition() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.Clear();
    // Query the server for the values
    _Func->GetVehiclePosition(m_ID, &s_Vector3.x, &s_Vector3.y, &s_Vector3.z);
    // Return the requested information
    return s_Vector3;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetPosition(const Vector3 & pos) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehiclePosition(m_ID, pos.x, pos.y, pos.z, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetPositionEx(const Vector3 & pos, bool empty) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehiclePosition(m_ID, pos.x, pos.y, pos.z, empty);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetPositionEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehiclePosition(m_ID, x, y, z, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetPositionEx(Float32 x, Float32 y, Float32 z, bool empty) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehiclePosition(m_ID, x, y, z, empty);
}

// ------------------------------------------------------------------------------------------------
const Quaternion & CVehicle::GetRotation() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Quaternion.Clear();
    // Query the server for the values
    _Func->GetVehicleRotation(m_ID, &s_Quaternion.x, &s_Quaternion.y, &s_Quaternion.z, &s_Quaternion.w);
    // Return the requested information
    return s_Quaternion;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRotation(const Quaternion & rot) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleRotation(m_ID, rot.x, rot.y, rot.z, rot.w);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRotationEx(Float32 x, Float32 y, Float32 z, Float32 w) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleRotation(m_ID, x, y, z, w);
}

// ------------------------------------------------------------------------------------------------
const Vector3 & CVehicle::GetRotationEuler() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.Clear();
    // Query the server for the values
    _Func->GetVehicleRotationEuler(m_ID, &s_Vector3.x, &s_Vector3.y, &s_Vector3.z);
    // Return the requested information
    return s_Vector3;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRotationEuler(const Vector3 & rot) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleRotationEuler(m_ID, rot.x, rot.y, rot.z);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRotationEulerEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleRotationEuler(m_ID, x, y, z);
}

// ------------------------------------------------------------------------------------------------
const Vector3 & CVehicle::GetSpeed() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.Clear();
    // Query the server for the values
    _Func->GetVehicleSpeed(m_ID, &s_Vector3.x, &s_Vector3.y, &s_Vector3.z, false);
    // Return the requested information
    return s_Vector3;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetSpeed(const Vector3 & vel) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, vel.x, vel.y, vel.z, false, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetSpeedEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, x, y, z, false, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::AddSpeed(const Vector3 & vel) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, vel.x, vel.y, vel.z, true, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::AddSpeedEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, x, y, z, true, false);
}

// ------------------------------------------------------------------------------------------------
const Vector3 & CVehicle::GetRelativeSpeed() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.Clear();
    // Query the server for the values
    _Func->GetVehicleSpeed(m_ID, &s_Vector3.x, &s_Vector3.y, &s_Vector3.z, true);
    // Return the requested information
    return s_Vector3;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRelativeSpeed(const Vector3 & vel) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, vel.x, vel.y, vel.z, false, true);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRelativeSpeedEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, x, y, z, false, true);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::AddRelativeSpeed(const Vector3 & vel) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, vel.x, vel.y, vel.z, true, true);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::AddRelativeSpeedEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, x, y, z, true, true);
}

// ------------------------------------------------------------------------------------------------
const Vector3 & CVehicle::GetTurnSpeed() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.Clear();
    // Query the server for the values
    _Func->GetVehicleTurnSpeed(m_ID, &s_Vector3.x, &s_Vector3.y, &s_Vector3.z, false);
    // Return the requested information
    return s_Vector3;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetTurnSpeed(const Vector3 & vel) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, vel.x, vel.y, vel.z, false, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetTurnSpeedEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, x, y, z, false, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::AddTurnSpeed(const Vector3 & vel) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, vel.x, vel.y, vel.z, true, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::AddTurnSpeedEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, x, y, z, true, false);
}

// ------------------------------------------------------------------------------------------------
const Vector3 & CVehicle::GetRelativeTurnSpeed() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.Clear();
    // Query the server for the values
    _Func->GetVehicleTurnSpeed(m_ID, &s_Vector3.x, &s_Vector3.y, &s_Vector3.z, true);
    // Return the requested information
    return s_Vector3;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRelativeTurnSpeed(const Vector3 & vel) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, vel.x, vel.y, vel.z, false, true);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRelativeTurnSpeedEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, x, y, z, false, true);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::AddRelativeTurnSpeed(const Vector3 & vel) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, vel.x, vel.y, vel.z, true, true);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::AddRelativeTurnSpeedEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, x, y, z, true, true);
}

// ------------------------------------------------------------------------------------------------
const Vector3 & CVehicle::GetSpawnPosition() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.Clear();
    // Query the server for the values
    _Func->GetVehicleSpawnPosition(m_ID, &s_Vector3.x, &s_Vector3.y, &s_Vector3.z);
    // Return the requested information
    return s_Vector3;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetSpawnPosition(const Vector3 & pos) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpawnPosition(m_ID, pos.x, pos.y, pos.z);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetSpawnPositionEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpawnPosition(m_ID, x, y, z);
}

// ------------------------------------------------------------------------------------------------
const Quaternion & CVehicle::GetSpawnRotation() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Quaternion.Clear();
    // Query the server for the values
    _Func->GetVehicleSpawnRotation(m_ID, &s_Quaternion.x, &s_Quaternion.y, &s_Quaternion.z, &s_Quaternion.w);
    // Return the requested information
    return s_Quaternion;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetSpawnRotation(const Quaternion & rot) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpawnRotation(m_ID, rot.x, rot.y, rot.z, rot.w);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetSpawnRotationEx(Float32 x, Float32 y, Float32 z, Float32 w) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpawnRotation(m_ID, x, y, z, w);
}

// ------------------------------------------------------------------------------------------------
const Vector3 & CVehicle::GetSpawnRotationEuler() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.Clear();
    // Query the server for the rotation values
    _Func->GetVehicleSpawnRotationEuler(m_ID, &s_Vector3.x, &s_Vector3.y, &s_Vector3.z);
    // Return the requested information
    return s_Vector3;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetSpawnRotationEuler(const Vector3 & rot) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpawnRotationEuler(m_ID, rot.x, rot.y, rot.z);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetSpawnRotationEulerEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleSpawnRotationEuler(m_ID, x, y, z);
}

// ------------------------------------------------------------------------------------------------
Uint32 CVehicle::GetIdleRespawnTimer() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetVehicleIdleRespawnTimer(m_ID);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetIdleRespawnTimer(Uint32 millis) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleIdleRespawnTimer(m_ID, millis);
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetHealth() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetVehicleHealth(m_ID);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetHealth(Float32 amount) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleHealth(m_ID, amount);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::Fix() const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleHealth(m_ID, 1000);
    _Func->SetVehicleDamageData(m_ID, 0);
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetPrimaryColor() const
{
    // Validate the managed identifier
    Validate();
    // The color value
    Int32 primary = -1;
    // Query the server for the requested color
    _Func->GetVehicleColour(m_ID, &primary, nullptr);
    // Return the requested information
    return primary;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetPrimaryColor(Int32 col) const
{
    // Validate the managed identifier
    Validate();
    // The unchanged color value
    Int32 secondary;
    // Query the server for the unchanged color
    _Func->GetVehicleColour(m_ID, nullptr, &secondary);
    // Perform the requested operation
    _Func->SetVehicleColour(m_ID, col, secondary);
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetSecondaryColor() const
{
    // Validate the managed identifier
    Validate();
    // The color value
    Int32 secondary = -1;
    // Query the server for the requested color
    _Func->GetVehicleColour(m_ID, nullptr, &secondary);
    // Return the requested information
    return secondary;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetSecondaryColor(Int32 col) const
{
    // Validate the managed identifier
    Validate();
    // The unchanged color value
    Int32 primary;
    // Query the server for the unchanged color
    _Func->GetVehicleColour(m_ID, &primary, nullptr);
    // Perform the requested operation
    _Func->SetVehicleColour(m_ID, primary, col);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetColors(Int32 primary, Int32 secondary) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetVehicleColour(m_ID, primary, secondary);
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetPartStatus(Int32 part) const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetVehiclePartStatus(m_ID, part);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetPartStatus(Int32 part, Int32 status)
{
    // Validate the managed identifier
    Validate();
    // Grab the current value for this property
    const Int32 current = _Func->GetVehiclePartStatus(m_ID, part);
    // Don't even bother if it's the same value
    if (current == status)
    {
        return;
    }
    // Avoid property unwind from a recursive call
    _Func->SetVehiclePartStatus(m_ID, part, status);
    // Avoid infinite recursive event loops
    if (!(m_CircularLocks & VEHICLECL_EMIT_VEHICLE_PARTSTATUS))
    {
        // Prevent this event from triggering while executed
        BitGuardU32 bg(m_CircularLocks, VEHICLECL_EMIT_VEHICLE_PARTSTATUS);
        // Now forward the event call
        Core::Get().EmitVehiclePartStatus(m_ID, part, current, status);
    }
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetTyreStatus(Int32 tyre) const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetVehicleTyreStatus(m_ID, tyre);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetTyreStatus(Int32 tyre, Int32 status)
{
    // Validate the managed identifier
    Validate();
    // Grab the current value for this property
    const Int32 current = _Func->GetVehicleTyreStatus(m_ID, tyre);
    // Don't even bother if it's the same value
    if (current == status)
    {
        return;
    }
    // Avoid property unwind from a recursive call
    _Func->SetVehicleTyreStatus(m_ID, tyre, status);
    // Avoid infinite recursive event loops
    if (!(m_CircularLocks & VEHICLECL_EMIT_VEHICLE_TYRESTATUS))
    {
        // Prevent this event from triggering while executed
        BitGuardU32 bg(m_CircularLocks, VEHICLECL_EMIT_VEHICLE_TYRESTATUS);
        // Now forward the event call
        Core::Get().EmitVehicleTyreStatus(m_ID, tyre, current, status);
    }
}

// ------------------------------------------------------------------------------------------------
Uint32 CVehicle::GetDamageData() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetVehicleDamageData(m_ID);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetDamageData(Uint32 data)
{
    // Validate the managed identifier
    Validate();
    // Grab the current value for this property
    const Uint32 current = _Func->GetVehicleDamageData(m_ID);
    // Don't even bother if it's the same value
    if (current == data)
    {
        return;
    }
    // Avoid property unwind from a recursive call
    _Func->SetVehicleDamageData(m_ID, data);
    // Avoid infinite recursive event loops
    if (!(m_CircularLocks & VEHICLECL_EMIT_VEHICLE_DAMAGEDATA))
    {
        // Prevent this event from triggering while executed
        BitGuardU32 bg(m_CircularLocks, VEHICLECL_EMIT_VEHICLE_DAMAGEDATA);
        // Now forward the event call
        Core::Get().EmitVehicleDamageData(m_ID, current, data);
    }
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetRadio() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetVehicleRadio(m_ID);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRadio(Int32 radio)
{
    // Validate the managed identifier
    Validate();
    // Grab the current value for this property
    const Int32 current = _Func->GetVehicleRadio(m_ID);
    // Don't even bother if it's the same value
    if (current == radio)
    {
        return;
    }
    // Avoid property unwind from a recursive call
    _Func->SetVehicleRadio(m_ID, radio);
    // Avoid infinite recursive event loops
    if (!(m_CircularLocks & VEHICLECL_EMIT_VEHICLE_RADIO))
    {
        // Prevent this event from triggering while executed
        BitGuardU32 bg(m_CircularLocks, VEHICLECL_EMIT_VEHICLE_RADIO);
        // Now forward the event call
        Core::Get().EmitVehicleRadio(m_ID, current, radio);
    }
}

// ------------------------------------------------------------------------------------------------
const Vector2 & CVehicle::GetTurretRotation() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector2.Clear();
    // Query the server for the values
    _Func->GetVehicleTurretRotation(m_ID, &s_Vector2.x, &s_Vector2.y);
    // Return the requested information
    return s_Vector2;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetHorizontalTurretRotation() const
{
    // Validate the managed identifier
    Validate();
    // Where the rotation value is retrieved
    Float32 rot = 0.0f;
    // Query the server for the turret rotation value
    _Func->GetVehicleTurretRotation(m_ID, &rot, nullptr);
    // Return the requested information
    return rot;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetVerticalTurretRotation() const
{
    // Validate the managed identifier
    Validate();
    // Where the rotation value is retrieved
    Float32 rot = 0.0f;
    // Query the server for the turret rotation value
    _Func->GetVehicleTurretRotation(m_ID, nullptr, &rot);
    // Return the requested information
    return rot;
}

// ------------------------------------------------------------------------------------------------
bool CVehicle::ExistsHandlingRule(Int32 rule) const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->ExistsInstHandlingRule(m_ID, rule);
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetHandlingRule(Int32 rule) const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetInstHandlingRule(m_ID, rule);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetHandlingRule(Int32 rule, Float32 data)
{
    // Validate the managed identifier
    Validate();
    // Grab the current value for this property
    const Float32 current = _Func->GetInstHandlingRule(m_ID, rule);
    // Avoid property unwind from a recursive call
    _Func->SetInstHandlingRule(m_ID, rule, data);
    // Avoid infinite recursive event loops
    if (!(m_CircularLocks & VEHICLECL_EMIT_VEHICLE_HANDLINGRULE))
    {
        // Prevent this event from triggering while executed
        BitGuardU32 bg(m_CircularLocks, VEHICLECL_EMIT_VEHICLE_HANDLINGRULE);
        // Now forward the event call
        Core::Get().EmitVehicleHandlingRule(m_ID, rule, current, data);
    }
}

// ------------------------------------------------------------------------------------------------
void CVehicle::ResetHandlingRule(Int32 rule)
{
    // Validate the managed identifier
    Validate();
    // Grab the current value for this property
    const Float32 current = _Func->GetInstHandlingRule(m_ID, rule);
    // Avoid property unwind from a recursive call
    _Func->ResetInstHandlingRule(m_ID, rule);
    // Avoid infinite recursive event loops
    if (!(m_CircularLocks & VEHICLECL_EMIT_VEHICLE_HANDLINGRULE))
    {
        // Prevent this event from triggering while executed
        BitGuardU32 bg(m_CircularLocks, VEHICLECL_EMIT_VEHICLE_HANDLINGRULE);
        // Now forward the event call
        Core::Get().EmitVehicleHandlingRule(m_ID, rule, current, _Func->GetInstHandlingRule(m_ID, rule));
    }
}

// ------------------------------------------------------------------------------------------------
void CVehicle::ResetHandlings() const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->ResetInstHandling(m_ID);
}

// ------------------------------------------------------------------------------------------------
bool CVehicle::Embark(CPlayer & player) const
{
    // Is the specified player even valid?
    if (!player.IsActive())
    {
        STHROWF("Invalid player argument: null");
    }
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    return (_Func->PutPlayerInVehicle(player.GetID(), m_ID, 0, true, true)
            != vcmpErrorRequestDenied);
}

// ------------------------------------------------------------------------------------------------
bool CVehicle::Embark(CPlayer & player, Int32 slot, bool allocate, bool warp) const
{
    // Is the specified player even valid?
    if (!player.IsActive())
    {
        STHROWF("Invalid player argument: null");
    }
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    return (_Func->PutPlayerInVehicle(player.GetID(), m_ID, slot, allocate, warp)
            != vcmpErrorRequestDenied);
}

// ------------------------------------------------------------------------------------------------
SQInteger CVehicle::GetTrackPosition() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return Core::Get().GetVehicle(m_ID).mTrackPosition;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetTrackPosition(SQInteger num) const
{
    // Validate the managed identifier
    Validate();
    // Assign the requested information
    Core::Get().GetVehicle(m_ID).mTrackPosition = num;
}

// ------------------------------------------------------------------------------------------------
SQInteger CVehicle::GetTrackRotation() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return Core::Get().GetVehicle(m_ID).mTrackRotation;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetTrackRotation(SQInteger num) const
{
    // Validate the managed identifier
    Validate();
    // Assign the requested information
    Core::Get().GetVehicle(m_ID).mTrackRotation = num;
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetLastPrimaryColor() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return Core::Get().GetVehicle(m_ID).mLastPrimaryColor;
}

// ------------------------------------------------------------------------------------------------
Int32 CVehicle::GetLastSecondaryColor() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return Core::Get().GetVehicle(m_ID).mLastSecondaryColor;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetLastHealth() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return Core::Get().GetVehicle(m_ID).mLastHealth;
}

// ------------------------------------------------------------------------------------------------
const Vector3 & CVehicle::GetLastPosition() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return Core::Get().GetVehicle(m_ID).mLastPosition;
}

// ------------------------------------------------------------------------------------------------
const Quaternion & CVehicle::GetLastRotation() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return Core::Get().GetVehicle(m_ID).mLastRotation;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetPositionX() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.x = 0;
    // Query the server for the requested component value
    _Func->GetVehiclePosition(m_ID, &s_Vector3.x, nullptr, nullptr);
    // Return the requested information
    return s_Vector3.x;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetPositionY() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.y = 0;
    // Query the server for the requested component value
    _Func->GetVehiclePosition(m_ID, nullptr, &s_Vector3.y, nullptr);
    // Return the requested information
    return s_Vector3.y;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetPositionZ() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.z = 0;
    // Query the server for the requested component value
    _Func->GetVehiclePosition(m_ID, nullptr, nullptr, &s_Vector3.z);
    // Return the requested information
    return s_Vector3.z;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetPositionX(Float32 x) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehiclePosition(m_ID, nullptr, &s_Vector3.y, &s_Vector3.z);
    // Perform the requested operation
    _Func->SetVehiclePosition(m_ID, x, s_Vector3.y, s_Vector3.z, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetPositionY(Float32 y) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehiclePosition(m_ID, &s_Vector3.x, nullptr, &s_Vector3.z);
    // Perform the requested operation
    _Func->SetVehiclePosition(m_ID, s_Vector3.x, y, s_Vector3.z, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetPositionZ(Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehiclePosition(m_ID, &s_Vector3.x, &s_Vector3.y, nullptr);
    // Perform the requested operation
    _Func->SetVehiclePosition(m_ID, s_Vector3.z, s_Vector3.y, z, false);
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetRotationX() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Quaternion.x = 0;
    // Query the server for the requested component value
    _Func->GetVehicleRotation(m_ID, &s_Quaternion.x, nullptr, nullptr, nullptr);
    // Return the requested information
    return s_Quaternion.x;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetRotationY() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Quaternion.y = 0;
    // Query the server for the requested component value
    _Func->GetVehicleRotation(m_ID, nullptr, &s_Quaternion.y, nullptr, nullptr);
    // Return the requested information
    return s_Quaternion.y;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetRotationZ() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Quaternion.z = 0;
    // Query the server for the requested component value
    _Func->GetVehicleRotation(m_ID, nullptr, nullptr, &s_Quaternion.z, nullptr);
    // Return the requested information
    return s_Quaternion.z;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetRotationW() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Quaternion.w = 0;
    // Query the server for the requested component value
    _Func->GetVehicleRotation(m_ID, nullptr, nullptr, nullptr, &s_Quaternion.w);
    // Return the requested information
    return s_Quaternion.w;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRotationX(Float32 x) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleRotation(m_ID, nullptr, &s_Quaternion.y, &s_Quaternion.z, &s_Quaternion.w);
    // Perform the requested operation
    _Func->SetVehicleRotation(m_ID, x, s_Quaternion.y, s_Quaternion.z, s_Quaternion.w);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRotationY(Float32 y) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleRotation(m_ID, &s_Quaternion.x, nullptr, &s_Quaternion.z, &s_Quaternion.w);
    // Perform the requested operation
    _Func->SetVehicleRotation(m_ID, s_Quaternion.x, y, s_Quaternion.z, s_Quaternion.w);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRotationZ(Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleRotation(m_ID, &s_Quaternion.x, &s_Quaternion.y, nullptr, &s_Quaternion.w);
    // Perform the requested operation
    _Func->SetVehicleRotation(m_ID, s_Quaternion.x, s_Quaternion.y, z, s_Quaternion.w);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRotationW(Float32 w) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleRotation(m_ID, &s_Quaternion.x, &s_Quaternion.y, &s_Quaternion.z, nullptr);
    // Perform the requested operation
    _Func->SetVehicleRotation(m_ID, s_Quaternion.x, s_Quaternion.y, s_Quaternion.z, w);
}


// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetEulerRotationX() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.x = 0;
    // Query the server for the requested component value
    _Func->GetVehicleRotationEuler(m_ID, &s_Vector3.x, nullptr, nullptr);
    // Return the requested information
    return s_Vector3.x;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetEulerRotationY() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.y = 0;
    // Query the server for the requested component value
    _Func->GetVehicleRotationEuler(m_ID, nullptr, &s_Vector3.y, nullptr);
    // Return the requested information
    return s_Vector3.y;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetEulerRotationZ() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.z = 0;
    // Query the server for the requested component value
    _Func->GetVehicleRotationEuler(m_ID, nullptr, nullptr, &s_Vector3.z);
    // Return the requested information
    return s_Vector3.z;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetEulerRotationX(Float32 x) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleRotationEuler(m_ID, nullptr, &s_Vector3.y, &s_Vector3.z);
    // Perform the requested operation
    _Func->SetVehicleRotationEuler(m_ID, x, s_Vector3.y, s_Vector3.z);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetEulerRotationY(Float32 y) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleRotationEuler(m_ID, &s_Vector3.x, nullptr, &s_Vector3.z);
    // Perform the requested operation
    _Func->SetVehicleRotationEuler(m_ID, s_Vector3.x, y, s_Vector3.z);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetEulerRotationZ(Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleRotationEuler(m_ID, &s_Vector3.x, &s_Vector3.y, nullptr);
    // Perform the requested operation
    _Func->SetVehicleRotationEuler(m_ID, s_Vector3.z, s_Vector3.y, z);
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetSpeedX() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.x = 0.0f;
    // Query the server for the requested component value
    _Func->GetVehicleSpeed(m_ID, &s_Vector3.x, nullptr, nullptr, false);
    // Return the requested information
    return s_Vector3.x;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetSpeedY() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.y = 0.0f;
    // Query the server for the requested component value
    _Func->GetVehicleSpeed(m_ID, nullptr, &s_Vector3.y, nullptr, false);
    // Return the requested information
    return s_Vector3.y;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetSpeedZ() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.z = 0.0f;
    // Query the server for the requested component value
    _Func->GetVehicleSpeed(m_ID, nullptr, nullptr, &s_Vector3.z, false);
    // Return the requested information
    return s_Vector3.z;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetSpeedX(Float32 x) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleSpeed(m_ID, nullptr, &s_Vector3.y, &s_Vector3.z, false);
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, x, s_Vector3.y, s_Vector3.z, false, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetSpeedY(Float32 y) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleSpeed(m_ID, &s_Vector3.x, nullptr, &s_Vector3.z, false);
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, s_Vector3.x, y, s_Vector3.z, false, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetSpeedZ(Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleSpeed(m_ID, &s_Vector3.x, &s_Vector3.y, nullptr, false);
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, s_Vector3.z, s_Vector3.y, z, false, false);
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetRelativeSpeedX() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.x = 0.0f;
    // Query the server for the requested component value
    _Func->GetVehicleSpeed(m_ID, &s_Vector3.x, nullptr, nullptr, true);
    // Return the requested information
    return s_Vector3.x;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetRelativeSpeedY() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.y = 0.0f;
    // Query the server for the requested component value
    _Func->GetVehicleSpeed(m_ID, nullptr, &s_Vector3.y, nullptr, true);
    // Return the requested information
    return s_Vector3.y;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetRelativeSpeedZ() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.z = 0.0f;
    // Query the server for the requested component value
    _Func->GetVehicleSpeed(m_ID, nullptr, nullptr, &s_Vector3.z, true);
    // Return the requested information
    return s_Vector3.z;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRelativeSpeedX(Float32 x) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleSpeed(m_ID, nullptr, &s_Vector3.y, &s_Vector3.z, true);
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, x, s_Vector3.y, s_Vector3.z, false, true);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRelativeSpeedY(Float32 y) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleSpeed(m_ID, &s_Vector3.x, nullptr, &s_Vector3.z, true);
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, s_Vector3.x, y, s_Vector3.z, false, true);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRelativeSpeedZ(Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleSpeed(m_ID, &s_Vector3.x, &s_Vector3.y, nullptr, true);
    // Perform the requested operation
    _Func->SetVehicleSpeed(m_ID, s_Vector3.z, s_Vector3.y, z, false, true);
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetTurnSpeedX() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.x = 0.0f;
    // Query the server for the requested component value
    _Func->GetVehicleTurnSpeed(m_ID, &s_Vector3.x, nullptr, nullptr, false);
    // Return the requested information
    return s_Vector3.x;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetTurnSpeedY() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.y = 0.0f;
    // Query the server for the requested component value
    _Func->GetVehicleTurnSpeed(m_ID, nullptr, &s_Vector3.y, nullptr, false);
    // Return the requested information
    return s_Vector3.y;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetTurnSpeedZ() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.z = 0.0f;
    // Query the server for the requested component value
    _Func->GetVehicleTurnSpeed(m_ID, nullptr, nullptr, &s_Vector3.z, false);
    // Return the requested information
    return s_Vector3.z;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetTurnSpeedX(Float32 x) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleTurnSpeed(m_ID, nullptr, &s_Vector3.y, &s_Vector3.z, false);
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, x, s_Vector3.y, s_Vector3.z, false, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetTurnSpeedY(Float32 y) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleTurnSpeed(m_ID, &s_Vector3.x, nullptr, &s_Vector3.z, false);
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, s_Vector3.x, y, s_Vector3.z, false, false);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetTurnSpeedZ(Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleTurnSpeed(m_ID, &s_Vector3.x, &s_Vector3.y, nullptr, false);
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, s_Vector3.z, s_Vector3.y, z, false, false);
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetRelativeTurnSpeedX() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.x = 0.0f;
    // Query the server for the requested component value
    _Func->GetVehicleTurnSpeed(m_ID, &s_Vector3.x, nullptr, nullptr, true);
    // Return the requested information
    return s_Vector3.x;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetRelativeTurnSpeedY() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.y = 0.0f;
    // Query the server for the requested component value
    _Func->GetVehicleTurnSpeed(m_ID, nullptr, &s_Vector3.y, nullptr, true);
    // Return the requested information
    return s_Vector3.y;
}

// ------------------------------------------------------------------------------------------------
Float32 CVehicle::GetRelativeTurnSpeedZ() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous information, if any
    s_Vector3.z = 0.0f;
    // Query the server for the requested component value
    _Func->GetVehicleTurnSpeed(m_ID, nullptr, nullptr, &s_Vector3.z, true);
    // Return the requested information
    return s_Vector3.z;
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRelativeTurnSpeedX(Float32 x) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleTurnSpeed(m_ID, nullptr, &s_Vector3.y, &s_Vector3.z, true);
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, x, s_Vector3.y, s_Vector3.z, false, true);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRelativeTurnSpeedY(Float32 y) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleTurnSpeed(m_ID, &s_Vector3.x, nullptr, &s_Vector3.z, true);
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, s_Vector3.x, y, s_Vector3.z, false, true);
}

// ------------------------------------------------------------------------------------------------
void CVehicle::SetRelativeTurnSpeedZ(Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetVehicleTurnSpeed(m_ID, &s_Vector3.x, &s_Vector3.y, nullptr, true);
    // Perform the requested operation
    _Func->SetVehicleTurnSpeed(m_ID, s_Vector3.z, s_Vector3.y, z, false, true);
}

// ------------------------------------------------------------------------------------------------
static LightObj & Vehicle_CreateEx(Int32 model, Int32 world, Float32 x, Float32 y, Float32 z, Float32 angle,
                            Int32 primary, Int32 secondary)
{
    return Core::Get().NewVehicle(model, world, x, y, z, angle, primary, secondary,
                            SQMOD_CREATE_DEFAULT, NullLightObj());
}

static LightObj & Vehicle_CreateEx(Int32 model, Int32 world, Float32 x, Float32 y, Float32 z, Float32 angle,
                            Int32 primary, Int32 secondary, Int32 header, LightObj & payload)
{
    return Core::Get().NewVehicle(model, world, x, y, z, angle, primary, secondary,
                            header, payload);
}

// ------------------------------------------------------------------------------------------------
static LightObj & Vehicle_Create(Int32 model, Int32 world, const Vector3 & pos, Float32 angle,
                        Int32 primary, Int32 secondary)
{
    return Core::Get().NewVehicle(model, world, pos.x, pos.y, pos.z, angle, primary, secondary,
                            SQMOD_CREATE_DEFAULT, NullLightObj());
}

static LightObj & Vehicle_Create(Int32 model, Int32 world, const Vector3 & pos, Float32 angle,
                        Int32 primary, Int32 secondary, Int32 header, LightObj & payload)
{
    return Core::Get().NewVehicle(model, world, pos.x, pos.y, pos.z, angle, primary, secondary,
                            header, payload);
}

// ================================================================================================
void Register_CVehicle(HSQUIRRELVM vm)
{
    RootTable(vm).Bind(Typename::Str,
        Class< CVehicle, NoConstructor< CVehicle > >(vm, Typename::Str)
        // Meta-methods
        .SquirrelFunc(_SC("_typename"), &Typename::Fn)
        .Func(_SC("_tostring"), &CVehicle::ToString)
        // Static Values
        .SetStaticValue(_SC("MaxID"), CVehicle::Max)
        // Core Properties
        .Prop(_SC("On"), &CVehicle::GetEvents)
        .Prop(_SC("ID"), &CVehicle::GetID)
        .Prop(_SC("Tag"), &CVehicle::GetTag, &CVehicle::SetTag)
        .Prop(_SC("Data"), &CVehicle::GetData, &CVehicle::SetData)
        .Prop(_SC("Active"), &CVehicle::IsActive)
        // Core Methods
        .FmtFunc(_SC("SetTag"), &CVehicle::ApplyTag)
        .Func(_SC("CustomEvent"), &CVehicle::CustomEvent)
        // Core Overloads
        .Overload< bool (CVehicle::*)(void) >(_SC("Destroy"), &CVehicle::Destroy)
        .Overload< bool (CVehicle::*)(Int32) >(_SC("Destroy"), &CVehicle::Destroy)
        .Overload< bool (CVehicle::*)(Int32, LightObj &) >(_SC("Destroy"), &CVehicle::Destroy)
        // Properties
        .Prop(_SC("SyncSource"), &CVehicle::GetSyncSource)
        .Prop(_SC("SyncType"), &CVehicle::GetSyncType)
        .Prop(_SC("World"), &CVehicle::GetWorld, &CVehicle::SetWorld)
        .Prop(_SC("Model"), &CVehicle::GetModel)
        .Prop(_SC("Immunity"), &CVehicle::GetImmunity, &CVehicle::SetImmunity)
        .Prop(_SC("Wrecked"), &CVehicle::IsWrecked)
        .Prop(_SC("Pos"), &CVehicle::GetPosition, &CVehicle::SetPosition)
        .Prop(_SC("Position"), &CVehicle::GetPosition, &CVehicle::SetPosition)
        .Prop(_SC("Rot"), &CVehicle::GetRotation, &CVehicle::SetRotation)
        .Prop(_SC("Rotation"), &CVehicle::GetRotation, &CVehicle::SetRotation)
        .Prop(_SC("EulerRot"), &CVehicle::GetRotationEuler, &CVehicle::SetRotationEuler)
        .Prop(_SC("EulerRotation"), &CVehicle::GetRotationEuler, &CVehicle::SetRotationEuler)
        .Prop(_SC("Speed"), &CVehicle::GetSpeed, &CVehicle::SetSpeed)
        .Prop(_SC("RelSpeed"), &CVehicle::GetRelativeSpeed, &CVehicle::SetRelativeSpeed)
        .Prop(_SC("RelativeSpeed"), &CVehicle::GetRelativeSpeed, &CVehicle::SetRelativeSpeed)
        .Prop(_SC("TurnSpeed"), &CVehicle::GetTurnSpeed, &CVehicle::SetTurnSpeed)
        .Prop(_SC("RelTurnSpeed"), &CVehicle::GetRelativeTurnSpeed, &CVehicle::SetRelativeTurnSpeed)
        .Prop(_SC("RelativeTurnSpeed"), &CVehicle::GetRelativeTurnSpeed, &CVehicle::SetRelativeTurnSpeed)
        .Prop(_SC("SpawnPos"), &CVehicle::GetSpawnPosition, &CVehicle::SetSpawnPosition)
        .Prop(_SC("SpawnPosition"), &CVehicle::GetSpawnPosition, &CVehicle::SetSpawnPosition)
        .Prop(_SC("SpawnRot"), &CVehicle::GetSpawnRotation, &CVehicle::SetSpawnRotation)
        .Prop(_SC("SpawnRotation"), &CVehicle::GetSpawnRotation, &CVehicle::SetSpawnRotation)
        .Prop(_SC("SpawnEulerRot"), &CVehicle::GetSpawnRotationEuler, &CVehicle::SetSpawnRotationEuler)
        .Prop(_SC("SpawnEulerRotation"), &CVehicle::GetSpawnRotationEuler, &CVehicle::SetSpawnRotationEuler)
        .Prop(_SC("IdleRespawnTimer"), &CVehicle::GetIdleRespawnTimer, &CVehicle::SetIdleRespawnTimer)
        .Prop(_SC("Health"), &CVehicle::GetHealth, &CVehicle::SetHealth)
        .Prop(_SC("PrimaryColor"), &CVehicle::GetPrimaryColor, &CVehicle::SetPrimaryColor)
        .Prop(_SC("SecondaryColor"), &CVehicle::GetSecondaryColor, &CVehicle::SetSecondaryColor)
        .Prop(_SC("PrimaryColour"), &CVehicle::GetPrimaryColor, &CVehicle::SetPrimaryColor)
        .Prop(_SC("SecondaryColour"), &CVehicle::GetSecondaryColor, &CVehicle::SetSecondaryColor)
        .Prop(_SC("DamageData"), &CVehicle::GetDamageData, &CVehicle::SetDamageData)
        .Prop(_SC("Radio"), &CVehicle::GetRadio, &CVehicle::SetRadio)
        .Prop(_SC("TurretRotation"), &CVehicle::GetTurretRotation)
        .Prop(_SC("HorTurretRotation"), &CVehicle::GetHorizontalTurretRotation)
        .Prop(_SC("HorizontalTurretRotation"), &CVehicle::GetHorizontalTurretRotation)
        .Prop(_SC("VerTurretRotation"), &CVehicle::GetVerticalTurretRotation)
        .Prop(_SC("VerticalTurretRotation"), &CVehicle::GetVerticalTurretRotation)
        .Prop(_SC("TrackPosition"), &CVehicle::GetTrackPosition, &CVehicle::SetTrackPosition)
        .Prop(_SC("TrackRotation"), &CVehicle::GetTrackRotation, &CVehicle::SetTrackRotation)
        .Prop(_SC("LastPrimaryColor"), &CVehicle::GetLastPrimaryColor)
        .Prop(_SC("LastSecondaryColor"), &CVehicle::GetLastSecondaryColor)
        .Prop(_SC("LastPrimaryColour"), &CVehicle::GetLastPrimaryColor)
        .Prop(_SC("LastSecondaryColour"), &CVehicle::GetLastSecondaryColor)
        .Prop(_SC("LastHealth"), &CVehicle::GetLastHealth)
        .Prop(_SC("LastPosition"), &CVehicle::GetLastPosition)
        .Prop(_SC("LastRotation"), &CVehicle::GetLastRotation)
        .Prop(_SC("PosX"), &CVehicle::GetPositionX, &CVehicle::SetPositionX)
        .Prop(_SC("PosY"), &CVehicle::GetPositionY, &CVehicle::SetPositionY)
        .Prop(_SC("PosZ"), &CVehicle::GetPositionZ, &CVehicle::SetPositionZ)
        .Prop(_SC("RotX"), &CVehicle::GetRotationX, &CVehicle::SetRotationX)
        .Prop(_SC("RotY"), &CVehicle::GetRotationY, &CVehicle::SetRotationY)
        .Prop(_SC("RotZ"), &CVehicle::GetRotationZ, &CVehicle::SetRotationZ)
        .Prop(_SC("RotW"), &CVehicle::GetRotationW, &CVehicle::SetRotationW)
        .Prop(_SC("EulerX"), &CVehicle::GetEulerRotationX, &CVehicle::SetEulerRotationX)
        .Prop(_SC("EulerY"), &CVehicle::GetEulerRotationY, &CVehicle::SetEulerRotationY)
        .Prop(_SC("EulerZ"), &CVehicle::GetEulerRotationZ, &CVehicle::SetEulerRotationZ)
        .Prop(_SC("SpeedX"), &CVehicle::GetSpeedX, &CVehicle::SetSpeedX)
        .Prop(_SC("SpeedY"), &CVehicle::GetSpeedY, &CVehicle::SetSpeedY)
        .Prop(_SC("SpeedZ"), &CVehicle::GetSpeedZ, &CVehicle::SetSpeedZ)
        .Prop(_SC("RelSpeedX"), &CVehicle::GetRelativeSpeedX, &CVehicle::SetRelativeSpeedX)
        .Prop(_SC("RelSpeedY"), &CVehicle::GetRelativeSpeedY, &CVehicle::SetRelativeSpeedY)
        .Prop(_SC("RelSpeedZ"), &CVehicle::GetRelativeSpeedZ, &CVehicle::SetRelativeSpeedZ)
        .Prop(_SC("TurnSpeedX"), &CVehicle::GetTurnSpeedX, &CVehicle::SetTurnSpeedX)
        .Prop(_SC("TurnSpeedY"), &CVehicle::GetTurnSpeedY, &CVehicle::SetTurnSpeedY)
        .Prop(_SC("TurnSpeedZ"), &CVehicle::GetTurnSpeedZ, &CVehicle::SetTurnSpeedZ)
        .Prop(_SC("RelTurnSpeedX"), &CVehicle::GetRelativeTurnSpeedX, &CVehicle::SetRelativeTurnSpeedX)
        .Prop(_SC("RelTurnSpeedY"), &CVehicle::GetRelativeTurnSpeedY, &CVehicle::SetRelativeTurnSpeedY)
        .Prop(_SC("RelTurnSpeedZ"), &CVehicle::GetRelativeTurnSpeedZ, &CVehicle::SetRelativeTurnSpeedZ)
        // Member Methods
        .Func(_SC("StreamedFor"), &CVehicle::IsStreamedFor)
        .Func(_SC("GetOption"), &CVehicle::GetOption)
        .Func(_SC("SetOption"), &CVehicle::SetOption)
        .Func(_SC("SetOptionEx"), &CVehicle::SetOptionEx)
        .Func(_SC("Occupant"), &CVehicle::GetOccupant)
        .Func(_SC("OccupantID"), &CVehicle::GetOccupantID)
        .Func(_SC("Respawn"), &CVehicle::Respawn)
        .Func(_SC("Explode"), &CVehicle::Explode)
        .Func(_SC("SetRot"), &CVehicle::SetRotationEx)
        .Func(_SC("SetRotation"), &CVehicle::SetRotationEx)
        .Func(_SC("SetEulerRot"), &CVehicle::SetRotationEulerEx)
        .Func(_SC("SetEulerRotation"), &CVehicle::SetRotationEulerEx)
        .Func(_SC("SetSpeed"), &CVehicle::SetSpeedEx)
        .Func(_SC("SetRelativeSpeed"), &CVehicle::SetRelativeSpeedEx)
        .Func(_SC("SetTurnSpeed"), &CVehicle::SetTurnSpeedEx)
        .Func(_SC("SetRelativeTurnSpeed"), &CVehicle::SetRelativeTurnSpeedEx)
        .Func(_SC("SetSpawnPos"), &CVehicle::SetSpawnPositionEx)
        .Func(_SC("SetSpawnPosition"), &CVehicle::SetSpawnPositionEx)
        .Func(_SC("SetSpawnRot"), &CVehicle::SetSpawnRotationEx)
        .Func(_SC("SetSpawnRotation"), &CVehicle::SetSpawnRotationEx)
        .Func(_SC("SetSpawnEulerRot"), &CVehicle::SetSpawnRotationEulerEx)
        .Func(_SC("SetSpawnEulerRotation"), &CVehicle::SetSpawnRotationEulerEx)
        .Func(_SC("Fix"), &CVehicle::Fix)
        .Func(_SC("SetColors"), &CVehicle::SetColors)
        .Func(_SC("GetPartStatus"), &CVehicle::GetPartStatus)
        .Func(_SC("SetPartStatus"), &CVehicle::SetPartStatus)
        .Func(_SC("GetTyreStatus"), &CVehicle::GetTyreStatus)
        .Func(_SC("SetTyreStatus"), &CVehicle::SetTyreStatus)
        .Func(_SC("ExistsHandlingRule"), &CVehicle::ExistsHandlingRule)
        .Func(_SC("GetHandlingRule"), &CVehicle::GetHandlingRule)
        .Func(_SC("SetHandlingRule"), &CVehicle::SetHandlingRule)
        .Func(_SC("ResetHandlingRule"), &CVehicle::ResetHandlingRule)
        .Func(_SC("ResetHandlings"), &CVehicle::ResetHandlings)
        // Member Overloads
        .Overload< void (CVehicle::*)(const Vector3 &, bool) const >
            (_SC("SetPos"), &CVehicle::SetPositionEx)
        .Overload< void (CVehicle::*)(Float32, Float32, Float32) const >
            (_SC("SetPos"), &CVehicle::SetPositionEx)
        .Overload< void (CVehicle::*)(Float32, Float32, Float32, bool) const >
            (_SC("SetPos"), &CVehicle::SetPositionEx)
        .Overload< void (CVehicle::*)(const Vector3 &, bool) const >
            (_SC("SetPosition"), &CVehicle::SetPositionEx)
        .Overload< void (CVehicle::*)(Float32, Float32, Float32) const >
            (_SC("SetPosition"), &CVehicle::SetPositionEx)
        .Overload< void (CVehicle::*)(Float32, Float32, Float32, bool) const >
            (_SC("SetPosition"), &CVehicle::SetPositionEx)
        .Overload< void (CVehicle::*)(const Vector3 &) const >
            (_SC("AddSpeed"), &CVehicle::AddSpeed)
        .Overload< void (CVehicle::*)(Float32, Float32, Float32) const >
            (_SC("AddSpeed"), &CVehicle::AddSpeedEx)
        .Overload< void (CVehicle::*)(const Vector3 &) const >
            (_SC("AddRelativeSpeed"), &CVehicle::AddRelativeSpeed)
        .Overload< void (CVehicle::*)(Float32, Float32, Float32) const >
            (_SC("AddRelativeSpeed"), &CVehicle::AddRelativeSpeedEx)
        .Overload< void (CVehicle::*)(const Vector3 &) const >
            (_SC("AddTurnSpeed"), &CVehicle::AddTurnSpeed)
        .Overload< void (CVehicle::*)(Float32, Float32, Float32) const >
            (_SC("AddTurnSpeed"), &CVehicle::AddTurnSpeedEx)
        .Overload< void (CVehicle::*)(const Vector3 &) const >
            (_SC("AddRelativeTurnSpeed"), &CVehicle::AddRelativeTurnSpeed)
        .Overload< void (CVehicle::*)(Float32, Float32, Float32) const >
            (_SC("AddRelativeTurnSpeed"), &CVehicle::AddRelativeTurnSpeedEx)
        .Overload< void (CVehicle::*)(void) const >
            (_SC("ResetHandling"), &CVehicle::ResetHandlings)
        .Overload< void (CVehicle::*)(Int32) >
            (_SC("ResetHandling"), &CVehicle::ResetHandlingRule)
        .Overload< bool (CVehicle::*)(CPlayer &) const >
            (_SC("Embark"), &CVehicle::Embark)
        .Overload< bool (CVehicle::*)(CPlayer &, Int32, bool, bool) const >
            (_SC("Embark"), &CVehicle::Embark)
        // Static Overloads
        .StaticOverload< LightObj & (*)(Int32, Int32, Float32, Float32, Float32, Float32, Int32, Int32) >
            (_SC("CreateEx"), &Vehicle_CreateEx)
        .StaticOverload< LightObj & (*)(Int32, Int32, Float32, Float32, Float32, Float32, Int32, Int32, Int32, LightObj &) >
            (_SC("CreateEx"), &Vehicle_CreateEx)
        .StaticOverload< LightObj & (*)(Int32, Int32, const Vector3 &, Float32, Int32, Int32) >
            (_SC("Create"), &Vehicle_Create)
        .StaticOverload< LightObj & (*)(Int32, Int32, const Vector3 &, Float32, Int32, Int32, Int32, LightObj &) >
            (_SC("Create"), &Vehicle_Create)
        // Raw Squirrel Methods
        .SquirrelFunc(_SC("NullInst"), &CVehicle::SqGetNull)
        .SquirrelFunc(_SC("MakeTask"), &Tasks::MakeTask< CVehicle, ENT_VEHICLE >)
        .SquirrelFunc(_SC("DropTask"), &Tasks::DropTask< CVehicle, ENT_VEHICLE >)
        .SquirrelFunc(_SC("DoesTask"), &Tasks::DoesTask< CVehicle, ENT_VEHICLE >)
        .SquirrelFunc(_SC("FindTask"), &Tasks::FindTask< CVehicle, ENT_VEHICLE >)
    );
}

} // Namespace:: SqMod
