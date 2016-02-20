// ------------------------------------------------------------------------------------------------
#include "Base/Color3.hpp"
#include "Base/Vector2.hpp"
#include "Base/Vector3.hpp"
#include "Entity/Player.hpp"
#include "Library/Numeric.hpp"

// ------------------------------------------------------------------------------------------------
#include "Misc/Functions.hpp"
#include "Misc/Model.hpp"
#include "Misc/Player.hpp"
#include "Misc/Vehicle.hpp"
#include "Misc/Weapon.hpp"
#include "Misc/World.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ================================================================================================
void Register_Misc(HSQUIRRELVM vm)
{
    Table srvns(vm);

    srvns.Func(_SC("SetTimeRate"), &SetTimeRate)
    .Func(_SC("GetTimeRate"), &GetTimeRate)
    .Func(_SC("SetHour"), &SetHour)
    .Func(_SC("GetHour"), &GetHour)
    .Func(_SC("SetMinute"), &SetMinute)
    .Func(_SC("GetMinute"), &GetMinute)
    .Func(_SC("SetWeather"), &SetWeather)
    .Func(_SC("GetWeather"), &GetWeather)
    .Func(_SC("SetGravity"), &SetGravity)
    .Func(_SC("GetGravity"), &GetGravity)
    .Func(_SC("SetGamespeed"), &SetGamespeed)
    .Func(_SC("GetGamespeed"), &GetGamespeed)
    .Func(_SC("SetWaterLevel"), &SetWaterLevel)
    .Func(_SC("GetWaterLevel"), &GetWaterLevel)
    .Func(_SC("SetMaxHeight"), &SetMaxHeight)
    .Func(_SC("GetMaxHeight"), &GetMaxHeight)
    .Func(_SC("SetKillCmdDelay"), &SetKillCmdDelay)
    .Func(_SC("GetKillCmdDelay"), &GetKillCmdDelay)
    .Func(_SC("SetVehiclesForcedRespawnHeight"), &SetVehiclesForcedRespawnHeight)
    .Func(_SC("GetVehiclesForcedRespawnHeight"), &GetVehiclesForcedRespawnHeight)
    .Func(_SC("ToggleSyncFrameLimiter"), &ToggleSyncFrameLimiter)
    .Func(_SC("EnabledSyncFrameLimiter"), &EnabledSyncFrameLimiter)
    .Func(_SC("ToggleFrameLimiter"), &ToggleFrameLimiter)
    .Func(_SC("EnabledFrameLimiter"), &EnabledFrameLimiter)
    .Func(_SC("ToggleTaxiBoostJump"), &ToggleTaxiBoostJump)
    .Func(_SC("EnabledTaxiBoostJump"), &EnabledTaxiBoostJump)
    .Func(_SC("ToggleDriveOnWater"), &ToggleDriveOnWater)
    .Func(_SC("EnabledDriveOnWater"), &EnabledDriveOnWater)
    .Func(_SC("ToggleFastSwitch"), &ToggleFastSwitch)
    .Func(_SC("EnabledFastSwitch"), &EnabledFastSwitch)
    .Func(_SC("ToggleFriendlyFire"), &ToggleFriendlyFire)
    .Func(_SC("EnabledFriendlyFire"), &EnabledFriendlyFire)
    .Func(_SC("ToggleDisableDriveby"), &ToggleDisableDriveby)
    .Func(_SC("EnabledDisableDriveby"), &EnabledDisableDriveby)
    .Func(_SC("TogglePerfectHandling"), &TogglePerfectHandling)
    .Func(_SC("EnabledPerfectHandling"), &EnabledPerfectHandling)
    .Func(_SC("ToggleFlyingCars"), &ToggleFlyingCars)
    .Func(_SC("EnabledFlyingCars"), &EnabledFlyingCars)
    .Func(_SC("ToggleJumpSwitch"), &ToggleJumpSwitch)
    .Func(_SC("EnabledJumpSwitch"), &EnabledJumpSwitch)
    .Func(_SC("ToggleShowMarkers"), &ToggleShowMarkers)
    .Func(_SC("EnabledShowMarkers"), &EnabledShowMarkers)
    .Func(_SC("ToggleStuntBike"), &ToggleStuntBike)
    .Func(_SC("EnabledStuntBike"), &EnabledStuntBike)
    .Func(_SC("ToggleShootInAir"), &ToggleShootInAir)
    .Func(_SC("EnabledShootInAir"), &EnabledShootInAir)
    .Func(_SC("ToggleShowNametags"), &ToggleShowNametags)
    .Func(_SC("EnabledShowNametags"), &EnabledShowNametags)
    .Func(_SC("ToggleJoinMessages"), &ToggleJoinMessages)
    .Func(_SC("EnabledJoinMessages"), &EnabledJoinMessages)
    .Func(_SC("ToggleDeathMessages"), &ToggleDeathMessages)
    .Func(_SC("EnabledDeathMessages"), &EnabledDeathMessages)
    .Func(_SC("ToggleChatTagsByDefaultEnabled"), &ToggleChatTagsByDefaultEnabled)
    .Func(_SC("EnabledChatTagsByDefault"), &EnabledChatTagsByDefault)
    .Func(_SC("CreateExplosion"), &CreateExplosion)
    .Func(_SC("CreateExplosionEx"), &CreateExplosionEx)
    .Func(_SC("HideMapObject"), &HideMapObject)
    .Func(_SC("HideMapObjectEx"), &HideMapObjectEx)
    .Func(_SC("ShowMapObject"), &ShowMapObject)
    .Func(_SC("ShowMapObjectEx"), &ShowMapObjectEx)
    .Func(_SC("ShowAllMapObjects"), &ShowAllMapObjects)
    .Func(_SC("SetWastedSettings"), &SetWastedSettings)
    .Func(_SC("GetWastedSettings"), &GetWastedSettings)
    .Func(_SC("SetWorldBounds"), &SetWorldBounds)
    .Func(_SC("SetWorldBoundsEx"), &SetWorldBoundsEx)
    .Func(_SC("GetWorldBounds"), &GetWorldBounds)
    .Func(_SC("GetPluginVersion"), &GetPluginVersion)
    .Func(_SC("GetPluginVersionStr"), &GetPluginVersionStr)
    .Func(_SC("GetPluginName"), &GetPluginName)
    .Func(_SC("GetPluginAuthor"), &GetPluginAuthor)
    .Func(_SC("GetPluginID"), &GetPluginID)
    .Func(_SC("GetNumberOfPlugins"), &GetNumberOfPlugins)
    .Func(_SC("FindPlugin"), &FindPlugin)
    .Func(_SC("GetVersion"), &GetServerVersion)
    .Func(_SC("GetPort"), &GetServerPort)
    .Func(_SC("GetFlags"), &GetServerFlags)
    .Func(_SC("SetName"), &SetServerName)
    .Func(_SC("GetName"), &GetServerName)
    .Func(_SC("GetTime"), &GetTime)
    .Func(_SC("SendCustomCommand"), &SendCustomCommand)
    .Func(_SC("SetMaxPlayers"), &SetMaxPlayers)
    .Func(_SC("GetMaxPlayers"), &GetMaxPlayers)
    .Func(_SC("SetServerPassword"), &SetServerPassword)
    .Func(_SC("GetServerPassword"), &GetServerPassword)
    .Func(_SC("SetGameModeText"), &SetGameModeText)
    .Func(_SC("GetGameModeText"), &GetGameModeText)
    .Func(_SC("AddRadioStream"), &AddRadioStream)
    .Func(_SC("RemoveRadioStream"), &RemoveRadioStream);

    RootTable(vm).Bind(_SC("Server"), srvns);

    RootTable(vm)
    .Func(_SC("GetModelName"), &GetModelName)
    .Func(_SC("SetModelName"), &SetModelName)
    .Func(_SC("IsModelWeapon"), &IsModelWeapon)
    .Func(_SC("IsModelActuallyWeapon"), &IsModelActuallyWeapon)
    .Func(_SC("IsWeaponNatural"), &IsWeaponNatural)
    .Func(_SC("SetUseClasses"), &SetUseClasses)
    .Func(_SC("GetUseClasses"), &GetUseClasses)
    .Func(_SC("AddPlayerClass"), &AddPlayerClass)
    .Func(_SC("SetSpawnPlayerPos"), &SetSpawnPlayerPos)
    .Func(_SC("SetSpawnPlayerPosEx"), &SetSpawnPlayerPosEx)
    .Func(_SC("SetSpawnCameraPos"), &SetSpawnCameraPos)
    .Func(_SC("SetSpawnCameraPosEx"), &SetSpawnCameraPosEx)
    .Func(_SC("GetSkinName"), &GetSkinName)
    .Func(_SC("SetSkinName"), &SetSkinName)
    .Func(_SC("GetSkinID"), &GetSkinID)
    .Func(_SC("IsSkinValid"), &IsSkinValid)
    .Func(_SC("FindPlayer"), &FindPlayer)
    .Func(_SC("GetAutomobileName"), &GetAutomobileName)
    .Func(_SC("SetAutomobileName"), &SetAutomobileName)
    .Func(_SC("GetAutomobileID"), &GetAutomobileID)
    .Func(_SC("IsAutomobileValid"), &IsAutomobileValid)
    .Func(_SC("GetWeaponName"), &GetWeaponName)
    .Func(_SC("SetWeaponName"), &SetWeaponName)
    .Func(_SC("GetWeaponID"), &GetWeaponID)
    .Func(_SC("IsWeaponValid"), &IsWeaponValid)
    .Func(_SC("WeaponToModel"), &WeaponToModel)
    .Func(_SC("PlaySound"), &PlaySound)
    .Func(_SC("PlaySoundEx"), &PlaySoundEx);
}

} // Namespace:: SqMod
