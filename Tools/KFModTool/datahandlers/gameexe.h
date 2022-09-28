#ifndef GAMEEXE_H
#define GAMEEXE_H

#include "kf2/text.h"
#include "kfmtdatahandler.h"

class GameEXE : public KFMTDataHandler
{
public:
    explicit GameEXE(KFMTFile& file_);

private:
    // KF2
    // FIXME: This is the kind of place where gsl::span would shine.
    // We really should consider adding gsl as a dependency :/
    KF2::PosString* uiStrings1;
    constexpr static size_t uiStrings1_size = 68;
    KF2::String* uiStrings2;
    constexpr static size_t uiStrings2_size = 50;
    KF2::String* itemStrings;
    constexpr static size_t itemStrings_size = 120;
    KF2::String* magicStrings;
    constexpr static size_t magicStrings_size = 20;
    std::array<uint8_t*, 6> shopStocks;
    std::array<uint16_t*, 6> shopBuyPrices;
    std::array<uint16_t*, 6> shopSellPrices;
    constexpr static size_t shopStuff_size = 120;

    void saveChanges() override {}

    friend class UIStrings1TableModel;
    friend class UIStrings2TableModel;
    friend class ItemStringsTableModel;
    friend class MagicStringsTableModel;
    friend class ShopTableModel;
};

#endif // GAMEEXE_H
