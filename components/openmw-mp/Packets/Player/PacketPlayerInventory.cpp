//
// Created by koncord on 22.10.16.
//

#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketPlayerInventory.hpp"

using namespace std;
using namespace mwmp;

PacketPlayerInventory::PacketPlayerInventory(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_INVENTORY;
}

void PacketPlayerInventory::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);

    RW(player->inventoryChanges.action, send);

    if (send)
        player->inventoryChanges.count = (unsigned int) (player->inventoryChanges.items.size());
    else
        player->inventoryChanges.items.clear();

    RW(player->inventoryChanges.count, send);

    for (unsigned int i = 0; i < player->inventoryChanges.count; i++)
    {
        Item item;

        if (send)
            item = player->inventoryChanges.items.at(i);

        RW(item.refId, send, true);
        RW(item.count, send);
        RW(item.charge, send);
        RW(item.enchantmentCharge, send);
        RW(item.soul, send, true);

        if (!send)
            player->inventoryChanges.items.push_back(item);
    }
}
