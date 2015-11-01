#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

// ------------------------------------------------------------------------------------------------
#include "Common.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
class Logger
{
public:
    // --------------------------------------------------------------------------------------------
    static constexpr Uint8 LEVEL_NIL = (1 << 0);
    static constexpr Uint8 LEVEL_DBG = (1 << 1);
    static constexpr Uint8 LEVEL_MSG = (1 << 2);
    static constexpr Uint8 LEVEL_SCS = (1 << 3);
    static constexpr Uint8 LEVEL_INF = (1 << 4);
    static constexpr Uint8 LEVEL_WRN = (1 << 5);
    static constexpr Uint8 LEVEL_ERR = (1 << 6);
    static constexpr Uint8 LEVEL_FTL = (1 << 7);
    static constexpr Uint8 LEVEL_ANY = 0xFF;

private:
    // --------------------------------------------------------------------------------------------
    friend class std::unique_ptr<Logger, void(*)(Logger *)>;

    // --------------------------------------------------------------------------------------------
    Logger();

    // --------------------------------------------------------------------------------------------
    ~Logger();

    // --------------------------------------------------------------------------------------------
    static void _Finalizer(Logger * ptr);

    // --------------------------------------------------------------------------------------------
public:
    // --------------------------------------------------------------------------------------------
    typedef std::unique_ptr<Logger, void(*)(Logger *)>    Pointer;

    // --------------------------------------------------------------------------------------------
    static Pointer Inst();

    // --------------------------------------------------------------------------------------------
    bool Init();
    bool Load();

    // --------------------------------------------------------------------------------------------
    void Deinit();
    void Unload();

    // --------------------------------------------------------------------------------------------
    void Terminate();

    // --------------------------------------------------------------------------------------------
    void ToggleConsoleTime(bool enabled);
    void ToggleFileTime(bool enabled);
    bool HasConsoleTime() const;
    bool HasFileTime() const;

    // --------------------------------------------------------------------------------------------
    void SetConsoleLevels(Uint8 levels);
    void SetFileLevels(Uint8 levels);
    Uint8 GetConsoleLevels() const;
    Uint8 GetFileLevels() const;

    // --------------------------------------------------------------------------------------------
    void EnableConsoleLevel(Uint8 level);
    void EnableFileLevel(Uint8 level);
    void DisableConsoleLevel(Uint8 level);
    void DisableFileLevel(Uint8 level);

    // --------------------------------------------------------------------------------------------
    Uint8 GetDebugLevel() const;
    void SetDebugLevel(Uint8 level);

    // --------------------------------------------------------------------------------------------
    SQInt32 GetVerbosity() const;
    void SetVerbosity(SQInt32 level);

public:
    // --------------------------------------------------------------------------------------------
    void Send(Uint8 type, bool sub, const char * fmt, va_list args);

    // --------------------------------------------------------------------------------------------
    void Dbg(const char * fmt, ...);
    void Msg(const char * fmt, ...);
    void Scs(const char * fmt, ...);
    void Inf(const char * fmt, ...);
    void Wrn(const char * fmt, ...);
    void Err(const char * fmt, ...);
    void Ftl(const char * fmt, ...);

    // --------------------------------------------------------------------------------------------
    void SDbg(const char * fmt, ...);
    void SMsg(const char * fmt, ...);
    void SScs(const char * fmt, ...);
    void SInf(const char * fmt, ...);
    void SWrn(const char * fmt, ...);
    void SErr(const char * fmt, ...);
    void SFtl(const char * fmt, ...);

    // --------------------------------------------------------------------------------------------
    bool cDbg(bool cond, const char * fmt, ...);
    bool cMsg(bool cond, const char * fmt, ...);
    bool cScs(bool cond, const char * fmt, ...);
    bool cInf(bool cond, const char * fmt, ...);
    bool cWrn(bool cond, const char * fmt, ...);
    bool cErr(bool cond, const char * fmt, ...);
    bool cFtl(bool cond, const char * fmt, ...);

    // --------------------------------------------------------------------------------------------
    bool cSDbg(bool cond, const char * fmt, ...);
    bool cSMsg(bool cond, const char * fmt, ...);
    bool cSScs(bool cond, const char * fmt, ...);
    bool cSInf(bool cond, const char * fmt, ...);
    bool cSWrn(bool cond, const char * fmt, ...);
    bool cSErr(bool cond, const char * fmt, ...);
    bool cSFtl(bool cond, const char * fmt, ...);

private:
    // --------------------------------------------------------------------------------------------
    bool        m_ConsoleTime;
    bool        m_FileTime;

    // --------------------------------------------------------------------------------------------
    Uint8       m_ConsoleLevels;
    Uint8       m_FileLevels;

    // --------------------------------------------------------------------------------------------
    String      m_LogPath;
    
    // --------------------------------------------------------------------------------------------
    Uint8       m_DebugLevel;

    // --------------------------------------------------------------------------------------------
    SQInt32     m_Verbosity;
};

// --------------------------------------------------------------------------------------------
extern const Logger::Pointer _Log;

} // Namespace:: SqMod

#endif // _LOGGER_HPP_
