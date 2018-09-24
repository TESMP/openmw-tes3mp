#include "weaponanimation.hpp"

#include <osg/MatrixTransform>

#include <components/resource/resourcesystem.hpp>
#include <components/resource/scenemanager.hpp>

/*
    Start of tes3mp addition

    Include additional headers for multiplayer purposes
*/
#include "../mwmp/MechanicsHelper.hpp"
/*
    End of tes3mp addition
*/

#include "../mwbase/world.hpp"
#include "../mwbase/environment.hpp"
#include "../mwbase/soundmanager.hpp"

#include "../mwworld/inventorystore.hpp"
#include "../mwworld/class.hpp"
#include "../mwworld/esmstore.hpp"

#include "../mwmechanics/creaturestats.hpp"
#include "../mwmechanics/combat.hpp"

#include "animation.hpp"
#include "rotatecontroller.hpp"

namespace MWRender
{

float WeaponAnimationTime::getValue(osg::NodeVisitor*)
{
    if (mWeaponGroup.empty())
        return 0;

    float current = mAnimation->getCurrentTime(mWeaponGroup);
    if (current == -1)
        return 0;
    return current - mStartTime;
}

void WeaponAnimationTime::setGroup(const std::string &group)
{
    mWeaponGroup = group;
    mStartTime = mAnimation->getStartTime(mWeaponGroup);
}

void WeaponAnimationTime::updateStartTime()
{
    setGroup(mWeaponGroup);
}

WeaponAnimation::WeaponAnimation()
    : mPitchFactor(0)
{
}

WeaponAnimation::~WeaponAnimation()
{

}

void WeaponAnimation::attachArrow(MWWorld::Ptr actor)
{
    const MWWorld::InventoryStore& inv = actor.getClass().getInventoryStore(actor);
    MWWorld::ConstContainerStoreIterator weaponSlot = inv.getSlot(MWWorld::InventoryStore::Slot_CarriedRight);
    if (weaponSlot == inv.end())
        return;
    if (weaponSlot->getTypeName() != typeid(ESM::Weapon).name())
        return;
    int weaponType = weaponSlot->get<ESM::Weapon>()->mBase->mData.mType;
    if (weaponType == ESM::Weapon::MarksmanThrown)
    {
        std::string soundid = weaponSlot->getClass().getUpSoundId(*weaponSlot);
        if(!soundid.empty())
        {
            MWBase::SoundManager *sndMgr = MWBase::Environment::get().getSoundManager();
            sndMgr->playSound3D(actor, soundid, 1.0f, 1.0f);
        }
        showWeapon(true);
    }
    else if (weaponType == ESM::Weapon::MarksmanBow || weaponType == ESM::Weapon::MarksmanCrossbow)
    {
        osg::Group* parent = getArrowBone();
        if (!parent)
            return;

        MWWorld::ConstContainerStoreIterator ammo = inv.getSlot(MWWorld::InventoryStore::Slot_Ammunition);
        if (ammo == inv.end())
            return;
        std::string model = ammo->getClass().getModel(*ammo);

        osg::ref_ptr<osg::Node> arrow = getResourceSystem()->getSceneManager()->getInstance(model, parent);

        mAmmunition = PartHolderPtr(new PartHolder(arrow));
    }
}

void WeaponAnimation::releaseArrow(MWWorld::Ptr actor, float attackStrength)
{
    MWWorld::InventoryStore& inv = actor.getClass().getInventoryStore(actor);
    MWWorld::ContainerStoreIterator weapon = inv.getSlot(MWWorld::InventoryStore::Slot_CarriedRight);
    if (weapon == inv.end())
        return;
    if (weapon->getTypeName() != typeid(ESM::Weapon).name())
        return;

    /*
        Start of tes3mp addition

        If this is an attack by a LocalPlayer or LocalActor, record its attackStrength and
        rangedWeaponId and prepare an attack packet for sending.

        Unlike melee attacks, ranged attacks require the weapon and ammo IDs to be recorded
        because players and actors can have multiple projectiles in the air at the same time.

        If it's an attack by a DedicatedPlayer or DedicatedActor, apply the attackStrength
        from their latest attack packet.
    */
    mwmp::Attack *localAttack = MechanicsHelper::getLocalAttack(actor);

    if (localAttack)
    {
        localAttack->attackStrength = attackStrength;
        localAttack->rangedWeaponId = weapon->getCellRef().getRefId();
        localAttack->shouldSend = true;
    }
    else
    {
        mwmp::Attack *dedicatedAttack = MechanicsHelper::getDedicatedAttack(actor);

        if (dedicatedAttack)
            attackStrength = dedicatedAttack->attackStrength;
    }
    /*
        End of tes3mp addition
    */

    // The orientation of the launched projectile. Always the same as the actor orientation, even if the ArrowBone's orientation dictates otherwise.
    osg::Quat orient = osg::Quat(actor.getRefData().getPosition().rot[0], osg::Vec3f(-1,0,0))
            * osg::Quat(actor.getRefData().getPosition().rot[2], osg::Vec3f(0,0,-1));

    const MWWorld::Store<ESM::GameSetting> &gmst =
        MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>();

    MWMechanics::applyFatigueLoss(actor, *weapon, attackStrength);

    if (weapon->get<ESM::Weapon>()->mBase->mData.mType == ESM::Weapon::MarksmanThrown)
    {
        /*
            Start of tes3mp addition

            If this is a local attack, clear the rangedAmmoId used for it
        */
        if (localAttack)
            localAttack->rangedAmmoId = "";
        /*
            End of tes3mp addition
        */

        // Thrown weapons get detached now
        osg::Node* weaponNode = getWeaponNode();
        if (!weaponNode)
            return;
        osg::NodePathList nodepaths = weaponNode->getParentalNodePaths();
        if (nodepaths.empty())
            return;
        osg::Vec3f launchPos = osg::computeLocalToWorld(nodepaths[0]).getTrans();

        float fThrownWeaponMinSpeed = gmst.find("fThrownWeaponMinSpeed")->getFloat();
        float fThrownWeaponMaxSpeed = gmst.find("fThrownWeaponMaxSpeed")->getFloat();
        float speed = fThrownWeaponMinSpeed + (fThrownWeaponMaxSpeed - fThrownWeaponMinSpeed) * attackStrength;

        MWBase::Environment::get().getWorld()->launchProjectile(actor, *weapon, launchPos, orient, *weapon, speed, attackStrength);

        showWeapon(false);

        inv.remove(*weapon, 1, actor);
    }
    else
    {
        // With bows and crossbows only the used arrow/bolt gets detached
        MWWorld::ContainerStoreIterator ammo = inv.getSlot(MWWorld::InventoryStore::Slot_Ammunition);
        if (ammo == inv.end())
            return;

        if (!mAmmunition)
            return;

        /*
            Start of tes3mp addition

            If this is a local attack, record the rangedAmmoId used for it
        */
        if (localAttack)
            localAttack->rangedAmmoId = ammo->getCellRef().getRefId();
        /*
            End of tes3mp addition
        */

        osg::ref_ptr<osg::Node> ammoNode = mAmmunition->getNode();
        osg::NodePathList nodepaths = ammoNode->getParentalNodePaths();
        if (nodepaths.empty())
            return;
        osg::Vec3f launchPos = osg::computeLocalToWorld(nodepaths[0]).getTrans();

        float fProjectileMinSpeed = gmst.find("fProjectileMinSpeed")->getFloat();
        float fProjectileMaxSpeed = gmst.find("fProjectileMaxSpeed")->getFloat();
        float speed = fProjectileMinSpeed + (fProjectileMaxSpeed - fProjectileMinSpeed) * attackStrength;

        MWBase::Environment::get().getWorld()->launchProjectile(actor, *ammo, launchPos, orient, *weapon, speed, attackStrength);

        inv.remove(*ammo, 1, actor);
        mAmmunition.reset();
    }
}

void WeaponAnimation::addControllers(const std::map<std::string, osg::ref_ptr<osg::MatrixTransform> >& nodes,
                                     std::multimap<osg::ref_ptr<osg::Node>, osg::ref_ptr<osg::NodeCallback> > &map, osg::Node* objectRoot)
{
    for (int i=0; i<2; ++i)
    {
        mSpineControllers[i] = NULL;

        std::map<std::string, osg::ref_ptr<osg::MatrixTransform> >::const_iterator found = nodes.find(i == 0 ? "bip01 spine1" : "bip01 spine2");
        if (found != nodes.end())
        {
            osg::Node* node = found->second;
            mSpineControllers[i] = new RotateController(objectRoot);
            node->addUpdateCallback(mSpineControllers[i]);
            map.insert(std::make_pair(node, mSpineControllers[i]));
        }
    }
}

void WeaponAnimation::deleteControllers()
{
    for (int i=0; i<2; ++i)
        mSpineControllers[i] = NULL;
}

void WeaponAnimation::configureControllers(float characterPitchRadians)
{
    if (mPitchFactor == 0.f || characterPitchRadians == 0.f)
    {
        setControllerEnabled(false);
        return;
    }

    float pitch = characterPitchRadians * mPitchFactor;
    osg::Quat rotate (pitch/2, osg::Vec3f(-1,0,0));
    setControllerRotate(rotate);
    setControllerEnabled(true);
}

void WeaponAnimation::setControllerRotate(const osg::Quat& rotate)
{
    for (int i=0; i<2; ++i)
        if (mSpineControllers[i])
            mSpineControllers[i]->setRotate(rotate);
}

void WeaponAnimation::setControllerEnabled(bool enabled)
{
    for (int i=0; i<2; ++i)
        if (mSpineControllers[i])
            mSpineControllers[i]->setEnabled(enabled);
}

}
