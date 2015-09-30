#ifndef _MISC_SOUND_HPP_
#define _MISC_SOUND_HPP_

// ------------------------------------------------------------------------------------------------
#include "Common.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
class CSound
{
public:
    // --------------------------------------------------------------------------------------------
    CSound() noexcept;
    CSound(SQInt32 id) noexcept;
    // --------------------------------------------------------------------------------------------
    CSound(const CSound & x) noexcept;
    CSound(CSound && x) noexcept;
    // --------------------------------------------------------------------------------------------
    ~CSound();
    // --------------------------------------------------------------------------------------------
    CSound & operator= (const CSound & x) noexcept;
    CSound & operator= (CSound && x) noexcept;
    // --------------------------------------------------------------------------------------------
    CSound operator+ (const CSound & x) const noexcept;
    CSound operator- (const CSound & x) const noexcept;
    CSound operator* (const CSound & x) const noexcept;
    CSound operator/ (const CSound & x) const noexcept;
    // --------------------------------------------------------------------------------------------
    bool operator == (const CSound & x) const noexcept;
    bool operator != (const CSound & x) const noexcept;
    bool operator < (const CSound & x) const noexcept;
    bool operator > (const CSound & x) const noexcept;
    bool operator <= (const CSound & x) const noexcept;
    bool operator >= (const CSound & x) const noexcept;
    // --------------------------------------------------------------------------------------------
    SQInteger Cmp(const CSound & x) const noexcept;
    // --------------------------------------------------------------------------------------------
    operator SQInt32 () const noexcept;
    operator bool () const noexcept;
    // --------------------------------------------------------------------------------------------
    SQInt32 GetID() const noexcept;
    void SetID(SQInt32 id) noexcept;
    // --------------------------------------------------------------------------------------------
    void Play() const noexcept;
protected:
    // --------------------------------------------------------------------------------------------
    SQInt32 m_ID;
};

} // Namespace:: SqMod

#endif // _MISC_SOUND_HPP_