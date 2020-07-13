#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <QByteArray>
#include <QDataStream>
#include <iostream>

class Checksum
{
public:
    static void calculateAndWriteChecksum(QByteArray& file)
    {
        auto ints = file.size() / 4 - 1;
        QDataStream fileStream(&file, QIODevice::ReadWrite);
        fileStream.setByteOrder(QDataStream::LittleEndian);
        quint32 checksum = 0x12345678;
        quint32 curInt = 0;
        for (auto curIntIndex = 0; curIntIndex < ints; curIntIndex++)
        {
            fileStream >> curInt;
            checksum += curInt;
        }
        fileStream << checksum;
    }
};

#endif // CHECKSUM_H
