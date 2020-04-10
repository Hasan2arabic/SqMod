#pragma once

// ------------------------------------------------------------------------------------------------
#include "Library/Chrono.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 *
*/
class Timer
{
    /* --------------------------------------------------------------------------------------------
     *
    */
    Timer(Int64 t)
        : m_Timestamp(t)
    {
        /* ... */
    }

public:

    /* --------------------------------------------------------------------------------------------
     *
    */
    Timer();

    /* --------------------------------------------------------------------------------------------
     *
    */
    Timer(const Timer & o)
        : m_Timestamp(o.m_Timestamp)
    {
        /* ... */
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    ~Timer()
    {
        /* ... */
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    Timer & operator = (const Timer o)
    {
        m_Timestamp = o.m_Timestamp;
        return *this;
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Int32 Cmp(const Timer & b) const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    CSStr ToString() const;

    /* --------------------------------------------------------------------------------------------
     *
    */
    void Reset();

    /* --------------------------------------------------------------------------------------------
     *
    */
    Timestamp Restart();

    /* --------------------------------------------------------------------------------------------
     *
    */
    Int64 RestartRaw();

    /* --------------------------------------------------------------------------------------------
     *
    */
    Timestamp GetElapsedTime() const;

    /* --------------------------------------------------------------------------------------------
     *
    */
    Int64 GetElapsedTimeRaw() const;

private:

    // --------------------------------------------------------------------------------------------
    Int64   m_Timestamp;
};

} // Namespace:: SqMod