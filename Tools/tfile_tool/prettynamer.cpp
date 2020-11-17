#include "prettynamer.h"

const std::unordered_map<QString, QString> &PrettyNamer::getPrettyMap(const QByteArray &md5Hash)
{
    if (md5Hash == "b383d528016c005e756af9618b76e93e" || // FDAT.T
        md5Hash == "8e4b1499d179303e3c8e954332bacf00" || // ITEM.T
        md5Hash == "28ed1eeac04678e6a81243fabd4802ae" || // MO.T
        md5Hash == "f0f96d1eb2e1d6498116948e8c5037bb" || // RTIM.T
        md5Hash == "9c980424dc165e5b15a8bcbdb50368a8" || // RTMD.T
        md5Hash == "ba9e1d53cc029f451df6c6ed3a385592" || // TALK.T
        md5Hash == "4605a5c590578e857f2e690fba575198"    // VAB.T
        )
        return kfUSPrettyMap;

    return emptyMap;
}
