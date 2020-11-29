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

    /*
    if (md5Hash == "C323AC0E13F3EE4FAAEF6E45C1379CD1" || // FDAT.T
        md5Hash == "5C9D729367476B66B7988288FE842BA4" || // ITEM.T
        md5Hash == "7E09927E405FFC282A4DBC501B95BF89" || // MO.T
        md5Hash == "AB20EC7C9C4E227FCA9C065D7DA05ECC" || // RTIM.T
        md5Hash == "9C980424DC165E5B15A8BCBDB50368A8" || // FDAT.T
        md5Hash == "D39EE781C7BAC1F8CC851AD2B8D0C72A" || // TALK.T
        md5Hash == "4605A5C590578E857F2E690FBA575198"    // VAB.T
        )
        return kfUSPrettyMap;   //JAPAN II PSBest Rev 1
    */
    return emptyMap;
}
