#include "randomizer.h"
#include <QBuffer>
#include <QDataStream>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>

Randomizer::Randomizer(QObject *parent, const QString &fileName, const QString &seed) : QObject(parent)
{
    parentWidget = reinterpret_cast<QWidget *>(parent);
    if (fileName.isEmpty())
    {
        QMessageBox::critical(parentWidget,
                              "Randomizer: What the hell?",
                              "The randomizer got an empty filename! This shouldn't have happened!!!");
        borken = true;
    }

    QFile cdFile(fileName);
    if (!cdFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(parentWidget,
                              "Randomizer: Failed to open file",
                              "The file failed to open :(");
        borken = true;
    }
    else
    {
        fdat = cdFile.readAll();
        cdFile.close();

        fdat1Array = fdat.mid(0x11000, 0x7000);
        fdat4Array = fdat.mid(0x2A000, 0x7000);
        fdat7Array = fdat.mid(0x44000, 0x7000);
        fdat10Array = fdat.mid(0x5D000, 0x7000);
        fdat13Array = fdat.mid(0x76000, 0x7000);
        fdat16Array = fdat.mid(0x8F800, 0x7000);
        fdat19Array = fdat.mid(0xA9000, 0x7000);
        fdat22Array = fdat.mid(0xC1800, 0x7000);
        fdat25Array = fdat.mid(0xDB000, 0x7000);

        emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Copied CD image into memory.");
    }

    if (!seed.isEmpty())
    {
        std::hash<QString> stringHasher;
        rng = QRandomGenerator(stringHasher(seed));
    }
    else
        rng = QRandomGenerator::securelySeeded();
}

void Randomizer::randomizeMonsters(bool randomizeItemDrops)
{
    if (borken)
        return;
    QString end = "...";

    if (randomizeItemDrops)
    {
        end = " and item drops...";
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing monsters" + end);
    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Declaring data streams for each map...");

    // Look, I tried to make something nice but UGH

    QDataStream fdat1Stream(&fdat1Array, QIODevice::ReadWrite);
    fdat1Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat4Stream(&fdat4Array, QIODevice::ReadWrite);
    fdat4Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat7Stream(&fdat7Array, QIODevice::ReadWrite);
    fdat7Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat10Stream(&fdat10Array, QIODevice::ReadWrite);
    fdat10Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat13Stream(&fdat13Array, QIODevice::ReadWrite);
    fdat13Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat16Stream(&fdat16Array, QIODevice::ReadWrite);
    fdat16Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat19Stream(&fdat19Array, QIODevice::ReadWrite);
    fdat19Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat22Stream(&fdat22Array, QIODevice::ReadWrite);
    fdat22Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat25Stream(&fdat25Array, QIODevice::ReadWrite);
    fdat25Stream.setByteOrder(QDataStream::LittleEndian);

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Getting ends of the monster blocks...");
    quint32 fdat1MonsterBlockEnd;
    quint32 fdat4MonsterBlockEnd;
    quint32 fdat7MonsterBlockEnd;
    quint32 fdat10MonsterBlockEnd;
    quint32 fdat13MonsterBlockEnd;
    quint32 fdat16MonsterBlockEnd;
    quint32 fdat19MonsterBlockEnd;
    quint32 fdat22MonsterBlockEnd;
    quint32 fdat25MonsterBlockEnd;

    fdat1Stream.skipRawData(0x32C0 + 4);
    fdat1Stream >> fdat1MonsterBlockEnd;
    fdat4Stream.skipRawData(0x32C0 + 4);
    fdat4Stream >> fdat4MonsterBlockEnd;
    fdat7Stream.skipRawData(0x32C0 + 4);
    fdat7Stream >> fdat7MonsterBlockEnd;
    fdat10Stream.skipRawData(0x32C0 + 4);
    fdat10Stream >> fdat10MonsterBlockEnd;
    fdat13Stream.skipRawData(0x32C0 + 4);
    fdat13Stream >> fdat13MonsterBlockEnd;
    fdat16Stream.skipRawData(0x32C0 + 4);
    fdat16Stream >> fdat16MonsterBlockEnd;
    fdat19Stream.skipRawData(0x32C0 + 4);
    fdat19Stream >> fdat19MonsterBlockEnd;
    fdat22Stream.skipRawData(0x32C0 + 4);
    fdat22Stream >> fdat22MonsterBlockEnd;
    fdat25Stream.skipRawData(0x32C0 + 4);
    fdat25Stream >> fdat25MonsterBlockEnd;

    quint64 bytes_done;
    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing map 1 (FDAT 1)...");

    bytes_done = 0;
    fdat1Stream.skipRawData(1);
    bytes_done++;
    while (bytes_done < fdat1MonsterBlockEnd)
    {
        fdat1Stream << getRandomMonster();
        if (randomizeItemDrops)
        {
            fdat1Stream.skipRawData(4);
            fdat1Stream << getRandomItem();
            fdat1Stream.skipRawData(10);
        }
        else
            fdat1Stream.skipRawData(15);
        bytes_done += 16;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing map 2 (FDAT 4)...");

    bytes_done = 0;
    fdat4Stream.skipRawData(1);
    bytes_done++;
    while (bytes_done < fdat4MonsterBlockEnd)
    {
        fdat4Stream << getRandomMonster();
        if (randomizeItemDrops)
        {
            fdat4Stream.skipRawData(4);
            fdat4Stream << getRandomItem();
            fdat4Stream.skipRawData(10);
        }
        else
            fdat4Stream.skipRawData(15);
        bytes_done += 16;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing map 3 (FDAT 7)...");

    bytes_done = 0;
    fdat7Stream.skipRawData(1);
    bytes_done++;
    while (bytes_done < fdat7MonsterBlockEnd)
    {
        fdat7Stream << getRandomMonster();
        if (randomizeItemDrops)
        {
            fdat7Stream.skipRawData(4);
            fdat7Stream << getRandomItem();
            fdat7Stream.skipRawData(10);
        }
        else
            fdat7Stream.skipRawData(15);
        bytes_done += 16;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing map 4 (FDAT 10)...");

    bytes_done = 0;
    fdat10Stream.skipRawData(1);
    bytes_done++;
    while (bytes_done < fdat10MonsterBlockEnd)
    {
        fdat10Stream << getRandomMonster();
        if (randomizeItemDrops)
        {
            fdat10Stream.skipRawData(4);
            fdat10Stream << getRandomItem();
            fdat10Stream.skipRawData(10);
        }
        else
            fdat10Stream.skipRawData(15);
        bytes_done += 16;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing map 5 (FDAT 13)...");

    bytes_done = 0;
    fdat13Stream.skipRawData(1);
    bytes_done++;
    while (bytes_done < fdat13MonsterBlockEnd)
    {
        fdat13Stream << getRandomMonster();
        if (randomizeItemDrops)
        {
            fdat13Stream.skipRawData(4);
            fdat13Stream << getRandomItem();
            fdat13Stream.skipRawData(10);
        }
        else
            fdat13Stream.skipRawData(15);
        bytes_done += 16;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing map 6 (FDAT 16)...");

    bytes_done = 0;
    fdat16Stream.skipRawData(1);
    bytes_done++;
    while (bytes_done < fdat16MonsterBlockEnd)
    {
        fdat16Stream << getRandomMonster();
        if (randomizeItemDrops)
        {
            fdat16Stream.skipRawData(4);
            fdat16Stream << getRandomItem();
            fdat16Stream.skipRawData(10);
        }
        else
            fdat16Stream.skipRawData(15);
        bytes_done += 16;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing map 7 (FDAT 19)...");

    bytes_done = 0;
    fdat19Stream.skipRawData(1);
    bytes_done++;
    while (bytes_done < fdat19MonsterBlockEnd)
    {
        fdat19Stream << getRandomMonster();
        if (randomizeItemDrops)
        {
            fdat19Stream.skipRawData(4);
            fdat19Stream << getRandomItem();
            fdat19Stream.skipRawData(10);
        }
        else
            fdat19Stream.skipRawData(15);
        bytes_done += 16;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing map 8 (FDAT 22)...");

    bytes_done = 0;
    fdat22Stream.skipRawData(1);
    bytes_done++;
    while (bytes_done < fdat22MonsterBlockEnd)
    {
        fdat22Stream << getRandomMonster();
        if (randomizeItemDrops)
        {
            fdat22Stream.skipRawData(4);
            fdat22Stream << getRandomItem();
            fdat22Stream.skipRawData(10);
        }
        else
            fdat22Stream.skipRawData(15);
        bytes_done += 16;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing map 9 (FDAT 25)...");

    bytes_done = 0;
    fdat25Stream.skipRawData(1);
    bytes_done++;
    while (bytes_done < fdat25MonsterBlockEnd)
    {
        fdat25Stream << getRandomMonster();
        if (randomizeItemDrops)
        {
            fdat25Stream.skipRawData(4);
            fdat25Stream << getRandomItem();
            fdat25Stream.skipRawData(10);
        }
        else
            fdat25Stream.skipRawData(15);
        bytes_done += 16;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 1 (FDAT 1)...");

    fdat1Stream.device()->reset();
    quint32 fdat1Checksum = 0x12345678;
    quint64 fdat1Stop = fdat1Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat1Stop)
    {
        quint32 curInt;
        fdat1Stream >> curInt;
        fdat1Checksum += curInt;
        bytes_done += 4;
    }

    fdat1Stream << fdat1Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 2 (FDAT 4)...");

    fdat4Stream.device()->reset();
    quint32 fdat4Checksum = 0x12345678;
    quint64 fdat4Stop = fdat4Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat4Stop)
    {
        quint32 curInt;
        fdat4Stream >> curInt;
        fdat4Checksum += curInt;
        bytes_done += 4;
    }

    fdat4Stream << fdat4Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 3 (FDAT 7)...");

    fdat7Stream.device()->reset();
    quint32 fdat7Checksum = 0x12345678;
    quint64 fdat7Stop = fdat7Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat7Stop)
    {
        quint32 curInt;
        fdat7Stream >> curInt;
        fdat7Checksum += curInt;
        bytes_done += 4;
    }

    fdat7Stream << fdat7Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 4 (FDAT 10)...");

    fdat10Stream.device()->reset();
    quint32 fdat10Checksum = 0x12345678;
    quint64 fdat10Stop = fdat10Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat10Stop)
    {
        quint32 curInt;
        fdat10Stream >> curInt;
        fdat10Checksum += curInt;
        bytes_done += 4;
    }

    fdat10Stream << fdat10Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 5 (FDAT 13)...");

    fdat13Stream.device()->reset();
    quint32 fdat13Checksum = 0x12345678;
    quint64 fdat13Stop = fdat13Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat13Stop)
    {
        quint32 curInt;
        fdat13Stream >> curInt;
        fdat13Checksum += curInt;
        bytes_done += 4;
    }

    fdat13Stream << fdat13Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 6 (FDAT 16)...");

    fdat16Stream.device()->reset();
    quint32 fdat16Checksum = 0x12345678;
    quint64 fdat16Stop = fdat16Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat16Stop)
    {
        quint32 curInt;
        fdat16Stream >> curInt;
        fdat16Checksum += curInt;
        bytes_done += 4;
    }

    fdat16Stream << fdat16Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 7 (FDAT 19)...");

    fdat19Stream.device()->reset();
    quint32 fdat19Checksum = 0x12345678;
    quint64 fdat19Stop = fdat19Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat19Stop)
    {
        quint32 curInt;
        fdat19Stream >> curInt;
        fdat19Checksum += curInt;
        bytes_done += 4;
    }

    fdat19Stream << fdat19Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 8 (FDAT 22)...");

    fdat22Stream.device()->reset();
    quint32 fdat22Checksum = 0x12345678;
    quint64 fdat22Stop = fdat22Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat22Stop)
    {
        quint32 curInt;
        fdat22Stream >> curInt;
        fdat22Checksum += curInt;
        bytes_done += 4;
    }

    fdat22Stream << fdat22Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 9 (FDAT 25)...");

    fdat25Stream.device()->reset();
    quint32 fdat25Checksum = 0x12345678;
    quint64 fdat25Stop = fdat25Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat25Stop)
    {
        quint32 curInt;
        fdat25Stream >> curInt;
        fdat25Checksum += curInt;
        bytes_done += 4;
    }

    fdat25Stream << fdat25Checksum;

}

void Randomizer::randomizeItems()
{
    if (borken)
        return;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing items...");
    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Declaring data streams for each map (again)...");

    // Look, I tried to make something nice but UGH

    QDataStream fdat1Stream(&fdat1Array, QIODevice::ReadWrite);
    fdat1Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat4Stream(&fdat4Array, QIODevice::ReadWrite);
    fdat4Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat7Stream(&fdat7Array, QIODevice::ReadWrite);
    fdat7Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat10Stream(&fdat10Array, QIODevice::ReadWrite);
    fdat10Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat13Stream(&fdat13Array, QIODevice::ReadWrite);
    fdat13Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat16Stream(&fdat16Array, QIODevice::ReadWrite);
    fdat16Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat19Stream(&fdat19Array, QIODevice::ReadWrite);
    fdat19Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat22Stream(&fdat22Array, QIODevice::ReadWrite);
    fdat22Stream.setByteOrder(QDataStream::LittleEndian);
    QDataStream fdat25Stream(&fdat25Array, QIODevice::ReadWrite);
    fdat25Stream.setByteOrder(QDataStream::LittleEndian);

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Getting ends of the monster blocks...");
    quint32 fdat1ItemBlockEnd;
    quint32 fdat4ItemBlockEnd;
    quint32 fdat7ItemBlockEnd;
    quint32 fdat10ItemBlockEnd;
    quint32 fdat13ItemBlockEnd;
    quint32 fdat16ItemBlockEnd;
    quint32 fdat19ItemBlockEnd;
    quint32 fdat22ItemBlockEnd;
    quint32 fdat25ItemBlockEnd;

    fdat1Stream.skipRawData(0x3F44 + 4);
    fdat1Stream >> fdat1ItemBlockEnd;
    fdat4Stream.skipRawData(0x3F44 + 4);
    fdat4Stream >> fdat4ItemBlockEnd;
    fdat7Stream.skipRawData(0x3F44 + 4);
    fdat7Stream >> fdat7ItemBlockEnd;
    fdat10Stream.skipRawData(0x3F44 + 4);
    fdat10Stream >> fdat10ItemBlockEnd;
    fdat13Stream.skipRawData(0x3F44 + 4);
    fdat13Stream >> fdat13ItemBlockEnd;
    fdat16Stream.skipRawData(0x3F44 + 4);
    fdat16Stream >> fdat16ItemBlockEnd;
    fdat19Stream.skipRawData(0x3F44 + 4);
    fdat19Stream >> fdat19ItemBlockEnd;
    fdat22Stream.skipRawData(0x3F44 + 4);
    fdat22Stream >> fdat22ItemBlockEnd;
    fdat25Stream.skipRawData(0x3F44 + 4);
    fdat25Stream >> fdat25ItemBlockEnd;

    quint64 bytes_done;
    quint8 cur_item;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing items in map 1 (FDAT 1)...");

    bytes_done = 0;
    fdat1Stream.skipRawData(4);
    bytes_done += 4;
    while (bytes_done < fdat1ItemBlockEnd)
    {
        fdat1Stream >> cur_item;
        if (isValidItem(cur_item))
        {
            fdat1Stream.device()->seek(fdat1Stream.device()->pos() - 1);
            fdat1Stream << getRandomItem();
            fdat1Stream.skipRawData(23);
        }
        else
            fdat1Stream.skipRawData(23);
        bytes_done += 24;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing items in map 2 (FDAT 4)...");

    bytes_done = 0;
    fdat4Stream.skipRawData(4);
    bytes_done += 4;
    while (bytes_done < fdat4ItemBlockEnd)
    {
        fdat4Stream >> cur_item;
        if (isValidItem(cur_item))
        {
            fdat4Stream.device()->seek(fdat4Stream.device()->pos() - 1);
            fdat4Stream << getRandomItem();
            fdat4Stream.skipRawData(23);
        }
        else
            fdat4Stream.skipRawData(23);
        bytes_done += 24;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing items in map 3 (FDAT 7)...");

    bytes_done = 0;
    fdat7Stream.skipRawData(4);
    bytes_done += 4;
    while (bytes_done < fdat7ItemBlockEnd)
    {
        fdat7Stream >> cur_item;
        if (isValidItem(cur_item))
        {
            fdat7Stream.device()->seek(fdat7Stream.device()->pos() - 1);
            fdat7Stream << getRandomItem();
            fdat7Stream.skipRawData(23);
        }
        else
            fdat7Stream.skipRawData(23);
        bytes_done += 24;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing items in map 4 (FDAT 10)...");

    bytes_done = 0;
    fdat10Stream.skipRawData(4);
    bytes_done += 4;
    while (bytes_done < fdat10ItemBlockEnd)
    {
        fdat10Stream >> cur_item;
        if (isValidItem(cur_item))
        {
            fdat10Stream.device()->seek(fdat10Stream.device()->pos() - 1);
            fdat10Stream << getRandomItem();
            fdat10Stream.skipRawData(23);
        }
        else
            fdat10Stream.skipRawData(23);
        bytes_done += 24;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing items in map 5 (FDAT 13)...");

    bytes_done = 0;
    fdat13Stream.skipRawData(4);
    bytes_done += 4;
    while (bytes_done < fdat13ItemBlockEnd)
    {
        fdat13Stream >> cur_item;
        if (isValidItem(cur_item))
        {
            fdat13Stream.device()->seek(fdat13Stream.device()->pos() - 1);
            fdat13Stream << getRandomItem();
            fdat13Stream.skipRawData(23);
        }
        else
            fdat13Stream.skipRawData(23);
        bytes_done += 24;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing items in map 6 (FDAT 16)...");

    bytes_done = 0;
    fdat16Stream.skipRawData(4);
    bytes_done += 4;
    while (bytes_done < fdat16ItemBlockEnd)
    {
        fdat16Stream >> cur_item;
        if (isValidItem(cur_item))
        {
            fdat16Stream.device()->seek(fdat16Stream.device()->pos() - 1);
            fdat16Stream << getRandomItem();
            fdat16Stream.skipRawData(23);
        }
        else
            fdat16Stream.skipRawData(23);
        bytes_done += 24;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing items in map 7 (FDAT 19)...");

    bytes_done = 0;
    fdat19Stream.skipRawData(4);
    bytes_done += 4;
    while (bytes_done < fdat19ItemBlockEnd)
    {
        fdat19Stream >> cur_item;
        if (isValidItem(cur_item))
        {
            fdat19Stream.device()->seek(fdat19Stream.device()->pos() - 1);
            fdat19Stream << getRandomItem();
            fdat19Stream.skipRawData(23);
        }
        else
            fdat19Stream.skipRawData(23);
        bytes_done += 24;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing items in map 8 (FDAT 22)...");

    bytes_done = 0;
    fdat22Stream.skipRawData(4);
    bytes_done += 4;
    while (bytes_done < fdat22ItemBlockEnd)
    {
        fdat22Stream >> cur_item;
        if (isValidItem(cur_item))
        {
            fdat22Stream.device()->seek(fdat22Stream.device()->pos() - 1);
            fdat22Stream << getRandomItem();
            fdat22Stream.skipRawData(23);
        }
        else
            fdat22Stream.skipRawData(23);
        bytes_done += 24;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Randomizing items in map 9 (FDAT 25)...");

    bytes_done = 0;
    fdat25Stream.skipRawData(4);
    bytes_done += 4;
    while (bytes_done < fdat25ItemBlockEnd)
    {
        fdat25Stream >> cur_item;
        if (isValidItem(cur_item))
        {
            fdat25Stream.device()->seek(fdat25Stream.device()->pos() - 1);
            fdat25Stream << getRandomItem();
            fdat25Stream.skipRawData(23);
        }
        else
            fdat25Stream.skipRawData(23);
        bytes_done += 24;
    }

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 1 (FDAT 1)...");

    fdat1Stream.device()->reset();
    quint32 fdat1Checksum = 0x12345678;
    quint64 fdat1Stop = fdat1Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat1Stop)
    {
        quint32 curInt;
        fdat1Stream >> curInt;
        fdat1Checksum += curInt;
        bytes_done += 4;
    }

    fdat1Stream << fdat1Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 2 (FDAT 4)...");

    fdat4Stream.device()->reset();
    quint32 fdat4Checksum = 0x12345678;
    quint64 fdat4Stop = fdat4Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat4Stop)
    {
        quint32 curInt;
        fdat4Stream >> curInt;
        fdat4Checksum += curInt;
        bytes_done += 4;
    }

    fdat4Stream << fdat4Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 3 (FDAT 7)...");

    fdat7Stream.device()->reset();
    quint32 fdat7Checksum = 0x12345678;
    quint64 fdat7Stop = fdat7Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat7Stop)
    {
        quint32 curInt;
        fdat7Stream >> curInt;
        fdat7Checksum += curInt;
        bytes_done += 4;
    }

    fdat7Stream << fdat7Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 4 (FDAT 10)...");

    fdat10Stream.device()->reset();
    quint32 fdat10Checksum = 0x12345678;
    quint64 fdat10Stop = fdat10Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat10Stop)
    {
        quint32 curInt;
        fdat10Stream >> curInt;
        fdat10Checksum += curInt;
        bytes_done += 4;
    }

    fdat10Stream << fdat10Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 5 (FDAT 13)...");

    fdat13Stream.device()->reset();
    quint32 fdat13Checksum = 0x12345678;
    quint64 fdat13Stop = fdat13Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat13Stop)
    {
        quint32 curInt;
        fdat13Stream >> curInt;
        fdat13Checksum += curInt;
        bytes_done += 4;
    }

    fdat13Stream << fdat13Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 6 (FDAT 16)...");

    fdat16Stream.device()->reset();
    quint32 fdat16Checksum = 0x12345678;
    quint64 fdat16Stop = fdat16Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat16Stop)
    {
        quint32 curInt;
        fdat16Stream >> curInt;
        fdat16Checksum += curInt;
        bytes_done += 4;
    }

    fdat16Stream << fdat16Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 7 (FDAT 19)...");

    fdat19Stream.device()->reset();
    quint32 fdat19Checksum = 0x12345678;
    quint64 fdat19Stop = fdat19Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat19Stop)
    {
        quint32 curInt;
        fdat19Stream >> curInt;
        fdat19Checksum += curInt;
        bytes_done += 4;
    }

    fdat19Stream << fdat19Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 8 (FDAT 22)...");

    fdat22Stream.device()->reset();
    quint32 fdat22Checksum = 0x12345678;
    quint64 fdat22Stop = fdat22Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat22Stop)
    {
        quint32 curInt;
        fdat22Stream >> curInt;
        fdat22Checksum += curInt;
        bytes_done += 4;
    }

    fdat22Stream << fdat22Checksum;

    emit statusUpdate(QDateTime::currentDateTime().time().toString() + ": Calculating checksum for map 9 (FDAT 25)...");

    fdat25Stream.device()->reset();
    quint32 fdat25Checksum = 0x12345678;
    quint64 fdat25Stop = fdat25Array.size() - 4;
    bytes_done = 0;

    while (bytes_done < fdat25Stop)
    {
        quint32 curInt;
        fdat25Stream >> curInt;
        fdat25Checksum += curInt;
        bytes_done += 4;
    }

    fdat25Stream << fdat25Checksum;
}

void Randomizer::setNoEmptyDrops(const bool &_noEmptyDrops)
{
    noEmptyDrops = _noEmptyDrops;
}

QByteArray &Randomizer::getFile()
{
    for (int it = 0x11000; it < 0x11000 + 0x7000; it++)
        fdat[it] = fdat1Array[it - 0x11000];

    for (int it = 0x2A000; it < 0x2A000 + 0x7000; it++)
        fdat[it] = fdat4Array[it - 0x2A000];

    for (int it = 0x44000; it < 0x44000 + 0x7000; it++)
        fdat[it] = fdat7Array[it - 0x44000];

    for (int it = 0x5D000; it < 0x5D000 + 0x7000; it++)
        fdat[it] = fdat10Array[it - 0x5D000];

    for (int it = 0x76000; it < 0x76000 + 0x7000; it++)
        fdat[it] = fdat13Array[it - 0x76000];

    for (int it = 0x8F800; it < 0x8F800 + 0x7000; it++)
        fdat[it] = fdat16Array[it - 0x8F800];

    for (int it = 0xA9000; it < 0xA9000 + 0x7000; it++)
        fdat[it] = fdat19Array[it - 0xA9000];

    for (int it = 0xC1800; it < 0xC1800 + 0x7000; it++)
        fdat[it] = fdat22Array[it - 0xC1800];

    for (int it = 0xDB000; it < 0xDB000 + 0x7000; it++)
        fdat[it] = fdat25Array[it - 0xDB000];

    return fdat;
}

quint8 Randomizer::getRandomItem()
{
    // I don't know why, but I have to initialize it like this or it doesn't work.
    quint8 item = 0;

    // Loop to get rid of invalid items
    do
    {
        item = rng.generate() % 119;
    }
    while ((item == 0 && noEmptyDrops) || !isValidItem(item));

    return item;
}

quint8 Randomizer::getRandomMonster()
{
    return rng.generate() % 31;
}

bool Randomizer::isValidItem(const quint8 &item)
{
    if (item == 0x7 || item == 0x8 || item == 0x12 || item == 0x13 || item == 0x14 || item == 0x1b || item == 0x21 || item == 0x28 || item == 0x2e || item == 0x34 || (item > 0x3b && item < 0x43) || item == 0x46 || item == 0x51 || item == 0x62 || item == 0x6e || item > 0x76)
        return false;

    return true;
}
