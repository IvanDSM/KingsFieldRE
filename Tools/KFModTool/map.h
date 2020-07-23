#ifndef MAP_H
#define MAP_H

#include "checksum.h"
#include "kftypes.h"
#include "tfile.h"

typedef quint8 byte;

class Map
{
public:
    Map(TFile &fdatTFile, unsigned int index, QString name);

    const std::vector<KingsField::EntityClassDeclaration> getEntityClassDeclarations() const
    {
        return entityClassDeclarations;
    }

    KingsField::EntityClassDeclaration &getClassDeclaration(byte classDeclIndex)
    {
        if (classDeclIndex < 40)
            return entityClassDeclarations[classDeclIndex];
    }

    const std::vector<KingsField::EntityInstance> getEntityInstances() const
    {
        return entityInstances;
    }

    KingsField::EntityInstance &getInstance(byte instanceIndex)
    {
        if (instanceIndex < 200)
            return entityInstances[instanceIndex];
    }

    const unsigned int &getIndex() const
    {
        return mapIndex;
    }

    const QString &getName() const
    {
        return mapName;
    }

    KingsField::ObjectInstanceDeclaration &getObjectInstance(size_t instanceIndex)
    {
        if (instanceIndex < 350)
            return objInstances[instanceIndex];
    }

    const std::vector<KingsField::ObjectInstanceDeclaration> &getObjectInstanceDeclarations() const
    {
        return objInstances;
    }


    KingsField::Tile& getTile(size_t line, size_t column)
    {
        if (line < 80 && column < 80)
            return tileMap[line][column];
    }

    void writeChanges();

private:
    TFile &fdat;

    KingsField::Tile tileMap[80][80];
    unsigned int mapIndex;
    QByteArray map1;
    QByteArray map2;
    QByteArray map3;
    QString mapName;
    std::vector<KingsField::EntityClassDeclaration> entityClassDeclarations;
    std::vector<KingsField::EntityInstance> entityInstances;
    std::vector<KingsField::ObjectInstanceDeclaration> objInstances;
};

#endif // MAP_H
