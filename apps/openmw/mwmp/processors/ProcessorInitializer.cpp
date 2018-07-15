#include "ProcessorInitializer.hpp"

#include "PlayerProcessor.hpp"
#include "player/ProcessorChatMessage.hpp"
#include "player/ProcessorGUIMessageBox.hpp"
#include "player/ProcessorHandshake.hpp"
#include "player/ProcessorUserDisconnected.hpp"
#include "player/ProcessorGameSettings.hpp"
#include "player/ProcessorGameWeather.hpp"
#include "player/ProcessorPlayerAnimFlags.hpp"
#include "player/ProcessorPlayerAnimPlay.hpp"
#include "player/ProcessorPlayerAttack.hpp"
#include "player/ProcessorPlayerAttribute.hpp"
#include "player/ProcessorPlayerBaseInfo.hpp"
#include "player/ProcessorPlayerBehavior.hpp"
#include "player/ProcessorPlayerBook.hpp"
#include "player/ProcessorPlayerBounty.hpp"
#include "player/ProcessorPlayerCellChange.hpp"
#include "player/ProcessorPlayerCellState.hpp"
#include "player/ProcessorPlayerCharClass.hpp"
#include "player/ProcessorPlayerCharGen.hpp"
#include "player/ProcessorPlayerDeath.hpp"
#include "player/ProcessorPlayerDisposition.hpp"
#include "player/ProcessorPlayerEquipment.hpp"
#include "player/ProcessorPlayerFaction.hpp"
#include "player/ProcessorPlayerInput.hpp"
#include "player/ProcessorPlayerInventory.hpp"
#include "player/ProcessorPlayerJail.hpp"
#include "player/ProcessorPlayerJournal.hpp"
#include "player/ProcessorPlayerKillCount.hpp"
#include "player/ProcessorPlayerLevel.hpp"
#include "player/ProcessorPlayerMiscellaneous.hpp"
#include "player/ProcessorPlayerMomentum.hpp"
#include "player/ProcessorPlayerPosition.hpp"
#include "player/ProcessorPlayerQuickKeys.hpp"
#include "player/ProcessorPlayerRegionAuthority.hpp"
#include "player/ProcessorPlayerReputation.hpp"
#include "player/ProcessorPlayerRest.hpp"
#include "player/ProcessorPlayerResurrect.hpp"
#include "player/ProcessorPlayerShapeshift.hpp"
#include "player/ProcessorPlayerSkill.hpp"
#include "player/ProcessorPlayerSpeech.hpp"
#include "player/ProcessorPlayerSpellbook.hpp"
#include "player/ProcessorPlayerStatsDynamic.hpp"
#include "player/ProcessorPlayerTopic.hpp"

#include "ObjectProcessor.hpp"
#include "object/ProcessorConsoleCommand.hpp"
#include "object/ProcessorContainer.hpp"
#include "object/ProcessorDoorDestination.hpp"
#include "object/ProcessorDoorState.hpp"
#include "object/ProcessorMusicPlay.hpp"
#include "object/ProcessorObjectActivate.hpp"
#include "object/ProcessorObjectAnimPlay.hpp"
#include "object/ProcessorObjectAttach.hpp"
#include "object/ProcessorObjectCollision.hpp"
#include "object/ProcessorObjectDelete.hpp"
#include "object/ProcessorObjectLock.hpp"
#include "object/ProcessorObjectMove.hpp"
#include "object/ProcessorObjectPlace.hpp"
#include "object/ProcessorObjectReset.hpp"
#include "object/ProcessorObjectRotate.hpp"
#include "object/ProcessorObjectScale.hpp"
#include "object/ProcessorObjectSpawn.hpp"
#include "object/ProcessorObjectState.hpp"
#include "object/ProcessorObjectTrap.hpp"
#include "object/ProcessorScriptLocalShort.hpp"
#include "object/ProcessorScriptLocalFloat.hpp"
#include "object/ProcessorScriptMemberShort.hpp"
#include "object/ProcessorScriptMemberFloat.hpp"
#include "object/ProcessorScriptGlobalShort.hpp"
#include "object/ProcessorScriptGlobalFloat.hpp"
#include "object/ProcessorVideoPlay.hpp"

#include "ActorProcessor.hpp"
#include "actor/ProcessorActorAI.hpp"
#include "actor/ProcessorActorAnimFlags.hpp"
#include "actor/ProcessorActorAnimPlay.hpp"
#include "actor/ProcessorActorAttack.hpp"
#include "actor/ProcessorActorAuthority.hpp"
#include "actor/ProcessorActorCellChange.hpp"
#include "actor/ProcessorActorDeath.hpp"
#include "actor/ProcessorActorEquipment.hpp"
#include "actor/ProcessorActorInteraction.hpp"
#include "actor/ProcessorActorList.hpp"
#include "actor/ProcessorActorPosition.hpp"
#include "actor/ProcessorActorSpeech.hpp"
#include "actor/ProcessorActorStatsDynamic.hpp"
#include "actor/ProcessorActorTest.hpp"

#include "WorldstateProcessor.hpp"
#include "worldstate/ProcessorCellCreate.hpp"
#include "worldstate/ProcessorCellReplace.hpp"
#include "worldstate/ProcessorRecordDynamic.hpp"
#include "worldstate/ProcessorWorldCollisionOverride.hpp"
#include "worldstate/ProcessorWorldMap.hpp"
#include "worldstate/ProcessorWorldTime.hpp"

using namespace mwmp;

void ProcessorInitializer()
{
    PlayerProcessor::AddProcessor(new ProcessorChatMessage());
    PlayerProcessor::AddProcessor(new ProcessorGUIMessageBox());
    PlayerProcessor::AddProcessor(new ProcessorHandshake());
    PlayerProcessor::AddProcessor(new ProcessorUserDisconnected());
    PlayerProcessor::AddProcessor(new ProcessorGameSettings());
    PlayerProcessor::AddProcessor(new ProcessorGameWeather());
    PlayerProcessor::AddProcessor(new ProcessorPlayerAnimFlags());
    PlayerProcessor::AddProcessor(new ProcessorPlayerAnimPlay());
    PlayerProcessor::AddProcessor(new ProcessorPlayerAttack());
    PlayerProcessor::AddProcessor(new ProcessorPlayerAttribute());
    PlayerProcessor::AddProcessor(new ProcessorPlayerBaseInfo());
    PlayerProcessor::AddProcessor(new ProcessorPlayerBehavior());
    PlayerProcessor::AddProcessor(new ProcessorPlayerBook());
    PlayerProcessor::AddProcessor(new ProcessorPlayerBounty());
    PlayerProcessor::AddProcessor(new ProcessorPlayerCellChange());
    PlayerProcessor::AddProcessor(new ProcessorPlayerCellState());
    PlayerProcessor::AddProcessor(new ProcessorPlayerCharClass());
    PlayerProcessor::AddProcessor(new ProcessorPlayerCharGen());
    PlayerProcessor::AddProcessor(new ProcessorPlayerDeath());
    PlayerProcessor::AddProcessor(new ProcessorPlayerDisposition());
    PlayerProcessor::AddProcessor(new ProcessorPlayerEquipment());
    PlayerProcessor::AddProcessor(new ProcessorPlayerFaction());
    PlayerProcessor::AddProcessor(new ProcessorPlayerInput());
    PlayerProcessor::AddProcessor(new ProcessorPlayerInventory());
    PlayerProcessor::AddProcessor(new ProcessorPlayerJail());
    PlayerProcessor::AddProcessor(new ProcessorPlayerJournal());
    PlayerProcessor::AddProcessor(new ProcessorPlayerKillCount());
    PlayerProcessor::AddProcessor(new ProcessorPlayerLevel());
    PlayerProcessor::AddProcessor(new ProcessorPlayerMiscellaneous());
    PlayerProcessor::AddProcessor(new ProcessorPlayerMomentum());
    PlayerProcessor::AddProcessor(new ProcessorPlayerPosition());
    PlayerProcessor::AddProcessor(new ProcessorPlayerQuickKeys());
    PlayerProcessor::AddProcessor(new ProcessorPlayerRegionAuthority());
    PlayerProcessor::AddProcessor(new ProcessorPlayerReputation());
    PlayerProcessor::AddProcessor(new ProcessorPlayerRest());
    PlayerProcessor::AddProcessor(new ProcessorPlayerResurrect());
    PlayerProcessor::AddProcessor(new ProcessorPlayerShapeshift());
    PlayerProcessor::AddProcessor(new ProcessorPlayerSkill());
    PlayerProcessor::AddProcessor(new ProcessorPlayerSpeech());
    PlayerProcessor::AddProcessor(new ProcessorPlayerSpellbook());
    PlayerProcessor::AddProcessor(new ProcessorPlayerStatsDynamic());
    PlayerProcessor::AddProcessor(new ProcessorPlayerTopic());

    ObjectProcessor::AddProcessor(new ProcessorConsoleCommand());
    ObjectProcessor::AddProcessor(new ProcessorContainer());
    ObjectProcessor::AddProcessor(new ProcessorDoorDestination());
    ObjectProcessor::AddProcessor(new ProcessorDoorState());
    ObjectProcessor::AddProcessor(new ProcessorMusicPlay());
    ObjectProcessor::AddProcessor(new ProcessorObjectActivate());
    ObjectProcessor::AddProcessor(new ProcessorObjectAnimPlay());
    ObjectProcessor::AddProcessor(new ProcessorObjectAttach());
    ObjectProcessor::AddProcessor(new ProcessorObjectCollision());
    ObjectProcessor::AddProcessor(new ProcessorObjectDelete());
    ObjectProcessor::AddProcessor(new ProcessorObjectLock());
    ObjectProcessor::AddProcessor(new ProcessorObjectMove());
    ObjectProcessor::AddProcessor(new ProcessorObjectPlace());
    ObjectProcessor::AddProcessor(new ProcessorObjectReset());
    ObjectProcessor::AddProcessor(new ProcessorObjectRotate());
    ObjectProcessor::AddProcessor(new ProcessorObjectScale());
    ObjectProcessor::AddProcessor(new ProcessorObjectSpawn());
    ObjectProcessor::AddProcessor(new ProcessorObjectState());
    ObjectProcessor::AddProcessor(new ProcessorObjectTrap());
    ObjectProcessor::AddProcessor(new ProcessorScriptLocalShort());
    ObjectProcessor::AddProcessor(new ProcessorScriptLocalFloat());
    ObjectProcessor::AddProcessor(new ProcessorScriptMemberShort());
    ObjectProcessor::AddProcessor(new ProcessorScriptMemberFloat());
    ObjectProcessor::AddProcessor(new ProcessorScriptGlobalShort());
    ObjectProcessor::AddProcessor(new ProcessorScriptGlobalFloat());
    ObjectProcessor::AddProcessor(new ProcessorVideoPlay());

    ActorProcessor::AddProcessor(new ProcessorActorAI());
    ActorProcessor::AddProcessor(new ProcessorActorAnimFlags());
    ActorProcessor::AddProcessor(new ProcessorActorAnimPlay());
    ActorProcessor::AddProcessor(new ProcessorActorAttack());
    ActorProcessor::AddProcessor(new ProcessorActorAuthority());
    ActorProcessor::AddProcessor(new ProcessorActorCellChange());
    ActorProcessor::AddProcessor(new ProcessorActorDeath());
    ActorProcessor::AddProcessor(new ProcessorActorEquipment());
    ActorProcessor::AddProcessor(new ProcessorActorInteraction());
    ActorProcessor::AddProcessor(new ProcessorActorList());
    ActorProcessor::AddProcessor(new ProcessorActorPosition());
    ActorProcessor::AddProcessor(new ProcessorActorSpeech());
    ActorProcessor::AddProcessor(new ProcessorActorStatsDynamic());
    ActorProcessor::AddProcessor(new ProcessorActorTest());

    WorldstateProcessor::AddProcessor(new ProcessorCellCreate());
    WorldstateProcessor::AddProcessor(new ProcessorCellReplace());
    WorldstateProcessor::AddProcessor(new ProcessorRecordDynamic());
    WorldstateProcessor::AddProcessor(new ProcessorWorldCollisionOverride());
    WorldstateProcessor::AddProcessor(new ProcessorWorldMap());
    WorldstateProcessor::AddProcessor(new ProcessorWorldTime());
}
