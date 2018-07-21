#ifndef OPENMW_NETWORKING_HPP
#define OPENMW_NETWORKING_HPP

#include <components/openmw-mp/Controllers/PlayerPacketController.hpp>
#include <components/openmw-mp/Controllers/ActorPacketController.hpp>
#include <components/openmw-mp/Controllers/ObjectPacketController.hpp>
#include <components/openmw-mp/Controllers/WorldstatePacketController.hpp>
#include <components/openmw-mp/Packets/PacketPreInit.hpp>
#include "Player.hpp"

class MasterClient;
namespace  mwmp
{
    class Networking
    {
    public:
        Networking(RakNet::RakPeerInterface *peer);
        ~Networking();

        void newPlayer(RakNet::RakNetGUID guid);
        void disconnectPlayer(RakNet::RakNetGUID guid);
        void kickPlayer(RakNet::RakNetGUID guid, bool sendNotification = true);
        
        void banAddress(const char *ipAddress);
        void unbanAddress(const char *ipAddress);
        RakNet::SystemAddress getSystemAddress(RakNet::RakNetGUID guid);

        void processPlayerPacket(RakNet::Packet *packet);
        void processActorPacket(RakNet::Packet *packet);
        void processObjectPacket(RakNet::Packet *packet);
        void processWorldstatePacket(RakNet::Packet *packet);
        void update(RakNet::Packet *packet, RakNet::BitStream &bsIn);

        unsigned short numberOfConnections() const;
        unsigned int maxConnections() const;
        int getAvgPing(RakNet::AddressOrGUID) const;

        int mainLoop();

        void stopServer(int code);

        PlayerPacketController *getPlayerPacketController() const;
        ActorPacketController *getActorPacketController() const;
        ObjectPacketController *getObjectPacketController() const;
        WorldstatePacketController *getWorldstatePacketController() const;

        BaseActorList *getReceivedActorList();
        BaseObjectList *getReceivedObjectList();
        BaseWorldstate *getReceivedWorldstate();

        int getCurrentMpNum();
        void setCurrentMpNum(int value);
        int incrementMpNum();

        bool getPluginEnforcementState();
        void setPluginEnforcementState(bool state);

        MasterClient *getMasterClient();
        void InitQuery(std::string queryAddr, unsigned short queryPort);
        void setServerPassword(std::string passw) noexcept;
        bool isPassworded() const;

        static const Networking &get();
        static Networking *getPtr();

        void postInit();
    private:
        bool preInit(RakNet::Packet *packet, RakNet::BitStream &bsIn);
        PacketPreInit::PluginContainer getPluginListSample();
        std::string serverPassword;
        static Networking *sThis;

        RakNet::RakPeerInterface *peer;
        RakNet::BitStream bsOut;
        TPlayers *players;
        MasterClient *mclient;

        BaseActorList baseActorList;
        BaseObjectList baseObjectList;
        BaseWorldstate baseWorldstate;

        PlayerPacketController *playerPacketController;
        ActorPacketController *actorPacketController;
        ObjectPacketController *objectPacketController;
        WorldstatePacketController *worldstatePacketController;

        bool running;
        int exitCode;
        PacketPreInit::PluginContainer samples;
    };
}


#endif //OPENMW_NETWORKING_HPP
