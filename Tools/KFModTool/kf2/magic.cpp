#include "magic.h"
#include "core/kfmtcore.h"

QString KF2::getMagicIDName(const KF2::MagicID magicId)
{
    switch (magicId)
    {
        case MagicID::ArcherArrow: return QStringLiteral("ArcherArrow");
        case MagicID::ArcherParalyzeArrow: return QStringLiteral("ArcherParalyzeArrow");
        case MagicID::Breath: return QStringLiteral("Breath");
        case MagicID::DarkSlayerMagicA: return QStringLiteral("DarkSlayerMagicA");
        case MagicID::DarkSlayerMagicB: return QStringLiteral("DarkSlayerMagicB");
        case MagicID::Dispoison: return QStringLiteral("Dispoison");
        case MagicID::DoubleFireball: return QStringLiteral("DoubleFireball");
        case MagicID::EarthHeal: return QStringLiteral("EarthHeal");
        case MagicID::EarthWave: return QStringLiteral("EarthWave");
        case MagicID::EnemyEarthMagic: return QStringLiteral("EnemyEarthMagic");
        case MagicID::EnemyHomingEarthMagic: return QStringLiteral("EnemyHomingEarthMagic");
        case MagicID::EnemyLightningVolt: return QStringLiteral("EnemyLightningVolt");
        case MagicID::FireBall: return QStringLiteral("FireBall");
        case MagicID::FireStorm: return QStringLiteral("FireStorm");
        case MagicID::FireWall: return QStringLiteral("FireWall");
        case MagicID::Flame: return QStringLiteral("Flame");
        case MagicID::FlameSwordMagicA: return QStringLiteral("FlameSwordMagicA");
        case MagicID::FlameSwordMagicB: return QStringLiteral("FlameSwordMagicB");
        case MagicID::Flash: return QStringLiteral("Flash");
        case MagicID::Freeze: return QStringLiteral("Freeze");
        case MagicID::IceBladeMagicA: return QStringLiteral("IceBladeMagicA");
        case MagicID::IceBladeMagicB: return QStringLiteral("IceBladeMagicB");
        case MagicID::IceStorm: return QStringLiteral("IceStorm");
        case MagicID::Light: return QStringLiteral("Light");
        case MagicID::LightningVolt: return QStringLiteral("LightningVolt");
        case MagicID::Meteor: return QStringLiteral("Meteor");
        case MagicID::MissileShield: return QStringLiteral("MissileShield");
        case MagicID::MoonlightSwordMagicA: return QStringLiteral("MoonlightSwordMagicA");
        case MagicID::MoonlightSwordMagicB: return QStringLiteral("MoonlightSwordMagicB");
        case MagicID::None: return QStringLiteral("None");
        case MagicID::PsytheCurseOrb: return QStringLiteral("PsytheCurseOrb");
        case MagicID::ResistFire: return QStringLiteral("ResistFire");
        case MagicID::SKnightPoisonBreath: return QStringLiteral("SKnightPoisonBreath");
        case MagicID::Seath: return QStringLiteral("Seath");
        case MagicID::SeathsSwordMagicA: return QStringLiteral("SeathsSwordMagicA");
        case MagicID::ShidenMagicA: return QStringLiteral("ShidenMagicA");
        case MagicID::ShidenMagicB: return QStringLiteral("ShidenMagicB");
        case MagicID::SpiderSwordMagicA: return QStringLiteral("SpiderSwordMagicA");
        case MagicID::SpiderSwordMagicB: return QStringLiteral("SpiderSwordMagicB");
        case MagicID::Stone: return QStringLiteral("Stone");
        case MagicID::TarnWindMagic: return QStringLiteral("TarnWindMagic");
        case MagicID::WaterFall: return QStringLiteral("WaterFall");
        case MagicID::WindCutter: return QStringLiteral("WindCutter");
        default: return unknownString;
    }
}
