#ifndef _MISC_PLAYER_IMMUNITY_HPP_
#define _MISC_PLAYER_IMMUNITY_HPP_

// ------------------------------------------------------------------------------------------------
#include "Common.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
struct CPlayerImmunity
{
    // --------------------------------------------------------------------------------------------
    CPlayerImmunity() noexcept;
    CPlayerImmunity(SQInt32 flags) noexcept;
    // --------------------------------------------------------------------------------------------
    CPlayerImmunity(const CPlayerImmunity & x) noexcept;
    CPlayerImmunity(CPlayerImmunity && x) noexcept;
    // --------------------------------------------------------------------------------------------
    ~CPlayerImmunity();
    // --------------------------------------------------------------------------------------------
    CPlayerImmunity & operator = (const CPlayerImmunity & x) noexcept;
    CPlayerImmunity & operator = (CPlayerImmunity && x) noexcept;
    // --------------------------------------------------------------------------------------------
    bool operator == (const CPlayerImmunity & x) const noexcept;
    bool operator != (const CPlayerImmunity & x) const noexcept;
    bool operator < (const CPlayerImmunity & x) const noexcept;
    bool operator > (const CPlayerImmunity & x) const noexcept;
    bool operator <= (const CPlayerImmunity & x) const noexcept;
    bool operator >= (const CPlayerImmunity & x) const noexcept;
    // --------------------------------------------------------------------------------------------
    SQInteger Cmp(const CPlayerImmunity & x) const noexcept;
    // --------------------------------------------------------------------------------------------
    operator SQInt32 () const noexcept;
    operator bool () const noexcept;
    // --------------------------------------------------------------------------------------------
    SQInt32 GetFlags() const noexcept;
    void SetFlags(SQInt32 flags) noexcept;
    // --------------------------------------------------------------------------------------------
    CPlayerImmunity & SetnGet(SQInt32 flags) noexcept;
    // --------------------------------------------------------------------------------------------
    void Apply(const CPlayer & player) const noexcept;
    // --------------------------------------------------------------------------------------------
    bool GetBullet() const noexcept;
    void SetBullet(bool toggle) noexcept;
    // --------------------------------------------------------------------------------------------
    bool GetFire() const noexcept;
    void SetFire(bool toggle) noexcept;
    // --------------------------------------------------------------------------------------------
    bool GetExplosion() const noexcept;
    void SetExplosion(bool toggle) noexcept;
    // --------------------------------------------------------------------------------------------
    bool GetCollision() const noexcept;
    void SetCollision(bool toggle) noexcept;
    // --------------------------------------------------------------------------------------------
    bool GetMelee() const noexcept;
    void SetMelee(bool toggle) noexcept;
    // --------------------------------------------------------------------------------------------
    void EnableAll() noexcept;
    void DisableAll() noexcept;
protected:
    // --------------------------------------------------------------------------------------------
    SQInt32 m_Flags;
};

} // Namespace:: SqMod

#endif // _MISC_PLAYER_IMMUNITY_HPP_