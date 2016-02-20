#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

// ------------------------------------------------------------------------------------------------
#include "Base/Shared.hpp"
#include "Base/Buffer.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
enum LogLvl
{
    LL_NIL = (1 << 0),
    LL_DBG = (1 << 1),
    LL_USR = (1 << 2),
    LL_SCS = (1 << 3),
    LL_INF = (1 << 4),
    LL_WRN = (1 << 5),
    LL_ERR = (1 << 6),
    LL_FTL = (1 << 7),
    LL_ANY = 0xFF
};

// --------------------------------------------------------------------------------------------
extern Logger * _Log;

// ------------------------------------------------------------------------------------------------
class Logger
{
protected:

    // --------------------------------------------------------------------------------------------
    Logger();

    // --------------------------------------------------------------------------------------------
    Logger(Logger const &);

    // --------------------------------------------------------------------------------------------
    Logger & operator= (Logger const &);

public:

    // --------------------------------------------------------------------------------------------
    ~Logger();

    // --------------------------------------------------------------------------------------------
    static Logger * Get()
    {
        if (!_Log)
        {
            return _Log = new Logger();
        }

        return _Log;
    }

    // --------------------------------------------------------------------------------------------
    void ToggleTime(bool enabled) { m_Time = enabled; }
    bool HasTime() const { return m_Time; }

    // --------------------------------------------------------------------------------------------
    void SetLevels(Uint8 levels) { m_Levels = levels; }
    Uint8 GetLevels() const { return m_Levels; }

    // --------------------------------------------------------------------------------------------
    void EnableLevel(Uint8 level) { m_Levels |= level; }
    void DisableLevel(Uint8 level) { if (m_Levels & level) m_Levels ^= level; }

    // --------------------------------------------------------------------------------------------
    void Send(Uint8 type, bool sub, CCStr fmt, va_list args);

    // --------------------------------------------------------------------------------------------
    void Message(Uint8 type, bool sub, CCStr fmt, ...);

    // --------------------------------------------------------------------------------------------
    void Throw(CCStr fmt, ...);
    void Throw(CCStr fmt, va_list args);
    void Debug(CCStr fmt, ...);
    void Debug(CCStr fmt, va_list args);

protected:

    // --------------------------------------------------------------------------------------------
    void Proccess(Uint8 type, bool sub);

private:

    // --------------------------------------------------------------------------------------------
    Buffer      m_Buffer;
    SQChar      m_TmBuff[80];

    // --------------------------------------------------------------------------------------------
    Uint8       m_Levels;
    bool        m_Time;
};

} // Namespace:: SqMod

#endif // _LOGGER_HPP_
