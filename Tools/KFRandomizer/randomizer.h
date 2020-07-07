#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <QObject>
#include <QRandomGenerator>

class Randomizer : public QObject
{
    Q_OBJECT
public:
    explicit Randomizer(QObject *parent = nullptr, QString fileName = "");
    void randomizeMonsters(bool randomizeItemDrops = false);
    void randomizeItems();
    void setNoEmptyDrops(bool _noEmptyDrops);
    QByteArray &getFile();

signals:
    void statusUpdate(const QString &status);

private:
    bool borken = false;
    bool noEmptyDrops = false;
    QByteArray fdat;
    QByteArray fdat1Array;
    QByteArray fdat4Array;
    QByteArray fdat7Array;
    QByteArray fdat10Array;
    QByteArray fdat13Array;
    QByteArray fdat16Array;
    QByteArray fdat19Array;
    QByteArray fdat22Array;
    QByteArray fdat25Array;
    QRandomGenerator rng;
    QWidget *parentWidget = nullptr;
    quint8 getRandomItem();
    quint8 getRandomMonster();
};

#endif // RANDOMIZER_H
