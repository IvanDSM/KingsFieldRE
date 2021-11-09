#include "kf2.h"
#include <QLineEdit>

QString KingsFieldII::KF2UTextCodec::convertToUnicode(const char* in,
                                                      int length,
                                                      QTextCodec::ConverterState* state) const
{
    QString result;
    result.resize(length);

    int remaining = 0;
    int invalid = 0;

    for (int i = 0; i < length; i++)
    {
        switch (in[i])
        {
            case 0x0: result[i] = 'A'; break;
            case 0x1: result[i] = 'B'; break;
            case 0x2: result[i] = 'C'; break;
            case 0x3: result[i] = 'D'; break;
            case 0x4: result[i] = 'E'; break;
            case 0x5: result[i] = 'F'; break;
            case 0x6: result[i] = 'G'; break;
            case 0x7: result[i] = 'H'; break;
            case 0x8: result[i] = 'I'; break;
            case 0x9: result[i] = 'J'; break;
            case 0xa: result[i] = 'K'; break;
            case 0xb: result[i] = 'L'; break;
            case 0xc: result[i] = 'M'; break;
            case 0xd: result[i] = 'N'; break;
            case 0xe: result[i] = 'O'; break;
            case 0xf: result[i] = 'P'; break;
            case 0x10: result[i] = 'Q'; break;
            case 0x11: result[i] = 'R'; break;
            case 0x12: result[i] = 'S'; break;
            case 0x13: result[i] = 'T'; break;
            case 0x14: result[i] = 'U'; break;
            case 0x15: result[i] = 'V'; break;
            case 0x16: result[i] = 'W'; break;
            case 0x17: result[i] = 'X'; break;
            case 0x18: result[i] = 'Y'; break;
            case 0x19: result[i] = 'Z'; break;
            case 0x20: result[i] = '0'; break;
            case 0x21: result[i] = '1'; break;
            case 0x22: result[i] = '2'; break;
            case 0x23: result[i] = '3'; break;
            case 0x24: result[i] = '4'; break;
            case 0x25: result[i] = '5'; break;
            case 0x26: result[i] = '6'; break;
            case 0x27: result[i] = '7'; break;
            case 0x28: result[i] = '8'; break;
            case 0x29: result[i] = '9'; break;
            case 0x30: result[i] = '.'; break;
            case 0x31: result[i] = ','; break;
            case 0x32: result[i] = '\''; break;
            case 0x33: result[i] = '-'; break;
            case 0x34: result[i] = '='; break;
            case 0x35: result[i] = '/'; break;
            case 0x36: result[i] = '*'; break;
            case 0x37: result[i] = '#'; break;
            case 0x38: result[i] = '!'; break;
            case 0x39: result[i] = L'•'; break;
            case 0x3a: result[i] = '?'; break;
            case 0x7f: result[i] = ' '; break;
            case static_cast<char>(0xffu):
                result[i] = '\0';
                remaining = length - i;
                result.resize(i);
                i = length;
                break;

            default: invalid++;
        }
    }

    if (state != nullptr)
    {
        state->invalidChars = invalid;
        state->remainingChars = remaining;
    }

    return result;
}

QByteArray KingsFieldII::KF2UTextCodec::convertFromUnicode(const QChar* in,
                                                           int length,
                                                           QTextCodec::ConverterState* state) const
{
    QByteArray result;
    result.resize(length);

    int remaining = 0;
    int invalid = 0;

    for (int i = 0; i < length; i++)
    {
        switch (in[i].unicode())
        {
            case 'A': result[i] = 0x0; break;
            case 'B': result[i] = 0x1; break;
            case 'C': result[i] = 0x2; break;
            case 'D': result[i] = 0x3; break;
            case 'E': result[i] = 0x4; break;
            case 'F': result[i] = 0x5; break;
            case 'G': result[i] = 0x6; break;
            case 'H': result[i] = 0x7; break;
            case 'I': result[i] = 0x8; break;
            case 'J': result[i] = 0x9; break;
            case 'K': result[i] = 0xa; break;
            case 'L': result[i] = 0xb; break;
            case 'M': result[i] = 0xc; break;
            case 'N': result[i] = 0xd; break;
            case 'O': result[i] = 0xe; break;
            case 'P': result[i] = 0xf; break;
            case 'Q': result[i] = 0x10; break;
            case 'R': result[i] = 0x11; break;
            case 'S': result[i] = 0x12; break;
            case 'T': result[i] = 0x13; break;
            case 'U': result[i] = 0x14; break;
            case 'V': result[i] = 0x15; break;
            case 'W': result[i] = 0x16; break;
            case 'X': result[i] = 0x17; break;
            case 'Y': result[i] = 0x18; break;
            case 'Z': result[i] = 0x19; break;
            case '0': result[i] = 0x20; break;
            case '1': result[i] = 0x21; break;
            case '2': result[i] = 0x22; break;
            case '3': result[i] = 0x23; break;
            case '4': result[i] = 0x24; break;
            case '5': result[i] = 0x25; break;
            case '6': result[i] = 0x26; break;
            case '7': result[i] = 0x27; break;
            case '8': result[i] = 0x28; break;
            case '9': result[i] = 0x29; break;
            case '.': result[i] = 0x30; break;
            case ',': result[i] = 0x31; break;
            case '\'': result[i] = 0x32; break;
            case '-': result[i] = 0x33; break;
            case '=': result[i] = 0x34; break;
            case '/': result[i] = 0x35; break;
            case '*': result[i] = 0x36; break;
            case '#': result[i] = 0x37; break;
            case '!': result[i] = 0x38; break;
            case L'•': result[i] = 0x39; break;
            case '?': result[i] = 0x3a; break;
            case ' ': result[i] = 0x7f; break;
            case '\0':
                result[i] = static_cast<char>(0xffu);
                remaining = length - i;
                result.resize(i);
                i = length;
                break;

            default: invalid++;
        }
    }

    if (state != nullptr)
    {
        state->invalidChars = invalid;
        state->remainingChars = remaining;
    }

    return result;
}

void KingsFieldII::KF2UTextCodec::kf2UConvert(const char* in,
                                              const int length,
                                              QTextCodec::ConverterState* state,
                                              Direction direction) const
{}

QWidget* KingsFieldII::KF2UTextDelegate::createEditor(QWidget* parent,
                                                      const QStyleOptionViewItem&,
                                                      const QModelIndex& index) const
{
    auto* editor = new QLineEdit(parent);
    // Actual pattern: [A-Z0-9\.,\\\-/\*!•\? ]+?
    // I have to double the \ because of C++ rules
    // See https://doc.qt.io/qt-5/qregularexpression.html#introduction
    editor->setValidator(
        new QRegularExpressionValidator(QRegularExpression("[A-Z0-9\\.,\\\\\\-/\\*!•\\? ]+?"),
                                        editor));
    return editor;
}

void KingsFieldII::KF2UTextDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    auto* lineEdit = reinterpret_cast<QLineEdit*>(editor);
    lineEdit->setText(index.model()->data(index, Qt::EditRole).toString());
}

void KingsFieldII::KF2UTextDelegate::setModelData(QWidget* editor,
                                                  QAbstractItemModel* model,
                                                  const QModelIndex& index) const
{
    auto* lineEdit = reinterpret_cast<QLineEdit*>(editor);
    model->setData(index, lineEdit->text());
}

void KingsFieldII::KF2UTextDelegate::updateEditorGeometry(QWidget* editor,
                                                          const QStyleOptionViewItem& option,
                                                          const QModelIndex&) const
{
    editor->setGeometry(option.rect);
}

QString KingsFieldII::getEntityMeshName(const KingsFieldII::EntityMeshID entityMeshId)
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

QString KingsFieldII::getEntityStateIDName(const KingsFieldII::EntityStateID entityStateId)
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

QString KingsFieldII::getMagicIDName(const KingsFieldII::MagicID magicId)
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

QString KingsFieldII::getObjectClassTypeName(const KingsFieldII::ObjectClassType classType)
{
    switch (classType)
    {
        case ObjectClassType::DragonGrass: return QStringLiteral("Dragon Grass");
        case ObjectClassType::DragonStoneSlot: return QStringLiteral("Dragon Stone Slot");
        case ObjectClassType::FloorTrap: return QStringLiteral("Floor Trap");
        case ObjectClassType::GuidePost: return QStringLiteral("Guide Post");
        case ObjectClassType::GuyraWarp: return QStringLiteral("Guyra Warp");
        case ObjectClassType::Hider: return QStringLiteral("Hider");
        case ObjectClassType::LoadTrigger: return QStringLiteral("LoadTrigger");
        case ObjectClassType::Minecart: return QStringLiteral("Minecart");
        case ObjectClassType::None: return QStringLiteral("None");
        case ObjectClassType::PickableItem: return QStringLiteral("Pickable Item");
        case ObjectClassType::RhombusKeySlot: return QStringLiteral("Rhombus Key Slot");
        case ObjectClassType::RotatesToOpen: return QStringLiteral("Rotates to Open");
        case ObjectClassType::SavePoint: return QStringLiteral("Save Point");
        case ObjectClassType::SecretCompartment: return QStringLiteral("Secret Compartment");
        case ObjectClassType::ShrineKeySlot: return QStringLiteral("Shrine Key Slot");
        case ObjectClassType::Sign: return QStringLiteral("Sign");
        case ObjectClassType::SkullKeySlot: return QStringLiteral("Skull Key Slot");
        case ObjectClassType::Skybox: return QStringLiteral("Skybox");
        case ObjectClassType::SlidesToOpen: return QStringLiteral("Slides to Open");
        case ObjectClassType::Switch: return QStringLiteral("Switch");
        case ObjectClassType::Trap: return QStringLiteral("Trap");
        case ObjectClassType::VerticalDoor: return QStringLiteral("Vertical Door");
        case ObjectClassType::VerticalDoor2: return QStringLiteral("Vertical Door 2");
        case ObjectClassType::WaterWell: return QStringLiteral("Water Well");
    }

    return unknownString;
}

QString KingsFieldII::getObjectName(const KingsFieldII::ObjectID itemId)
{
    switch (itemId)
    {
        case ObjectID::ABrokenSword: return QStringLiteral("ABrokenSword");
        case ObjectID::ASoldierOfVerdite: return QStringLiteral("ASoldierOfVerdite");
        case ObjectID::ArmsA: return QStringLiteral("ArmsA");
        case ObjectID::ArmsDemonsHands: return QStringLiteral("ArmsDemonsHands");
        case ObjectID::ArmsIronGloves: return QStringLiteral("ArmsIronGloves");
        case ObjectID::ArmsRuinousGloves: return QStringLiteral("ArmsRuinousGloves");
        case ObjectID::ArmsSilverArms: return QStringLiteral("ArmsSilverArms");
        case ObjectID::ArmsStoneHands: return QStringLiteral("ArmsStoneHands");
        case ObjectID::Barrel: return QStringLiteral("Barrel");
        case ObjectID::Bed: return QStringLiteral("Bed");
        case ObjectID::BigGreyDoorLeft: return QStringLiteral("BigGreyDoorLeft");
        case ObjectID::BigGreyDoorRight: return QStringLiteral("BigGreyDoorRight");
        case ObjectID::BigRoughStoneDoor: return QStringLiteral("BigRoughStoneDoor");
        case ObjectID::BigStoneDoor: return QStringLiteral("BigStoneDoor");
        case ObjectID::BodyA: return QStringLiteral("BodyA");
        case ObjectID::BodyBreastPlate: return QStringLiteral("BodyBreastPlate");
        case ObjectID::BodyDarkArmor: return QStringLiteral("BodyDarkArmor");
        case ObjectID::BodyIceArmor: return QStringLiteral("BodyIceArmor");
        case ObjectID::BodyKnightPlate: return QStringLiteral("BodyKnightPlate");
        case ObjectID::BodySeathsArmor: return QStringLiteral("BodySeathsArmor");
        case ObjectID::Bones: return QStringLiteral("Bones");
        case ObjectID::Bones2: return QStringLiteral("Bones2");
        case ObjectID::Bucket: return QStringLiteral("Bucket");
        case ObjectID::CeilingTorch: return QStringLiteral("CeilingTorch");
        case ObjectID::Chair: return QStringLiteral("Chair");
        case ObjectID::ColosseumDoor: return QStringLiteral("ColosseumDoor");
        case ObjectID::CopperKnightStatue: return QStringLiteral("CopperKnightStatue");
        case ObjectID::CrossFeetTable: return QStringLiteral("CrossFeetTable");
        case ObjectID::DaytimeSkybox: return QStringLiteral("DaytimeSkybox");
        case ObjectID::DeadCrystalMiner: return QStringLiteral("DeadCrystalMiner");
        case ObjectID::DeadDudeRENAME_ME: return QStringLiteral("DeadDudeRENAME_ME");
        case ObjectID::DemonLordFromMadScientistTube:
            return QStringLiteral("DemonLordFromMadScientistTube");
        case ObjectID::DemonLordStatue: return QStringLiteral("DemonLordStatue");
        case ObjectID::DragonGrass: return QStringLiteral("DragonGrass");
        case ObjectID::DragonStoneSlot: return QStringLiteral("DragonStoneSlot");
        case ObjectID::DrawbridgeSwitch: return QStringLiteral("DrawbridgeSwitch");
        case ObjectID::DummyItem1: return QStringLiteral("DummyItem1");
        case ObjectID::DummyItem2: return QStringLiteral("DummyItem2");
        case ObjectID::DummyItem3: return QStringLiteral("DummyItem3");
        case ObjectID::DummyItem4: return QStringLiteral("DummyItem4");
        case ObjectID::DummyItem5: return QStringLiteral("DummyItem5");
        case ObjectID::DummyItem6: return QStringLiteral("DummyItem6");
        case ObjectID::DummyItem7: return QStringLiteral("DummyItem7");
        case ObjectID::EarthElementalStatue: return QStringLiteral("EarthElementalStatue");
        case ObjectID::ElfsGrave: return QStringLiteral("ElfsGrave");
        case ObjectID::EquipItemAmuletOfMist: return QStringLiteral("EquipItemAmuletOfMist");
        case ObjectID::EquipItemEarthRing: return QStringLiteral("EquipItemEarthRing");
        case ObjectID::EquipItemLightwaveRing: return QStringLiteral("EquipItemLightwaveRing");
        case ObjectID::EquipItemPsycprosCollar: return QStringLiteral("EquipItemPsycprosCollar");
        case ObjectID::EquipItemScorpionsBracelet:
            return QStringLiteral("EquipItemScorpionsBracelet");
        case ObjectID::EquipItemSeathsBracelet: return QStringLiteral("EquipItemSeathsBracelet");
        case ObjectID::EquipItemSeathsTear: return QStringLiteral("EquipItemSeathsTear");
        case ObjectID::FeetA: return QStringLiteral("FeetA");
        case ObjectID::FeetDeathWalkers: return QStringLiteral("FeetDeathWalkers");
        case ObjectID::FeetIronBoots: return QStringLiteral("FeetIronBoots");
        case ObjectID::FeetLegGuarders: return QStringLiteral("FeetLegGuarders");
        case ObjectID::FeetRuinousBoots: return QStringLiteral("FeetRuinousBoots");
        case ObjectID::FeetSilverBoots: return QStringLiteral("FeetSilverBoots");
        case ObjectID::GoldenThingRENAME_ME: return QStringLiteral("GoldenThingRENAME_ME");
        case ObjectID::GreenWallFloorTrap: return QStringLiteral("GreenWallFloorTrap");
        case ObjectID::GreenWallSecretDoor: return QStringLiteral("GreenWallSecretDoor");
        case ObjectID::GreenWallWithSecret1: return QStringLiteral("GreenWallWithSecret1");
        case ObjectID::GreenWallWithSecret2: return QStringLiteral("GreenWallWithSecret2");
        case ObjectID::GreenWallWithSpikeTrap: return QStringLiteral("GreenWallWithSpikeTrap");
        case ObjectID::Guidepost: return QStringLiteral("Guidepost");
        case ObjectID::GuyraTeleportCube: return QStringLiteral("GuyraTeleportCube");
        case ObjectID::HarvineCastleSign: return QStringLiteral("HarvineCastleSign");
        case ObjectID::HarvinesCastleDoor: return QStringLiteral("HarvinesCastleDoor");
        case ObjectID::HarvinesThrone: return QStringLiteral("HarvinesThrone");
        case ObjectID::HeadA: return QStringLiteral("HeadA");
        case ObjectID::HeadBloodCrown: return QStringLiteral("HeadBloodCrown");
        case ObjectID::HeadGreatHelm: return QStringLiteral("HeadGreatHelm");
        case ObjectID::HeadIronMask: return QStringLiteral("HeadIronMask");
        case ObjectID::HeadKnightHelm: return QStringLiteral("HeadKnightHelm");
        case ObjectID::HeadLightningHelm: return QStringLiteral("HeadLightningHelm");
        case ObjectID::HeadSeathsHelm: return QStringLiteral("HeadSeathsHelm");
        case ObjectID::InvisibleObject: return QStringLiteral("InvisibleObject");
        case ObjectID::ItemAHerb: return QStringLiteral("ItemAHerb");
        case ObjectID::ItemAHerb2: return QStringLiteral("ItemAHerb2");
        case ObjectID::ItemAPotion: return QStringLiteral("ItemAPotion");
        case ObjectID::ItemARing: return QStringLiteral("ItemARing");
        case ObjectID::ItemAntidote: return QStringLiteral("ItemAntidote");
        case ObjectID::ItemArrowForTheBow: return QStringLiteral("ItemArrowForTheBow");
        case ObjectID::ItemBloodStone: return QStringLiteral("ItemBloodStone");
        case ObjectID::ItemBluePotion: return QStringLiteral("ItemBluePotion");
        case ObjectID::ItemCrystal: return QStringLiteral("ItemCrystal");
        case ObjectID::ItemCrystalFlask: return QStringLiteral("ItemCrystalFlask");
        case ObjectID::ItemCrystalShard: return QStringLiteral("ItemCrystalShard");
        case ObjectID::ItemDarkCrystal: return QStringLiteral("ItemDarkCrystal");
        case ObjectID::ItemDemonsPick: return QStringLiteral("ItemDemonsPick");
        case ObjectID::ItemDragonCrystal: return QStringLiteral("ItemDragonCrystal");
        case ObjectID::ItemDragonStone: return QStringLiteral("ItemDragonStone");
        case ObjectID::ItemEarthCrystal: return QStringLiteral("ItemEarthCrystal");
        case ObjectID::ItemEarthHerb: return QStringLiteral("ItemEarthHerb");
        case ObjectID::ItemElfsBolt: return QStringLiteral("ItemElfsBolt");
        case ObjectID::ItemElfsKey: return QStringLiteral("ItemElfsKey");
        case ObjectID::ItemFigureOfSeath: return QStringLiteral("ItemFigureOfSeath");
        case ObjectID::ItemFireCrystal: return QStringLiteral("ItemFireCrystal");
        case ObjectID::ItemGoldCoin: return QStringLiteral("ItemGoldCoin");
        case ObjectID::ItemGoldKey: return QStringLiteral("ItemGoldKey");
        case ObjectID::ItemGoldPotion: return QStringLiteral("ItemGoldPotion");
        case ObjectID::ItemGreenPotion: return QStringLiteral("ItemGreenPotion");
        case ObjectID::ItemGroundBell: return QStringLiteral("ItemGroundBell");
        case ObjectID::ItemHarvinesFlute: return QStringLiteral("ItemHarvinesFlute");
        case ObjectID::ItemHarvinesKey: return QStringLiteral("ItemHarvinesKey");
        case ObjectID::ItemJailKey: return QStringLiteral("ItemJailKey");
        case ObjectID::ItemLightCrystal: return QStringLiteral("ItemLightCrystal");
        case ObjectID::ItemMagiciansKey: return QStringLiteral("ItemMagiciansKey");
        case ObjectID::ItemMinersMap: return QStringLiteral("ItemMinersMap");
        case ObjectID::ItemMoonGate: return QStringLiteral("ItemMoonGate");
        case ObjectID::ItemMoonKey: return QStringLiteral("ItemMoonKey");
        case ObjectID::ItemMoonStone: return QStringLiteral("ItemMoonStone");
        case ObjectID::ItemNecronsMap: return QStringLiteral("ItemNecronsMap");
        case ObjectID::ItemPhantomRod: return QStringLiteral("ItemPhantomRod");
        case ObjectID::ItemPiratesKey: return QStringLiteral("ItemPiratesKey");
        case ObjectID::ItemPiratesMap: return QStringLiteral("ItemPiratesMap");
        case ObjectID::ItemRedPotion: return QStringLiteral("ItemRedPotion");
        case ObjectID::ItemRhombusKey: return QStringLiteral("ItemRhombusKey");
        case ObjectID::ItemSeathsPlume: return QStringLiteral("ItemSeathsPlume");
        case ObjectID::ItemShrineKey: return QStringLiteral("ItemShrineKey");
        case ObjectID::ItemSilverKey: return QStringLiteral("ItemSilverKey");
        case ObjectID::ItemSkullKey: return QStringLiteral("ItemSkullKey");
        case ObjectID::ItemStarGate: return QStringLiteral("ItemStarGate");
        case ObjectID::ItemStarKey: return QStringLiteral("ItemStarKey");
        case ObjectID::ItemSunGate: return QStringLiteral("ItemSunGate");
        case ObjectID::ItemSunKey: return QStringLiteral("ItemSunKey");
        case ObjectID::ItemTruthGlass: return QStringLiteral("ItemTruthGlass");
        case ObjectID::ItemVerdite: return QStringLiteral("ItemVerdite");
        case ObjectID::ItemWaterCrystal: return QStringLiteral("ItemWaterCrystal");
        case ObjectID::ItemWindCrystal: return QStringLiteral("ItemWindCrystal");
        case ObjectID::JailDoor: return QStringLiteral("JailDoor");
        case ObjectID::KnockerDoorLeft: return QStringLiteral("KnockerDoorLeft");
        case ObjectID::KnockerDoorRight: return QStringLiteral("KnockerDoorRight");
        case ObjectID::Lantern: return QStringLiteral("Lantern");
        case ObjectID::LoadArea: return QStringLiteral("LoadArea");
        case ObjectID::MadScientistBox: return QStringLiteral("MadScientistBox");
        case ObjectID::MadScientistLightCrystalMachine:
            return QStringLiteral("MadScientistLightCrystalMachine");
        case ObjectID::MadScientistTube: return QStringLiteral("MadScientistTube");
        case ObjectID::MarbleWallFloorTrap: return QStringLiteral("MarbleWallFloorTrap");
        case ObjectID::MineSign: return QStringLiteral("MineSign");
        case ObjectID::Minecart: return QStringLiteral("Minecart");
        case ObjectID::MinersGraveMaybe: return QStringLiteral("MinersGraveMaybe");
        case ObjectID::Moon: return QStringLiteral("Moon");
        case ObjectID::MountainSkybox: return QStringLiteral("MountainSkybox");
        case ObjectID::NighttimeSkybox: return QStringLiteral("NighttimeSkybox");
        case ObjectID::NighttimeSkybox2: return QStringLiteral("NighttimeSkybox2");
        case ObjectID::None: return QStringLiteral("None");
        case ObjectID::PillarOfWind: return QStringLiteral("PillarOfWind");
        case ObjectID::RedFlower: return QStringLiteral("RedFlower");
        case ObjectID::RhombusKeyDoor: return QStringLiteral("RhombusKeyDoor");
        case ObjectID::RhombusKeySlot: return QStringLiteral("RhombusKeySlot");
        case ObjectID::SamuraisGrave: return QStringLiteral("SamuraisGrave");
        case ObjectID::Savepoint: return QStringLiteral("Savepoint");
        case ObjectID::SeathsFountainDoorLeft: return QStringLiteral("SeathsFountainDoorLeft");
        case ObjectID::SeathsFountainDoorRight: return QStringLiteral("SeathsFountainDoorRight");
        case ObjectID::SeathsFountainPillar: return QStringLiteral("SeathsFountainPillar");
        case ObjectID::SecretDoor: return QStringLiteral("SecretDoor");
        case ObjectID::Shelf: return QStringLiteral("Shelf");
        case ObjectID::ShieldA: return QStringLiteral("ShieldA");
        case ObjectID::ShieldCrystalGuard: return QStringLiteral("ShieldCrystalGuard");
        case ObjectID::ShieldLargeShield: return QStringLiteral("ShieldLargeShield");
        case ObjectID::ShieldLeatherShield: return QStringLiteral("ShieldLeatherShield");
        case ObjectID::ShieldMoonGuard: return QStringLiteral("ShieldMoonGuard");
        case ObjectID::ShieldSeathsShield: return QStringLiteral("ShieldSeathsShield");
        case ObjectID::ShieldSkullShield: return QStringLiteral("ShieldSkullShield");
        case ObjectID::ShovelAndHammer: return QStringLiteral("ShovelAndHammer");
        case ObjectID::ShrineKeySlot: return QStringLiteral("ShrineKeySlot");
        case ObjectID::Sign: return QStringLiteral("Sign");
        case ObjectID::SimpleStoolMaybeRENAME_ME:
            return QStringLiteral("SimpleStoolMaybeRENAME_ME");
        case ObjectID::SkullKeySlot: return QStringLiteral("SkullKeySlot");
        case ObjectID::SkullKeyWaterObstacle: return QStringLiteral("SkullKeyWaterObstacle");
        case ObjectID::SlotForSomethingRENAME_ME:
            return QStringLiteral("SlotForSomethingRENAME_ME");
        case ObjectID::SmallBed: return QStringLiteral("SmallBed");
        case ObjectID::SmallStackOfLogs: return QStringLiteral("SmallStackOfLogs");
        case ObjectID::SmallTable: return QStringLiteral("SmallTable");
        case ObjectID::SmallWeirdPillarRENAME_ME:
            return QStringLiteral("SmallWeirdPillarRENAME_ME");
        case ObjectID::SomeBrokenGrave: return QStringLiteral("SomeBrokenGrave");
        case ObjectID::SomeBrokenGrave2: return QStringLiteral("SomeBrokenGrave2");
        case ObjectID::SomeDoorHandleRENAME_ME: return QStringLiteral("SomeDoorHandleRENAME_ME");
        case ObjectID::SomeGrave: return QStringLiteral("SomeGrave");
        case ObjectID::SquareWell: return QStringLiteral("SquareWell");
        case ObjectID::StoneChestBody: return QStringLiteral("StoneChestBody");
        case ObjectID::StoneChestLid: return QStringLiteral("StoneChestLid");
        case ObjectID::StoneGobletWithLavaRENAME_ME:
            return QStringLiteral("StoneGobletWithLavaRENAME_ME");
        case ObjectID::StonePillar: return QStringLiteral("StonePillar");
        case ObjectID::StoneThing2RENAME_ME: return QStringLiteral("StoneThing2RENAME_ME");
        case ObjectID::StoneThing3RENAME_ME: return QStringLiteral("StoneThing3RENAME_ME");
        case ObjectID::StoneThingRENAME_ME: return QStringLiteral("StoneThingRENAME_ME");
        case ObjectID::Stool: return QStringLiteral("Stool");
        case ObjectID::SwingingScythe: return QStringLiteral("SwingingScythe");
        case ObjectID::SwingingSpikeBall: return QStringLiteral("SwingingSpikeBall");
        case ObjectID::TableWithThingie: return QStringLiteral("TableWithThingie");
        case ObjectID::TarnStatue: return QStringLiteral("TarnStatue");
        case ObjectID::TheMagiciansLamp: return QStringLiteral("TheMagiciansLamp");
        case ObjectID::TheSoldiersGrave: return QStringLiteral("TheSoldiersGrave");
        case ObjectID::ThreeStones: return QStringLiteral("ThreeStones");
        case ObjectID::TinyXFeetTable: return QStringLiteral("TinyXFeetTable");
        case ObjectID::Tree: return QStringLiteral("Tree");
        case ObjectID::WHATTHEFUCKStatue: return QStringLiteral("WHATTHEFUCKStatue");
        case ObjectID::WTF: return QStringLiteral("WTF");
        case ObjectID::WallTorch: return QStringLiteral("WallTorch");
        case ObjectID::WallWithSecret: return QStringLiteral("WallWithSecret");
        case ObjectID::WallWithSecret2: return QStringLiteral("WallWithSecret2");
        case ObjectID::WallWithSpikeTrap: return QStringLiteral("WallWithSpikeTrap");
        case ObjectID::WallWriting: return QStringLiteral("WallWriting");
        case ObjectID::WallWriting2: return QStringLiteral("WallWriting2");
        case ObjectID::WallWriting3: return QStringLiteral("WallWriting3");
        case ObjectID::WaterWell: return QStringLiteral("WaterWell");
        case ObjectID::WeaponA1: return QStringLiteral("WeaponA1");
        case ObjectID::WeaponA2: return QStringLiteral("WeaponA2");
        case ObjectID::WeaponA3: return QStringLiteral("WeaponA3");
        case ObjectID::WeaponA4: return QStringLiteral("WeaponA4");
        case ObjectID::WeaponA5: return QStringLiteral("WeaponA5");
        case ObjectID::WeaponArbalest: return QStringLiteral("WeaponArbalest");
        case ObjectID::WeaponBastardSword: return QStringLiteral("WeaponBastardSword");
        case ObjectID::WeaponBattleHammer: return QStringLiteral("WeaponBattleHammer");
        case ObjectID::WeaponBow: return QStringLiteral("WeaponBow");
        case ObjectID::WeaponCrescentAxe: return QStringLiteral("WeaponCrescentAxe");
        case ObjectID::WeaponDagger: return QStringLiteral("WeaponDagger");
        case ObjectID::WeaponDarkSlayer: return QStringLiteral("WeaponDarkSlayer");
        case ObjectID::WeaponFlameSword: return QStringLiteral("WeaponFlameSword");
        case ObjectID::WeaponIceBlade: return QStringLiteral("WeaponIceBlade");
        case ObjectID::WeaponKnightSword: return QStringLiteral("WeaponKnightSword");
        case ObjectID::WeaponMoonlightSword: return QStringLiteral("WeaponMoonlightSword");
        case ObjectID::WeaponMorningStar: return QStringLiteral("WeaponMorningStar");
        case ObjectID::WeaponSeathsSword: return QStringLiteral("WeaponSeathsSword");
        case ObjectID::WeaponShiden: return QStringLiteral("WeaponShiden");
        case ObjectID::WeaponShortSword: return QStringLiteral("WeaponShortSword");
        case ObjectID::WeaponSpider: return QStringLiteral("WeaponSpider");
        case ObjectID::WeirdPillarRENAME_ME: return QStringLiteral("WeirdPillarRENAME_ME");
        case ObjectID::WhitePinkFlower: return QStringLiteral("WhitePinkFlower");
        case ObjectID::WoodenChestBody: return QStringLiteral("WoodenChestBody");
        case ObjectID::WoodenChestLid: return QStringLiteral("WoodenChestLid");
        case ObjectID::WoodenThingRENAME_ME: return QStringLiteral("WoodenThingRENAME_ME");
        case ObjectID::XFeetTable: return QStringLiteral("XFeetTable");
        default: return unknownString;
    }
}

QString KingsFieldII::getWeaponStatsName(const byte weaponStatsIndex)
{
    switch (weaponStatsIndex)
    {
        case 0: return QStringLiteral("Dagger");
        case 1: return QStringLiteral("Short Sword");
        case 2: return QStringLiteral("Knight Sword");
        case 3: return QStringLiteral("Morning Star");
        case 4: return QStringLiteral("Battle Hammer");
        case 5: return QStringLiteral("Bastard Sword");
        case 6: return QStringLiteral("Crescent Axe");
        case 7: return QStringLiteral("A");
        case 8: return QStringLiteral("A");
        case 9: return QStringLiteral("Flame Sword");
        case 10: return QStringLiteral("Shiden");
        case 11: return QStringLiteral("Spider");
        case 12: return QStringLiteral("Ice Blade");
        case 13: return QStringLiteral("Seath's Sword");
        case 14: return QStringLiteral("Moonlight Sword");
        case 15: return QStringLiteral("Dark Slayer");
        case 16: return QStringLiteral("Bow");
        case 17: return QStringLiteral("Arbalest");
        default: return unknownString;
    }
}
