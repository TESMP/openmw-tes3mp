#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketPlayerSpellbook.hpp"

using namespace std;
using namespace mwmp;

PacketPlayerSpellbook::PacketPlayerSpellbook(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_SPELLBOOK;
}

void PacketPlayerSpellbook::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);

    RW(player->spellbookChanges.action, send);

    if (send)
        player->spellbookChanges.count = (unsigned int) (player->spellbookChanges.spells.size());
    else
        player->spellbookChanges.spells.clear();

    RW(player->spellbookChanges.count, send);

    for (unsigned int i = 0; i < player->spellbookChanges.count; i++)
    {
        ESM::Spell spell;

        if (send)
            spell = player->spellbookChanges.spells.at(i);

        RW(spell.mId, send, true);

        if (!send)
            player->spellbookChanges.spells.push_back(spell);
    }

}
