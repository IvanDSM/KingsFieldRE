#include "entity.h"
#include "core/kfmtcore.h"

QString KF2::getEntityMeshName(const KF2::EntityMeshID entityMeshId)
{
    switch (entityMeshId)
    {
        case EntityMeshID::AlHunt: return QStringLiteral("AlHunt");
        case EntityMeshID::Archer: return QStringLiteral("Archer");
        case EntityMeshID::Baltail: return QStringLiteral("Baltail");
        case EntityMeshID::BaltailTail: return QStringLiteral("BaltailTail");
        case EntityMeshID::Billent: return QStringLiteral("Billent");
        case EntityMeshID::Bitt: return QStringLiteral("Bitt");
        case EntityMeshID::Cable: return QStringLiteral("Cable");
        case EntityMeshID::CellfyFoss: return QStringLiteral("CellfyFoss");
        case EntityMeshID::CellfyFoss2: return QStringLiteral("CellfyFoss2");
        case EntityMeshID::CliffLore: return QStringLiteral("CliffLore");
        case EntityMeshID::CopperKnight: return QStringLiteral("CopperKnight");
        case EntityMeshID::DalfVice: return QStringLiteral("DalfVice");
        case EntityMeshID::DavidTabler: return QStringLiteral("DavidTabler");
        case EntityMeshID::DemonLord: return QStringLiteral("DemonLord");
        case EntityMeshID::DiasBagil: return QStringLiteral("DiasBagil");
        case EntityMeshID::DragonGrass: return QStringLiteral("DragonGrass");
        case EntityMeshID::EarnestClyde: return QStringLiteral("EarnestClyde");
        case EntityMeshID::EarnestClydeSitting: return QStringLiteral("EarnestClydeSitting");
        case EntityMeshID::EarthElemental: return QStringLiteral("EarthElemental");
        case EntityMeshID::FaiFadlin: return QStringLiteral("FaiFadlin");
        case EntityMeshID::FireElemental: return QStringLiteral("FireElemental");
        case EntityMeshID::Ghost: return QStringLiteral("Ghost");
        case EntityMeshID::GiantTermite: return QStringLiteral("GiantTermite");
        case EntityMeshID::GigiBudwell: return QStringLiteral("GigiBudwell");
        case EntityMeshID::GigiBudwellWatering: return QStringLiteral("GigiBudwellWatering");
        case EntityMeshID::GreenSlime: return QStringLiteral("GreenSlime");
        case EntityMeshID::GreenSlime2: return QStringLiteral("GreenSlime2");
        case EntityMeshID::GreenSlime3: return QStringLiteral("GreenSlime3");
        case EntityMeshID::GreenSlime4: return QStringLiteral("GreenSlime4");
        case EntityMeshID::GreenSlimeDeath: return QStringLiteral("GreenSlimeDeath");
        case EntityMeshID::GreenSlimeDeath2: return QStringLiteral("GreenSlimeDeath2");
        case EntityMeshID::GreenSlimeDeath3: return QStringLiteral("GreenSlimeDeath3");
        case EntityMeshID::GreenSlimeDeath4: return QStringLiteral("GreenSlimeDeath4");
        case EntityMeshID::Guyra: return QStringLiteral("Guyra");
        case EntityMeshID::HarrisCarvitto: return QStringLiteral("HarrisCarvitto");
        case EntityMeshID::HeadEater: return QStringLiteral("HeadEater");
        case EntityMeshID::JoseHarven: return QStringLiteral("JoseHarven");
        case EntityMeshID::JoseHavenDeath: return QStringLiteral("JoseHavenDeath");
        case EntityMeshID::JoseHavenDeath2: return QStringLiteral("JoseHavenDeath2");
        case EntityMeshID::Kald: return QStringLiteral("Kald");
        case EntityMeshID::KarenShore: return QStringLiteral("KarenShore");
        case EntityMeshID::KarenShoreChair: return QStringLiteral("KarenShoreChair");
        case EntityMeshID::KehlHunt: return QStringLiteral("KehlHunt");
        case EntityMeshID::KehlHunt2: return QStringLiteral("KehlHunt2");
        case EntityMeshID::KrakenBody: return QStringLiteral("KrakenBody");
        case EntityMeshID::KrakenHead: return QStringLiteral("KrakenHead");
        case EntityMeshID::KrolaAmgun: return QStringLiteral("KrolaAmgun");
        case EntityMeshID::KrolaAmgunCooking: return QStringLiteral("KrolaAmgunCooking");
        case EntityMeshID::LeonShore: return QStringLiteral("LeonShore");
        case EntityMeshID::LeonShoreWatering: return QStringLiteral("LeonShoreWatering");
        case EntityMeshID::LogStalker: return QStringLiteral("LogStalker");
        case EntityMeshID::MagesCandlesticks: return QStringLiteral("MagesCandlesticks");
        case EntityMeshID::MarkWozz: return QStringLiteral("MarkWozz");
        case EntityMeshID::MechaDemonLord: return QStringLiteral("MechaDemonLord");
        case EntityMeshID::MechaReik: return QStringLiteral("MechaReik");
        case EntityMeshID::MechaTermite: return QStringLiteral("MechaTermite");
        case EntityMeshID::Meryl: return QStringLiteral("Meryl");
        case EntityMeshID::Miria: return QStringLiteral("Miria");
        case EntityMeshID::Mogle: return QStringLiteral("Mogle");
        case EntityMeshID::NolaBagil: return QStringLiteral("NolaBagil");
        case EntityMeshID::None: return QStringLiteral("None");
        case EntityMeshID::PoisonSlime: return QStringLiteral("PoisonSlime");
        case EntityMeshID::Psythe: return QStringLiteral("Psythe");
        case EntityMeshID::RaddBilheim: return QStringLiteral("RaddBilheim");
        case EntityMeshID::RaffyFoss: return QStringLiteral("RaffyFoss");
        case EntityMeshID::RandFerrer: return QStringLiteral("RandFerrer");
        case EntityMeshID::RedSpikeBall: return QStringLiteral("RedSpikeBall");
        case EntityMeshID::Refma: return QStringLiteral("Refma");
        case EntityMeshID::Refma2: return QStringLiteral("Refma2");
        case EntityMeshID::Reik: return QStringLiteral("Reik");
        case EntityMeshID::SKnight: return QStringLiteral("SKnight");
        case EntityMeshID::SaintGrave: return QStringLiteral("SaintGrave");
        case EntityMeshID::Salamander: return QStringLiteral("Salamander");
        case EntityMeshID::SandlerAmgun: return QStringLiteral("SandlerAmgun");
        case EntityMeshID::SandlerAmgun2: return QStringLiteral("SandlerAmgun2");
        case EntityMeshID::Sigill: return QStringLiteral("Sigill");
        case EntityMeshID::Skeleton: return QStringLiteral("Skeleton");
        case EntityMeshID::SkeletonOfOneEyedGiant: return QStringLiteral("SkeletonOfOneEyedGiant");
        case EntityMeshID::Soldier: return QStringLiteral("Soldier");
        case EntityMeshID::StingFly: return QStringLiteral("StingFly");
        case EntityMeshID::StingFlyTail: return QStringLiteral("StingFlyTail");
        case EntityMeshID::Tarn: return QStringLiteral("Tarn");
        case EntityMeshID::TeoBudwell: return QStringLiteral("TeoBudwell");
        case EntityMeshID::TeoBudwellMowing: return QStringLiteral("TeoBudwellMowing");
        case EntityMeshID::TeoBudwellWithGigi: return QStringLiteral("TeoBudwellWithGigi");
        case EntityMeshID::Termite: return QStringLiteral("Termite");
        case EntityMeshID::ThePictureOfAKing: return QStringLiteral("ThePictureOfAKing");
        case EntityMeshID::Transparent: return QStringLiteral("Transparent");
        case EntityMeshID::Unused: return QStringLiteral("Unused");
        case EntityMeshID::Unused10: return QStringLiteral("Unused10");
        case EntityMeshID::Unused11: return QStringLiteral("Unused11");
        case EntityMeshID::Unused12: return QStringLiteral("Unused12");
        case EntityMeshID::Unused13: return QStringLiteral("Unused13");
        case EntityMeshID::Unused14: return QStringLiteral("Unused14");
        case EntityMeshID::Unused15: return QStringLiteral("Unused15");
        case EntityMeshID::Unused16: return QStringLiteral("Unused16");
        case EntityMeshID::Unused17: return QStringLiteral("Unused17");
        case EntityMeshID::Unused18: return QStringLiteral("Unused18");
        case EntityMeshID::Unused19: return QStringLiteral("Unused19");
        case EntityMeshID::Unused2: return QStringLiteral("Unused2");
        case EntityMeshID::Unused20: return QStringLiteral("Unused20");
        case EntityMeshID::Unused21: return QStringLiteral("Unused21");
        case EntityMeshID::Unused22: return QStringLiteral("Unused22");
        case EntityMeshID::Unused23: return QStringLiteral("Unused23");
        case EntityMeshID::Unused24: return QStringLiteral("Unused24");
        case EntityMeshID::Unused3: return QStringLiteral("Unused3");
        case EntityMeshID::Unused4: return QStringLiteral("Unused4");
        case EntityMeshID::Unused5: return QStringLiteral("Unused5");
        case EntityMeshID::Unused6: return QStringLiteral("Unused6");
        case EntityMeshID::Unused7: return QStringLiteral("Unused7");
        case EntityMeshID::Unused8: return QStringLiteral("Unused8");
        case EntityMeshID::Unused9: return QStringLiteral("Unused9");
        default: return unknownString;
    }
}

QString KF2::getEntityStateIDName(const KF2::EntityStateID entityStateId)
{
    switch (entityStateId)
    {
        case EntityStateID::FlyingAttackMaybe: return QStringLiteral("Flying Attack?");
        case EntityStateID::FlyingWander: return QStringLiteral("Flying Wander");
        case EntityStateID::MagicAttack: return QStringLiteral("Magic Attack");
        case EntityStateID::ApproachingPlayer: return QStringLiteral("Approaching Player");
        case EntityStateID::Wander: return QStringLiteral("Wander");
        case EntityStateID::MeleeAttack: return QStringLiteral("Melee Attack");
        case EntityStateID::TakingDamage: return QStringLiteral("Taking Damage");
        case EntityStateID::None: return QStringLiteral("None");
        case EntityStateID::MeleeAttack3: return QStringLiteral("Melee Attack 3");
        case EntityStateID::MeleeAttack2: return QStringLiteral("Melee Attack 2");
        case EntityStateID::Idle: return QStringLiteral("Idle");
        case EntityStateID::Dialogue: return QStringLiteral("Dialogue");
        case EntityStateID::Dying: return QStringLiteral("Dying");
        default: return unknownString;
    }
}
