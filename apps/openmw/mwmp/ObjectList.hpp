#ifndef OPENMW_OBJECTLIST_HPP
#define OPENMW_OBJECTLIST_HPP

#include <components/openmw-mp/Base/BaseObject.hpp>
#include "../mwworld/cellstore.hpp"
#include <RakNetTypes.h>

namespace mwmp
{
    class Networking;
    class ObjectList : public BaseObjectList
    {
    public:

        ObjectList();
        virtual ~ObjectList();

        void reset();

        void addObject(BaseObject baseObject);
        BaseObject getBaseObject(const MWWorld::Ptr& ptr);
        void addContainerItem(mwmp::BaseObject& baseObject, const MWWorld::Ptr& itemPtr, int actionCount);
        void addEntireContainer(const MWWorld::Ptr& ptr);

        void editContainers(MWWorld::CellStore* cellStore);

        void activateObjects(MWWorld::CellStore* cellStore);
        void placeObjects(MWWorld::CellStore* cellStore);
        void spawnObjects(MWWorld::CellStore* cellStore);
        void deleteObjects(MWWorld::CellStore* cellStore);
        void lockObjects(MWWorld::CellStore* cellStore);
        void triggerTrapObjects(MWWorld::CellStore* cellStore);
        void scaleObjects(MWWorld::CellStore* cellStore);
        void setObjectStates(MWWorld::CellStore* cellStore);
        void moveObjects(MWWorld::CellStore* cellStore);
        void rotateObjects(MWWorld::CellStore* cellStore);
        void animateObjects(MWWorld::CellStore* cellStore);
        void activateDoors(MWWorld::CellStore* cellStore);
        void setDoorDestinations(MWWorld::CellStore* cellStore);
        void runConsoleCommands(MWWorld::CellStore* cellStore);

        void setLocalShorts(MWWorld::CellStore* cellStore);
        void setLocalFloats(MWWorld::CellStore* cellStore);
        void setMemberShorts();
        void setGlobalShorts();

        void playMusic();
        void playVideo();

        void addAllContainers(MWWorld::CellStore* cellStore);
        void addRequestedContainers(MWWorld::CellStore* cellStore, const std::vector<BaseObject>& requestObjects);

        void addObjectActivate(const MWWorld::Ptr& ptr, const MWWorld::Ptr& activatingActor);
        void addObjectPlace(const MWWorld::Ptr& ptr, bool droppedByPlayer = false);
        void addObjectSpawn(const MWWorld::Ptr& ptr);
        void addObjectSpawn(const MWWorld::Ptr& ptr, const MWWorld::Ptr& master, float spawnDuration);
        void addObjectDelete(const MWWorld::Ptr& ptr);
        void addObjectLock(const MWWorld::Ptr& ptr, int lockLevel);
        void addObjectTrap(const MWWorld::Ptr& ptr, const ESM::Position& pos, bool isDisarmed);
        void addObjectScale(const MWWorld::Ptr& ptr, float scale);
        void addObjectState(const MWWorld::Ptr& ptr, bool objectState);
        void addObjectAnimPlay(const MWWorld::Ptr& ptr, std::string group, int mode);

        void addDoorState(const MWWorld::Ptr& ptr, int state);
        void addMusicPlay(std::string filename);
        void addVideoPlay(std::string filename, bool allowSkipping);
        void addScriptLocalShort(const MWWorld::Ptr& ptr, int index, int shortVal);
        void addScriptLocalFloat(const MWWorld::Ptr& ptr, int index, float floatVal);
        void addScriptMemberShort(std::string refId, int index, int shortVal);
        void addScriptGlobalShort(std::string varName, int shortVal);

        void sendObjectActivate();
        void sendObjectPlace();
        void sendObjectSpawn();
        void sendObjectDelete();
        void sendObjectLock();
        void sendObjectTrap();
        void sendObjectScale();
        void sendObjectState();
        void sendObjectAnimPlay();
        void sendDoorState();
        void sendMusicPlay();
        void sendVideoPlay();
        void sendScriptLocalShort();
        void sendScriptLocalFloat();
        void sendScriptMemberShort();
        void sendScriptGlobalShort();
        void sendContainer();

    private:
        Networking *getNetworking();

    };
}

#endif //OPENMW_OBJECTLIST_HPP
