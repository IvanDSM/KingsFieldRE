#ifndef STRINGTABLEMODELS_H
#define STRINGTABLEMODELS_H

#include "datahandlers/gameexe.h"
#include <QAbstractTableModel>

class UIStrings1TableModel : public QAbstractTableModel
{
public:
    explicit UIStrings1TableModel(GameEXE& gameExe_, QObject* parent = nullptr)
        : QAbstractTableModel(parent), gameExe(gameExe_)
    {}

    int columnCount(const QModelIndex&) const override { return 1; }

    QVariant data(const QModelIndex& index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex& = QModelIndex()) const override
    {
        return createIndex(row, column, &gameExe.uiStrings1[row]);
    }

    int rowCount(const QModelIndex&) const override { return GameEXE::uiStrings1_size; }

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

private:
    GameEXE& gameExe;
};

class UIStrings2TableModel : public QAbstractTableModel
{
public:
    explicit UIStrings2TableModel(GameEXE& gameExe_, QObject* parent = nullptr)
        : QAbstractTableModel(parent), gameExe(gameExe_)
    {}

    int columnCount(const QModelIndex&) const override { return 1; }

    QVariant data(const QModelIndex& index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex& = QModelIndex()) const override
    {
        return createIndex(row, column, &gameExe.uiStrings2[row]);
    }

    int rowCount(const QModelIndex&) const override { return GameEXE::uiStrings2_size; }

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

private:
    GameEXE& gameExe;
};

class ItemStringsTableModel : public QAbstractTableModel
{
public:
    explicit ItemStringsTableModel(GameEXE& gameExe_, QObject* parent = nullptr)
        : QAbstractTableModel(parent), gameExe(gameExe_)
    {}

    int columnCount(const QModelIndex&) const override { return 1; }

    QVariant data(const QModelIndex& index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex& = QModelIndex()) const override
    {
        return createIndex(row, column, &gameExe.itemStrings[row]);
    }

    int rowCount(const QModelIndex&) const override { return GameEXE::itemStrings_size; }

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

private:
    GameEXE& gameExe;
};

class MagicStringsTableModel : public QAbstractTableModel
{
public:
    explicit MagicStringsTableModel(GameEXE& gameExe_, QObject* parent = nullptr)
        : QAbstractTableModel(parent), gameExe(gameExe_)
    {}

    int columnCount(const QModelIndex&) const override { return 1; }

    QVariant data(const QModelIndex& index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex& = QModelIndex()) const override
    {
        return createIndex(row, column, &gameExe.magicStrings[row]);
    }

    int rowCount(const QModelIndex&) const override { return GameEXE::magicStrings_size; }

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

private:
    GameEXE& gameExe;
};

#endif // STRINGTABLEMODELS_H
