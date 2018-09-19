#ifndef OPENMW_MECHANICSHELPER_HPP
#define OPENMW_MECHANICSHELPER_HPP

#include <components/openmw-mp/Base/BaseStructs.hpp>

#include "../mwworld/containerstore.hpp"

#include <osg/Vec3f>


namespace MechanicsHelper
{
    osg::Vec3f getLinearInterpolation(osg::Vec3f start, osg::Vec3f end, float percent);
    ESM::Position getPositionFromVector(osg::Vec3f vector);

    void spawnLeveledCreatures(MWWorld::CellStore* cellStore);

    bool isUsingRangedWeapon(const MWWorld::Ptr& ptr);

    mwmp::Attack *getLocalAttack(const MWWorld::Ptr& ptr);
    mwmp::Attack *getDedicatedAttack(const MWWorld::Ptr& ptr);

    MWWorld::Ptr getPlayerPtr(const mwmp::Target& target);

    mwmp::Target getTarget(const MWWorld::Ptr& ptr);
    void clearTarget(mwmp::Target& target);
    bool isEmptyTarget(const mwmp::Target& target);

    void assignAttackTarget(mwmp::Attack* attack, const MWWorld::Ptr& target);
    void resetAttack(mwmp::Attack* attack);

    bool getSpellSuccess(std::string spellId, const MWWorld::Ptr& caster);

    void processAttack(mwmp::Attack attack, const MWWorld::Ptr& attacker);

    bool doesEffectListContainEffect(const ESM::EffectList& effectList, short effectId, short attributeId = -1, short skillId = -1);
    void unequipItemsByEffect(const MWWorld::Ptr& ptr, short enchantmentType, short effectId, short attributeId = -1, short skillId = -1);

    MWWorld::Ptr getItemPtrFromStore(const mwmp::Item& item, MWWorld::ContainerStore& store);
}


#endif //OPENMW_MECHANICSHELPER_HPP
