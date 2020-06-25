#ifndef FDAT28_H
#define FDAT28_H

#include "kftypes.h"
#include <vector>

class FDAT28
{
public:
    FDAT28();
    KingsField80175914OddStruct getGodOnlyKnows(size_t index);
    KingsFieldPlayerLvlData getLvlData(size_t level);
    KingsFieldMagicStructure getMagicData(size_t magicId);
    KingsFieldWeaponStats getWeaponStats(size_t weaponId);
    bool isLoaded();
    void loadFile(QString &fileName);

private:
    bool loaded = false;
    static const size_t oddStructVectorSize = 320;
    static const size_t lvlDataVectorSize = 100;
    static const size_t magicDataVectorSize = 63;
    static const size_t weaponStatsVectorSize = 18;
    std::vector<KingsField80175914OddStruct> oddStructVector;
    std::vector<KingsFieldPlayerLvlData> lvlDataVector;
    std::vector<KingsFieldMagicStructure> magicDataVector;
    std::vector<KingsFieldWeaponStats> weaponStatsVector;
};

#endif // FDAT28_H
