#ifndef _MISC_RADIO_HPP_
#define _MISC_RADIO_HPP_

// ------------------------------------------------------------------------------------------------
#include "Common.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
class CRadio
{
public:
    // --------------------------------------------------------------------------------------------
    CRadio() noexcept;
    CRadio(SQInt32 id) noexcept;
    // --------------------------------------------------------------------------------------------
    CRadio(const CRadio & x) noexcept;
    CRadio(CRadio && x) noexcept;
    // --------------------------------------------------------------------------------------------
    ~CRadio();
    // --------------------------------------------------------------------------------------------
    CRadio & operator= (const CRadio & x) noexcept;
    CRadio & operator= (CRadio && x) noexcept;
    // --------------------------------------------------------------------------------------------
    CRadio operator+ (const CRadio & x) const noexcept;
    CRadio operator- (const CRadio & x) const noexcept;
    CRadio operator* (const CRadio & x) const noexcept;
    CRadio operator/ (const CRadio & x) const noexcept;
    // --------------------------------------------------------------------------------------------
    bool operator == (const CRadio & x) const noexcept;
    bool operator != (const CRadio & x) const noexcept;
    bool operator < (const CRadio & x) const noexcept;
    bool operator > (const CRadio & x) const noexcept;
    bool operator <= (const CRadio & x) const noexcept;
    bool operator >= (const CRadio & x) const noexcept;
    // --------------------------------------------------------------------------------------------
    SQInteger Cmp(const CRadio & x) const noexcept;
    // --------------------------------------------------------------------------------------------
    operator SQInt32 () const noexcept;
    operator bool () const noexcept;
    // --------------------------------------------------------------------------------------------
    SQInt32 GetID() const noexcept;
    void SetID(SQInt32 id) noexcept;
    // --------------------------------------------------------------------------------------------
    CRadio & SetnGet(SQInt32 id) noexcept;
    // --------------------------------------------------------------------------------------------
    void Apply(const CVehicle & vehicle) const noexcept;
protected:
    // --------------------------------------------------------------------------------------------
    SQInt32 m_ID;
};

} // Namespace:: SqMod

#endif // _MISC_RADIO_HPP_