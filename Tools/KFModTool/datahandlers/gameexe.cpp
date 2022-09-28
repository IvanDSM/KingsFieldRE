#include "gameexe.h"
#include "core/kfmtcore.h"
#include "core/kfmterror.h"
#include "utilities.h"

constexpr inline size_t ramToFilePos(size_t ramPos)
{
    // Only tested for KF2U!!!
    return ramPos - 0x80010800;
}

GameEXE::GameEXE(KFMTFile& file_) : KFMTDataHandler(file_)
{
    switch (core.currentVersionedGame())
    {
        case KFMTCore::VersionedGame::KF2Jv1_0:

            //uiStrings1 = &Utilities::as<KF2::PosString>(file.rawData,
            //                                                     ramToFilePos(0x80064cf0));
            //uiStrings2 = &Utilities::as<KF2::String>(file.rawData,
            //                                                  ramToFilePos(0x80065674));
            //itemStrings = &Utilities::as<KF2::String>(file.rawData,
            //                                                   ramToFilePos(0x80065b24));
            //magicStrings = &Utilities::as<KF2::String>(file.rawData,
            //                                                    ramToFilePos(0x80066664));

            for (size_t i = 0; i < 6; i++)
            {
                shopStocks.at(i) = reinterpret_cast<uint8_t*>(
                    file.rawData.data() + ramToFilePos(0x80065950 + (120 * i)));
                shopBuyPrices.at(i) = &Utilities::as<uint16_t>(file.rawData,
                                                               ramToFilePos(0x80065c20 + (240 * i)));

                uint16_t* sellTable = nullptr;

                if (i == 5)
                    sellTable = &Utilities::as<uint16_t>(file.rawData,
                                                         ramToFilePos(0x800661c0 + (240 * (i - 1))));
                else if (i != 4)
                    sellTable = &Utilities::as<uint16_t>(file.rawData,
                                                         ramToFilePos(0x800661c0 + (240 * i)));

                shopSellPrices.at(i) = sellTable;
            }

            break;
        case KFMTCore::VersionedGame::KF2U:
            uiStrings1 = &Utilities::as<KF2::PosString>(file.rawData,
                                                                 ramToFilePos(0x80064cf0));
            uiStrings2 = &Utilities::as<KF2::String>(file.rawData,
                                                              ramToFilePos(0x80065674));
            itemStrings = &Utilities::as<KF2::String>(file.rawData,
                                                               ramToFilePos(0x80065b24));
            magicStrings = &Utilities::as<KF2::String>(file.rawData,
                                                                ramToFilePos(0x80066664));
            for (size_t i = 0; i < 6; i++)
            {
                shopStocks.at(i) = reinterpret_cast<uint8_t*>(
                    file.rawData.data() + ramToFilePos(0x80066844 + (120 * i)));
                shopBuyPrices.at(i) = &Utilities::as<uint16_t>(file.rawData,
                                                               ramToFilePos(0x80066b14 + (240 * i)));

                uint16_t* sellTable = nullptr;

                if (i == 5)
                    sellTable = &Utilities::as<uint16_t>(file.rawData,
                                                         ramToFilePos(0x800670b4 + (240 * (i - 1))));
                else if (i != 4)
                    sellTable = &Utilities::as<uint16_t>(file.rawData,
                                                         ramToFilePos(0x800670b4 + (240 * i)));

                shopSellPrices.at(i) = sellTable;
            }
            break;
        default:
            KFMTError::fatalError(QStringLiteral("GameEXE created for unsupported game %1!")
                                      .arg(static_cast<size_t>(core.currentVersionedGame())));
    }
}
