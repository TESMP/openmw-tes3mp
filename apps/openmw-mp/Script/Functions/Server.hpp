#ifndef OPENMW_SERVERAPI_HPP
#define OPENMW_SERVERAPI_HPP

#include "../Types.hpp"

#define SERVERAPI \
    {"StopServer",          ServerFunctions::StopServer},\
    \
    {"Kick",                ServerFunctions::Kick},\
    {"BanAddress",          ServerFunctions::BanAddress},\
    {"UnbanAddress",        ServerFunctions::UnbanAddress},\
    \
    {"GetServerVersion",    ServerFunctions::GetServerVersion},\
    {"GetProtocolVersion",  ServerFunctions::GetProtocolVersion},\
    {"GetAvgPing",          ServerFunctions::GetAvgPing},\
    {"GetIP",               ServerFunctions::GetIP},\
    {"GetMaxPlayers",       ServerFunctions::GetMaxPlayers},\
    {"GetPort",             ServerFunctions::GetPort},\
    {"HasPassword",         ServerFunctions::HasPassword},\
    \
    {"SetGameMode",         ServerFunctions::SetGameMode},\
    {"SetHostname",         ServerFunctions::SetHostname},\
    {"SetServerPassword",   ServerFunctions::SetServerPassword},\
    {"SetRuleString",       ServerFunctions::SetRuleString},\
    {"SetRuleValue",        ServerFunctions::SetRuleValue}

class ServerFunctions
{
public:

    /**
    * \brief Shut down the server.
    *
    * \param code The shutdown code.
    * \return void
    */
    static void StopServer(int code) noexcept;

    /**
    * \brief Kick a certain player from the server.
    *
    * \param pid The player ID.
    * \return void
    */
    static void Kick(unsigned short pid) noexcept;

    /**
    * \brief Ban a certain IP address from the server.
    *
    * \param ipAddress The IP address.
    * \return void
    */
    static void BanAddress(const char *ipAddress) noexcept;

    /**
    * \brief Unban a certain IP address from the server.
    *
    * \param ipAddress The IP address.
    * \return void
    */
    static void UnbanAddress(const char *ipAddress) noexcept;

    /**
    * \brief Get the TES3MP version of the server.
    *
    * \return The server version.
    */
    static const char *GetServerVersion() noexcept;

    /**
    * \brief Get the protocol version of the server.
    *
    * \return The protocol version.
    */
    static const char *GetProtocolVersion() noexcept;

    /**
    * \brief Get the average ping of a certain player.
    *
    * \param pid The player ID.
    * \return The average ping.
    */
    static int GetAvgPing(unsigned short pid) noexcept;

    /**
    * \brief Get the IP address of a certain player.
    *
    * \param pid The player ID.
    * \return The IP address.
    */
    static const char* GetIP(unsigned short pid) noexcept;

    /**
     * \brief Get the port used by the server.
     *
     * \return Port
     */
    static unsigned short GetPort() noexcept;

    /**
     * \brief Get the maximum number of players.
     *
     * \return Max players
     */
    static unsigned int GetMaxPlayers() noexcept;

    /**
     * \brief Checking if the server requires a password to connect.
     *
     * @return
     */
    static bool HasPassword() noexcept;

    /**
    * \brief Set the game mode of the server, as displayed in the server browser.
    *
    * \param name The new game mode.
    * \return void
    */
    static void SetGameMode(const char* gameMode) noexcept;

    /**
    * \brief Set the name of the server, as displayed in the server browser.
    *
    * \param name The new name.
    * \return void
    */
    static void SetHostname(const char* name) noexcept;

    /**
    * \brief Set the password required to join the server.
    *
    * \param password The password.
    * \return void
    */
    static void SetServerPassword(const char *passw) noexcept;

    /**
    * \brief Set a rule string for the server details displayed in the server browser.
    *
    * \param key The name of the rule.
    * \param value The string value of the rule.
    * \return void
    */
    static void SetRuleString(const char *key, const char *value) noexcept;

    /**
    * \brief Set a rule value for the server details displayed in the server browser.
    *
    * \param key The name of the rule.
    * \param value The numerical value of the rule.
    * \return void
    */
    static void SetRuleValue(const char *key, double value) noexcept;
};

#endif //OPENMW_SERVERAPI_HPP
