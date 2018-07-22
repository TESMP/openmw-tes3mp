#include "summoning.hpp"

#include <iostream>

/*
    Start of tes3mp addition

    Include additional headers for multiplayer purposes
*/
#include <components/openmw-mp/Log.hpp>
#include "../mwmechanics/creaturestats.hpp"
#include "../mwmp/Main.hpp"
#include "../mwmp/Networking.hpp"
#include "../mwmp/CellController.hpp"
#include "../mwmp/ObjectList.hpp"
/*
    End of tes3mp addition
*/

#include "../mwbase/environment.hpp"
#include "../mwbase/world.hpp"
#include "../mwbase/mechanicsmanager.hpp"

#include "../mwworld/esmstore.hpp"
#include "../mwworld/class.hpp"
#include "../mwworld/manualref.hpp"
#include "../mwworld/inventorystore.hpp"

#include "../mwrender/animation.hpp"

#include "spellcasting.hpp"
#include "creaturestats.hpp"
#include "aifollow.hpp"

namespace MWMechanics
{

    UpdateSummonedCreatures::UpdateSummonedCreatures(const MWWorld::Ptr &actor)
        : mActor(actor)
    {

    }

    UpdateSummonedCreatures::~UpdateSummonedCreatures()
    {
    }

    void UpdateSummonedCreatures::visit(EffectKey key, const std::string &sourceName, const std::string &sourceId, int casterActorId, float magnitude, float remainingTime, float totalTime)
    {
        if (isSummoningEffect(key.mId) && magnitude > 0)
        {
            mActiveEffects.insert(std::make_pair(key.mId, sourceId));
        }
    }

    void UpdateSummonedCreatures::process(bool cleanup)
    {
        MWMechanics::CreatureStats& creatureStats = mActor.getClass().getCreatureStats(mActor);
        std::map<CreatureStats::SummonKey, int>& creatureMap = creatureStats.getSummonedCreatureMap();

        for (std::set<std::pair<int, std::string> >::iterator it = mActiveEffects.begin(); it != mActiveEffects.end(); ++it)
        {
            bool found = creatureMap.find(std::make_pair(it->first, it->second)) != creatureMap.end();
            if (!found)
            {
                std::string creatureID = getSummonedCreature(it->first);
                if (!creatureID.empty())
                {
                    int creatureActorId = -1;

                    /*
                        Start of tes3mp change (major)

                        Send an ID_OBJECT_SPAWN packet every time a creature is summoned in a cell that we hold
                        authority over, then delete the creature and wait for the server to send it back with a
                        unique mpNum of its own

                        Comment out most of the code here except for the actual placement of the Ptr and the
                        creatureActorId insertion into the creatureMap
                    */
                    try
                    {
                        MWWorld::ManualRef ref(MWBase::Environment::get().getWorld()->getStore(), creatureID, 1);

                        /*
                        MWMechanics::CreatureStats& summonedCreatureStats = ref.getPtr().getClass().getCreatureStats(ref.getPtr());

                        // Make the summoned creature follow its master and help in fights
                        AiFollow package(mActor);
                        summonedCreatureStats.getAiSequence().stack(package, ref.getPtr());
                        creatureActorId = summonedCreatureStats.getActorId();
                        */

                        MWWorld::Ptr placed = MWBase::Environment::get().getWorld()->safePlaceObject(ref.getPtr(), mActor, mActor.getCell(), 0, 120.f);

                        /*
                        MWRender::Animation* anim = MWBase::Environment::get().getWorld()->getAnimation(placed);
                        if (anim)
                        {
                            const ESM::Static* fx = MWBase::Environment::get().getWorld()->getStore().get<ESM::Static>()
                                    .search("VFX_Summon_Start");
                            if (fx)
                                anim->addEffect("meshes\\" + fx->mModel, -1, false);
                        }
                        */

                        if (mwmp::Main::get().getCellController()->hasLocalAuthority(*placed.getCell()->getCell()))
                        {
                            mwmp::ObjectList *objectList = mwmp::Main::get().getNetworking()->getObjectList();
                            objectList->reset();
                            objectList->packetOrigin = mwmp::CLIENT_GAMEPLAY;

                            MWMechanics::CreatureStats *actorCreatureStats = &mActor.getClass().getCreatureStats(mActor);

                            objectList->addObjectSpawn(placed, mActor, actorCreatureStats->getActiveSpells().getEffectDuration(it->first));
                            objectList->sendObjectSpawn();
                        }

                        MWBase::Environment::get().getWorld()->deleteObject(placed);
                    }
                    catch (std::exception& e)
                    {
                        std::cerr << "Failed to spawn summoned creature: " << e.what() << std::endl;
                        // still insert into creatureMap so we don't try to spawn again every frame, that would spam the warning log
                    }

                    creatureMap.insert(std::make_pair(*it, creatureActorId));
                    /*
                        End of tes3mp change (major)
                    */
                }
            }
        }

        // Update summon effects
        for (std::map<CreatureStats::SummonKey, int>::iterator it = creatureMap.begin(); it != creatureMap.end(); )
        {
            bool found = mActiveEffects.find(it->first) != mActiveEffects.end();
            if (!found)
            {
                // Effect has ended
                MWBase::Environment::get().getMechanicsManager()->cleanupSummonedCreature(mActor, it->second);
                creatureMap.erase(it++);
                continue;
            }
            ++it;
        }

        std::vector<int>& graveyard = creatureStats.getSummonedCreatureGraveyard();
        for (std::vector<int>::iterator it = graveyard.begin(); it != graveyard.end(); )
        {
            MWWorld::Ptr ptr = MWBase::Environment::get().getWorld()->searchPtrViaActorId(*it);
            if (!ptr.isEmpty())
            {
                it = graveyard.erase(it);

                const ESM::Static* fx = MWBase::Environment::get().getWorld()->getStore().get<ESM::Static>()
                        .search("VFX_Summon_End");
                if (fx)
                    MWBase::Environment::get().getWorld()->spawnEffect("meshes\\" + fx->mModel,
                        "", ptr.getRefData().getPosition().asVec3());

                MWBase::Environment::get().getWorld()->deleteObject(ptr);

                /*
                    Start of tes3mp addition

                    Send an ID_OBJECT_DELETE packet every time a summoned creature despawns
                */
                mwmp::ObjectList *objectList = mwmp::Main::get().getNetworking()->getObjectList();
                objectList->reset();
                objectList->packetOrigin = mwmp::CLIENT_GAMEPLAY;
                objectList->addObjectDelete(ptr);
                objectList->sendObjectDelete();
                /*
                    End of tes3mp addition
                */
            }
            else
                ++it;
        }

        if (!cleanup)
            return;

        for (std::map<CreatureStats::SummonKey, int>::iterator it = creatureMap.begin(); it != creatureMap.end(); )
        {
            /*
                Start of tes3mp addition

                If we're iterating over a SummonKey matching an actorId of -1, that means it's a summon
                yet to be sent back to us by the server and we should skip over it, because deleting it
                here would mean it becomes just a regular creature when the server sends it back to us
            */
            if (it->second == -1)
            {
                ++it;
                continue;
            }
            /*
                End of tes3mp addition
            */

            MWWorld::Ptr ptr = MWBase::Environment::get().getWorld()->searchPtrViaActorId(it->second);
            if (ptr.isEmpty() || (ptr.getClass().getCreatureStats(ptr).isDead() && ptr.getClass().getCreatureStats(ptr).isDeathAnimationFinished()))
            {
                // Purge the magic effect so a new creature can be summoned if desired
                creatureStats.getActiveSpells().purgeEffect(it->first.first, it->first.second);
                if (mActor.getClass().hasInventoryStore(mActor))
                    mActor.getClass().getInventoryStore(mActor).purgeEffect(it->first.first, it->first.second);

                MWBase::Environment::get().getMechanicsManager()->cleanupSummonedCreature(mActor, it->second);
                creatureMap.erase(it++);
            }
            else
                ++it;
        }
    }

}
