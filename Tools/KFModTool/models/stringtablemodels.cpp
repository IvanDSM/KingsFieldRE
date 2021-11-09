#include "stringtablemodels.h"
#include <cstring>

// Codec for the table models
// I don't like just throwing it here but the way QTextCodec works there's nothing else I can do.
static QTextCodec* codec = new KingsFieldII::KF2UTextCodec();

// UIStrings1TableModel

QVariant UIStrings1TableModel::data(const QModelIndex& index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid()) return {};

    return codec->toUnicode(gameExe.uiStrings1[index.row()].str, 24);
}

Qt::ItemFlags UIStrings1TableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

QVariant UIStrings1TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};

    if (orientation == Qt::Horizontal) return QStringLiteral("String");

    //if (orientation == Qt::Vertical):

    switch (section)
    {
        case 0: return QStringLiteral("Use Item");
        case 1: return QStringLiteral("Use Magic");
        case 2: return QStringLiteral("Equipment");
        case 3: return QStringLiteral("Strength");
        case 4: return QStringLiteral("Drop Item");
        case 5: return QStringLiteral("Data");
        case 6: return QStringLiteral("Option");
        case 7: return QStringLiteral("Return");
        case 10: return QStringLiteral("Data");
        case 11: return QStringLiteral("Load");
        case 12: return QStringLiteral("Quit");
        case 13: return QStringLiteral("Return");
        case 14: return QStringLiteral("Save");
        case 15: return QStringLiteral("Load");
        case 16: return QStringLiteral("Quit");
        case 21: return QStringLiteral("Option");
        case 22: return QStringLiteral("Sound");
        case 23: return QStringLiteral("Music");
        case 24: return QStringLiteral("Display HP/MP");
        case 25: return QStringLiteral("Display Compass");
        case 26: return QStringLiteral("Display Items");
        case 27: return QStringLiteral("Walking Effect");
        case 28: return QStringLiteral("Return");
        case 32: return QStringLiteral("Shop");
        case 33: return QStringLiteral("Buy");
        case 34: return QStringLiteral("Sell");
        case 35: return QStringLiteral("Return");
        case 43: return QStringLiteral("Locksmith");
        case 44: return QStringLiteral("Buy");
        case 45: return QStringLiteral("Copy");
        case 46: return QStringLiteral("Return");
        case 55: return QStringLiteral("Fortune Teller");
        case 56: return QStringLiteral("Crystal Artisan");
        case 66: return QStringLiteral("New");
        case 67: return QStringLiteral("Load");
        default: return QStringLiteral("Unused");
    }
}

bool UIStrings1TableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!value.isValid() || value.toString().isEmpty() || role != Qt::EditRole || !index.isValid())
        return false;

    const auto converted = codec->fromUnicode(value.toString());
    auto* string = &gameExe.uiStrings1[index.row()];

    std::fill(std::begin(string->str), std::end(string->str), static_cast<char>(0xffu));

    std::memcpy(string, converted.data(), converted.size());

    emit dataChanged(index, index);

    return true;
}

// UIStrings2TableModel

QVariant UIStrings2TableModel::data(const QModelIndex& index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid()) return {};

    return codec->toUnicode(gameExe.uiStrings2[index.row()].str, 24);
}

Qt::ItemFlags UIStrings2TableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

QVariant UIStrings2TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};

    if (orientation == Qt::Horizontal) return QStringLiteral("String");

    //if (orientation == Qt::Vertical):

    switch (section)
    {
        case 0: return QStringLiteral("Weapon");
        case 1: return QStringLiteral("Magic");
        case 2: return QStringLiteral("Shield");
        case 3: return QStringLiteral("Head");
        case 4: return QStringLiteral("Body");
        case 5: return QStringLiteral("Arms");
        case 6: return QStringLiteral("Feet");
        case 7: return QStringLiteral("Item 1");
        case 8: return QStringLiteral("Item 2");
        case 9: return QStringLiteral("Select Button");
        case 10: return QStringLiteral("Access Memory Card");
        case 11: return QStringLiteral("Take Off");
        case 12: return QStringLiteral("Experience");
        case 13: return QStringLiteral("Level");
        case 14: return QStringLiteral("Offense");
        case 15: return QStringLiteral("Defense");
        case 16: return QStringLiteral("Condition");
        case 17: return QStringLiteral("Paralyze");
        case 18: return QStringLiteral("Curse");
        case 19: return QStringLiteral("Slow");
        case 20: return QStringLiteral("Poison");
        case 21: return QStringLiteral("Dark");
        case 22: return QStringLiteral("Good");
        case 23: return QStringLiteral("Gold");
        case 24: return QStringLiteral("Checking the RAM Card");
        case 25: return QStringLiteral("Please Wait");
        case 26: return QStringLiteral("Cannot Save");
        case 27: return QStringLiteral("Check the RAM Card");
        case 28: return QStringLiteral("Not Formatted");
        case 29: return QStringLiteral("Will You Format?");
        case 30: return QStringLiteral("Cannot Save, If The RAM");
        case 31: return QStringLiteral("Card Is Not Formatted");
        case 32: return QStringLiteral("Cannot Save Data");
        case 33: return QStringLiteral("In This Card");
        case 34: return QStringLiteral("Cannot Load");
        case 35: return QStringLiteral("Saving");
        case 36: return QStringLiteral("Not Enough Space");
        case 37: return QStringLiteral("Loading");
        case 38: return QStringLiteral("Remove The CD");
        case 39: return QStringLiteral("And Turn Off The Power");
        case 40: return QStringLiteral("Data Error!");
        case 41: return QStringLiteral("Cannot Save");
        case 42: return QStringLiteral("Without The RAM Card");
        case 43: return QStringLiteral("RAM Card Is Full");
        case 44: return QStringLiteral("Please Insert A New Card");
        default: return QStringLiteral("Unused");
    }
}

bool UIStrings2TableModel::setData(const QModelIndex& index, const QVariant& value, int role) {}

// ItemStringsTableModel

QVariant ItemStringsTableModel::data(const QModelIndex& index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid()) return {};

    return codec->toUnicode(gameExe.itemStrings[index.row()].str, 24);
}

Qt::ItemFlags ItemStringsTableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

QVariant ItemStringsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};

    if (orientation == Qt::Horizontal) return QStringLiteral("String");

    //if (orientation == Qt::Vertical):

    return KingsFieldII::getObjectName(static_cast<KingsFieldII::ObjectID>(section));
}

bool ItemStringsTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {}

// MagicStringsTableModel

QVariant MagicStringsTableModel::data(const QModelIndex& index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid()) return {};

    return codec->toUnicode(gameExe.magicStrings[index.row()].str, 24);
}

Qt::ItemFlags MagicStringsTableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

QVariant MagicStringsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};

    if (orientation == Qt::Horizontal) return QStringLiteral("String");

    //if (orientation == Qt::Vertical):

    return KingsFieldII::getMagicIDName(static_cast<KingsFieldII::MagicID>(section));
}

bool MagicStringsTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {}
