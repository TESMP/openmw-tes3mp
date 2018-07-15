#include "../Packets/Object/PacketObjectActivate.hpp"
#include "../Packets/Object/PacketObjectAnimPlay.hpp"
#include "../Packets/Object/PacketObjectAttach.hpp"
#include "../Packets/Object/PacketObjectCollision.hpp"
#include "../Packets/Object/PacketObjectDelete.hpp"
#include "../Packets/Object/PacketObjectLock.hpp"
#include "../Packets/Object/PacketObjectMove.hpp"
#include "../Packets/Object/PacketObjectPlace.hpp"
#include "../Packets/Object/PacketObjectReset.hpp"
#include "../Packets/Object/PacketObjectRotate.hpp"
#include "../Packets/Object/PacketObjectScale.hpp"
#include "../Packets/Object/PacketObjectSpawn.hpp"
#include "../Packets/Object/PacketObjectState.hpp"
#include "../Packets/Object/PacketObjectTrap.hpp"

#include "../Packets/Object/PacketContainer.hpp"
#include "../Packets/Object/PacketDoorDestination.hpp"
#include "../Packets/Object/PacketDoorState.hpp"
#include "../Packets/Object/PacketMusicPlay.hpp"
#include "../Packets/Object/PacketVideoPlay.hpp"

#include "../Packets/Object/PacketConsoleCommand.hpp"
#include "../Packets/Object/PacketScriptLocalShort.hpp"
#include "../Packets/Object/PacketScriptLocalFloat.hpp"
#include "../Packets/Object/PacketScriptMemberShort.hpp"
#include "../Packets/Object/PacketScriptMemberFloat.hpp"
#include "../Packets/Object/PacketScriptGlobalShort.hpp"
#include "../Packets/Object/PacketScriptGlobalFloat.hpp"

#include "ObjectPacketController.hpp"

template <typename T>
inline void AddPacket(mwmp::ObjectPacketController::packets_t *packets, RakNet::RakPeerInterface *peer)
{
    T *packet = new T(peer);
    typedef mwmp::ObjectPacketController::packets_t::value_type value_t;
    packets->insert(value_t(packet->GetPacketID(), value_t::second_type(packet)));
}

mwmp::ObjectPacketController::ObjectPacketController(RakNet::RakPeerInterface *peer)
{
    AddPacket<PacketObjectActivate>(&packets, peer);
    AddPacket<PacketObjectAnimPlay>(&packets, peer);
    AddPacket<PacketObjectAttach>(&packets, peer);
    AddPacket<PacketObjectCollision>(&packets, peer);
    AddPacket<PacketObjectDelete>(&packets, peer);
    AddPacket<PacketObjectLock>(&packets, peer);
    AddPacket<PacketObjectMove>(&packets, peer);
    AddPacket<PacketObjectPlace>(&packets, peer);
    AddPacket<PacketObjectReset>(&packets, peer);
    AddPacket<PacketObjectRotate>(&packets, peer);
    AddPacket<PacketObjectScale>(&packets, peer);
    AddPacket<PacketObjectSpawn>(&packets, peer);
    AddPacket<PacketObjectState>(&packets, peer);
    AddPacket<PacketObjectTrap>(&packets, peer);
    
    AddPacket<PacketContainer>(&packets, peer);
    AddPacket<PacketDoorDestination>(&packets, peer);
    AddPacket<PacketDoorState>(&packets, peer);
    AddPacket<PacketMusicPlay>(&packets, peer);
    AddPacket<PacketVideoPlay>(&packets, peer);

    AddPacket<PacketConsoleCommand>(&packets, peer);
    AddPacket<PacketScriptLocalShort>(&packets, peer);
    AddPacket<PacketScriptLocalFloat>(&packets, peer);
    AddPacket<PacketScriptMemberShort>(&packets, peer);
    AddPacket<PacketScriptMemberFloat>(&packets, peer);
    AddPacket<PacketScriptGlobalShort>(&packets, peer);
    AddPacket<PacketScriptGlobalFloat>(&packets, peer);
}


mwmp::ObjectPacket *mwmp::ObjectPacketController::GetPacket(RakNet::MessageID id)
{
    return packets[(unsigned char)id].get();
}

void mwmp::ObjectPacketController::SetStream(RakNet::BitStream *inStream, RakNet::BitStream *outStream)
{
    for(const auto &packet : packets)
        packet.second->SetStreams(inStream, outStream);
}

bool mwmp::ObjectPacketController::ContainsPacket(RakNet::MessageID id)
{
    for(const auto &packet : packets)
    {
        if (packet.first == id)
            return true;
    }
    return false;
}
