#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketPlayerJournal.hpp"

using namespace std;
using namespace mwmp;

PacketPlayerJournal::PacketPlayerJournal(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_JOURNAL;
}

void PacketPlayerJournal::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);

    if (send)
        player->journalChanges.count = (unsigned int)(player->journalChanges.journalItems.size());
    else
        player->journalChanges.journalItems.clear();

    RW(player->journalChanges.count, send);

    for (unsigned int i = 0; i < player->journalChanges.count; i++)
    {
        JournalItem journalItem;

        if (send)
            journalItem = player->journalChanges.journalItems.at(i);

        RW(journalItem.type, send);
        RW(journalItem.quest, send, true);
        RW(journalItem.index, send);

        if (journalItem.type == JournalItem::ENTRY)
        {
            RW(journalItem.actorRefId, send, true);

            RW(journalItem.hasTimestamp, send);

            if (journalItem.hasTimestamp)
            {
                RW(journalItem.timestamp.daysPassed, send);
                RW(journalItem.timestamp.month, send);
                RW(journalItem.timestamp.day, send);
            }
        }

        if (!send)
            player->journalChanges.journalItems.push_back(journalItem);
    }
}
