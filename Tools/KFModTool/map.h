#ifndef MAP_H
#define MAP_H

#include "checksum.h"
#include "kfmterror.h"
#include "kftypes.h"
#include "tfile.h"
#include <QMessageBox>

typedef quint8 byte;

class Map
{
public:
    Map(TFile &fdatTFile, unsigned int index, QString name);

    KingsField::EntityClassDeclaration &getEntityClassDeclaration(byte classDeclIndex)
    {
        try
        {
            return entityClassDeclarations[classDeclIndex];
        }
        catch (const std::out_of_range &exception)
        {
            KFMTError::outOfRange(classDeclIndex, "entity class declaration", exception.what());
        }

    }

    const std::array<KingsField::EntityClassDeclaration, 40> getEntityClassDeclarations() const
    {
        return entityClassDeclarations;
    }

    const std::array<KingsField::EntityInstance, 200> getEntityInstances() const
    {
        return entityInstances;
    }

    KingsField::EntityInstance &getEntityInstance(byte instanceIndex)
    {
        try
        {
            return entityInstances[instanceIndex];
        }
        catch (const std::out_of_range &exception)
        {
            KFMTError::outOfRange(instanceIndex, "entity instance declaration", exception.what());
        }
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
        try
        {
            return objInstances[instanceIndex];
        }
        catch (const std::out_of_range &exception)
        {
            KFMTError::outOfRange(instanceIndex, "object instance declaration", exception.what());
        }
    }

    const std::array<KingsField::ObjectInstanceDeclaration, 350> &getObjectInstanceDeclarations() const
    {
        return objInstances;
    }

    KingsField::Tile& getTile(size_t line, size_t column)
    {
        try
        {
            return tileMap[line][column];
        }
        catch (const std::out_of_range &exception)
        {
            QString errorMessage = "Tried accessing tile at position X %1 Y %2.\n%3";
            errorMessage = errorMessage.arg(column).arg(line).arg(exception.what());
            KFMTError::fatalError(errorMessage);
        }
    }

    KingsField::VFXInstanceDeclaration &getVFXInstance(size_t instanceIndex)
    {
        try
        {
            return vfxInstances[instanceIndex];
        }
        catch (const std::out_of_range &exception)
        {
            KFMTError::outOfRange(instanceIndex, "VFX instance declaration", exception.what());
        }
    }

    const std::array<KingsField::VFXInstanceDeclaration, 128> &getVFXInstanceDeclarations() const
    {
        return vfxInstances;
    }

    void writeChanges();

private:
    TFile &fdat;

    KingsField::Tile tileMap[80][80] {};
    unsigned int mapIndex;
    QByteArray map1;
    QByteArray map2;
    QByteArray map3;
    QString mapName;
    std::array<KingsField::EntityClassDeclaration, 40> entityClassDeclarations {};
    std::array<KingsField::EntityInstance, 200> entityInstances {};
    std::array<KingsField::ObjectInstanceDeclaration, 350> objInstances {};
    std::array<KingsField::VFXInstanceDeclaration, 128> vfxInstances {};
};

#endif // MAP_H
