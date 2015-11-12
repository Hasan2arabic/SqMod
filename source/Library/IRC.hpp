#ifndef _LIBRARY_IRC_HPP_
#define _LIBRARY_IRC_HPP_

// ------------------------------------------------------------------------------------------------
#include "Common.hpp"

// ------------------------------------------------------------------------------------------------
#include <libircclient.h>
#include <libirc_rfcnumeric.h>

// ------------------------------------------------------------------------------------------------
namespace SqMod {
namespace IRC {

/* ------------------------------------------------------------------------------------------------
 * ...
*/
class Session
{
protected:

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static irc_callbacks_t  s_Callbacks;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static bool             s_Initialized;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static irc_callbacks_t * GetCallbacks();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void ForwardEvent(Session * session, Function & listener, const char * event,
                                const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void ForwardEvent(Session * session, Function & listener, unsigned int event,
                                const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void ForwardEvent(Session * session, Function & listener, const char * nick,
                                const char * addr, irc_dcc_t dccid);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void ForwardEvent(Session * session, Function & listener, const char * nick,
                                const char * addr, const char * filename, unsigned long size, irc_dcc_t dccid);

public:

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Session();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Session(const Session & o) = default;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Session(Session && o) = default;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    ~Session();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Session & operator = (const Session & o) = default;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Session & operator = (Session && o) = default;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void Process(SQFloat delta);

    /* --------------------------------------------------------------------------------------------
      * ...
     */
    void VMClose();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 Cmp(const Session & o) const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    const SQChar * ToString() const;

    /* --------------------------------------------------------------------------------------------
     * Retrieve the local tag.
    */
    const SQChar * GetTag() const;

    /* --------------------------------------------------------------------------------------------
     * Change the local tag.
    */
    void SetTag(const SQChar * tag);

    /* --------------------------------------------------------------------------------------------
     * Retrieve the local data.
    */
    SqObj & GetData();

    /* --------------------------------------------------------------------------------------------
     * Change the local data.
    */
    void SetData(SqObj & data);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    const SQChar * GetServer() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetServer(const SQChar * server);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    const SQChar * GetPassword() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetPassword(const SQChar * passwd);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    const SQChar * GetNick() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetNick(const SQChar * nick);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    const SQChar * GetUser() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetUser(const SQChar * user);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    const SQChar * GetName() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetName(const SQChar * name);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQUint32 GetPort() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetPort(SQUint32 port);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQUint32 GetTries() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetTries(SQUint32 num);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQFloat GetWait() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetWait(SQFloat time);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQUint32 GetLeftTries() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetLeftTries(SQUint32 num);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQFloat GetNextTry() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetNextTry(SQFloat time);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQFloat GetSessionTime() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    bool GetReconnect() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    bool GetIPv6() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnConnect();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnConnect(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnConnect_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnNick();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnNick(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnNick_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnQuit();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnQuit(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnQuit_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnJoin();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnJoin(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnJoin_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnPart();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnPart(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnPart_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnMode();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnMode(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnMode_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnUmode();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnUmode(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnUmode_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnTopic();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnTopic(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnTopic_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnKick();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnKick(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnKick_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnChannel();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnChannel(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnChannel_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnPrivMSG();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnPrivMSG(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnPrivMSG_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnNotice();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnNotice(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnNotice_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnChannel_Notice();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnChannel_Notice(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnChannel_Notice_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnInvite();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnInvite(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnInvite_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnCTCP_Req();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnCTCP_Req(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnCTCP_Req_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnCTCP_Rep();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnCTCP_Rep(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnCTCP_Rep_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnCTCP_Action();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnCTCP_Action(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnCTCP_Action_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnUnknown();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnUnknown(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnUnknown_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnNumeric();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnNumeric(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnNumeric_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnDcc_Chat_Req();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnDcc_Chat_Req(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnDcc_Chat_Req_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function GetOnDcc_Send_Req();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnDcc_Send_Req(Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOnDcc_Send_Req_Env(SqObj & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    bool IsValid() const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 Connect();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 Connect(const SQChar * server, SQUint32 port, const SQChar * nick);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 Connect(const SQChar * server, SQUint32 port, const SQChar * nick, const SQChar * passwd);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 Connect(const SQChar * server, SQUint32 port, const SQChar * nick, const SQChar * passwd,
                    const SQChar * username);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 Connect(const SQChar * server, SQUint32 port, const SQChar * nick, const SQChar * passwd,
                    const SQChar * username, const SQChar * realname);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 Connect6();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 Connect6(const SQChar * server, SQUint32 port, const SQChar * nick);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 Connect6(const SQChar * server, SQUint32 port, const SQChar * nick, const SQChar * passwd);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 Connect6(const SQChar * server, SQUint32 port, const SQChar * nick, const SQChar * passwd,
                    const SQChar * username);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 Connect6(const SQChar * server, SQUint32 port, const SQChar * nick, const SQChar * passwd,
                    const SQChar * username, const SQChar * realname);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void Disconnect();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    bool IsConnected();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdJoin(const SQChar * channel);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdJoin(const SQChar * channel, const SQChar * key);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdPart(const SQChar * channel);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdInvite(const SQChar * nick, const SQChar * channel);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdNames(const SQChar * channel);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdList();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdList(const SQChar * channel);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdTopic(const SQChar * channel);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdTopic(const SQChar * channel, const SQChar * topic);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdChannelMode(const SQChar * channel);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdChannelMode(const SQChar * channel, const SQChar * mode);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdUserMode();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdUserMode(const SQChar * mode);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdKick(const SQChar * nick, const SQChar * channel);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdKick(const SQChar * nick, const SQChar * channel, const SQChar * reason);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdMsg(const SQChar * nch, const SQChar * text);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdMe(const SQChar * nch, const SQChar * text);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdNotice(const SQChar * nch, const SQChar * text);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdCtcpRequest(const SQChar * nick, const SQChar * request);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdCtcpReply(const SQChar * nick, const SQChar * reply);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdNick(const SQChar * nick);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdWhois(const SQChar * nick);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdQuit();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 CmdQuit(const SQChar * reason);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 SendRaw(const SQChar * str);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 DestroyDcc(SQUint32 dccid);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetCtcpVersion(const SQChar * version);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32 GetErrNo();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    const SQChar * GetErrStr();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void SetOption(SQUint32 option);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void ResetOption(SQUint32 option);

protected:

    /* --------------------------------------------------------------------------------------------
     * Throw a bad reference error.
    */
    void _Handle(const char * loc, const char * act) const
    {
        DbgWrn("IRC.Session", loc, "Attempting to <%s> using an invalid session: null", act);
    }

    /* --------------------------------------------------------------------------------------------
     * Throw a bad action error.
    */
    void _Issue(const char * loc, const char * act, const char * msg) const
    {
        DbgErr("IRC.Session", loc, "Attempting to <%s> %s", act, msg);
    }

    /* --------------------------------------------------------------------------------------------
     * Throw a bad result error.
    */
    void _Error(const char * loc, const char * act, const char * inf) const
    {
        DbgErr("IRC.Session", loc, "Unable to <%s> because: %s", act, inf);
    }

private:

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    irc_session_t*  m_Session;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    String          m_Server;
    String          m_Passwd;
    String          m_Nick;
    String          m_User;
    String          m_Name;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQInt32         m_Port;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQUint32        m_Tries;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQFloat         m_Wait;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQUint32        m_LeftTries;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQFloat         m_NextTry;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SQFloat         m_SessionTime;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    bool            m_Reconnect;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    bool            m_IPv6;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Function        m_OnConnect;
    Function        m_OnNick;
    Function        m_OnQuit;
    Function        m_OnJoin;
    Function        m_OnPart;
    Function        m_OnMode;
    Function        m_OnUmode;
    Function        m_OnTopic;
    Function        m_OnKick;
    Function        m_OnChannel;
    Function        m_OnPrivMSG;
    Function        m_OnNotice;
    Function        m_OnChannel_Notice;
    Function        m_OnInvite;
    Function        m_OnCTCP_Req;
    Function        m_OnCTCP_Rep;
    Function        m_OnCTCP_Action;
    Function        m_OnUnknown;
    Function        m_OnNumeric;
    Function        m_OnDcc_Chat_Req;
    Function        m_OnDcc_Send_Req;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    String          m_Tag;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SqObj           m_Data;

public:

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnConnect(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnNick(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnQuit(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnJoin(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnPart(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnMode(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnUmode(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnTopic(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnKick(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnChannel(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnPrivMSG(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnNotice(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnChannel_Notice(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnInvite(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnCTCP_Req(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnCTCP_Rep(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnCTCP_Action(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnUnknown(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnNumeric(irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnDcc_Chat_Req(irc_session_t * session, const char * nick, const char * addr, irc_dcc_t dccid);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void OnDcc_Send_Req(irc_session_t * session, const char * nick, const char * addr, const char * filename, unsigned long size, irc_dcc_t dccid);

};

} // Namespace:: IRC
} // Namespace:: SqMod

#endif // _LIBRARY_IRC_HPP_
