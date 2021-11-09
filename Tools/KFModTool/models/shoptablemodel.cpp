#include "shoptablemodel.h"

QVariant ShopTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};
    switch (orientation)
    {
        case Qt::Horizontal:
            switch (section)
            {
                case 0: return QStringLiteral("Has");
                case 1: return QStringLiteral("'Buy' price");
                case 2:
                    // 5 is the locksmith's shop, and the sell prices table is used for the
                    // duplication prices.
                    if (shopIndex != 5) return QStringLiteral("'Sell' price");
                    return QStringLiteral("'Duplicate' price");
                default: return {};
            }
        case Qt::Vertical:
            return KingsFieldII::getObjectName(static_cast<KingsFieldII::ObjectID>(section));
        default: return {};
    }
}

int ShopTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return 120;
}

int ShopTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return 3;
}

static const auto naStr = QStringLiteral("Shop does not have this option");

QVariant ShopTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return {};

    // This bit of code represents the 1-byte bools as checkboxes in the table model
    // The "* 2" is done because in the Qt::CheckState enum, "Checked" has the value 2.
    // See https://doc.qt.io/qt-5/qt.html#CheckState-enum
    if (role == Qt::CheckStateRole && index.column() == 0)
        return gameExe.shopStocks[shopIndex][index.row()] * 2;

    if (role != Qt::DisplayRole) return {};

    switch (index.column())
    {
        case 1: return gameExe.shopBuyPrices[shopIndex][index.row()];
        case 2:
            if (shopIndex == 4) return naStr;

            return gameExe.shopSellPrices[shopIndex][index.row()];
        default: return {};
    }
}
