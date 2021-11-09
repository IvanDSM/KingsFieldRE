#ifndef SHOPLISTMODEL_H
#define SHOPLISTMODEL_H

#include <QAbstractListModel>

class ShopListModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    explicit ShopListModel(QObject* parent = nullptr) : QAbstractListModel(parent) {}

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private:
    static const std::array<QString, 6> kf2ShopNames;
};

#endif // SHOPLISTMODEL_H
