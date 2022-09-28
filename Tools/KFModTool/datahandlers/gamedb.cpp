#include "gamedb.h"
#include "utilities.h"

GameDB::GameDB(KFMTFile& file_) : KFMTDataHandler(file_)
{
    QDataStream stream(file.rawData);
    stream.setByteOrder(QDataStream::LittleEndian);
    uint32_t sectionSize;

    // Section 1 - Object Class Declarations
    stream >> sectionSize;
    objClasses = &Utilities::as<KF2::ObjectClass>(file.rawData, stream.device()->pos());
    stream.skipRawData(sectionSize);

    // Section 2 - Weapon Stats
    stream >> sectionSize;
    weaponStats = &Utilities::as<KF2::Weapon>(file.rawData, stream.device()->pos());
    stream.skipRawData(sectionSize);

    // Section 3 - Armor Stats
    stream >> sectionSize;
    armorStats = &Utilities::as<KF2::Armor>(file.rawData, stream.device()->pos());
    stream.skipRawData(sectionSize);

    // Section 4 - Player Level Data
    stream >> sectionSize;
    lvlData = &Utilities::as<KF2::PlayerLevel>(file.rawData, stream.device()->pos());
    stream.skipRawData(sectionSize);

    // Section 5 - Magic Data
    stream >> sectionSize;
    magicData = &Utilities::as<KF2::Magic>(file.rawData, stream.device()->pos());
    stream.skipRawData(sectionSize);
}
