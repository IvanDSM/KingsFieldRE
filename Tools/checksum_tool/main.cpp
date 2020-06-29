#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    qInfo() << "checksum_tool - IvanDSM 2020";

    if (argc < 2)
    {
        qInfo() << "No file provided. Exiting.";
        return 1;
    }

    QFile inFile(argv[1]);
    if (!inFile.open(QIODevice::ReadOnly))
    {
        qInfo() << "Couldn't open the file. Exiting.";
        return 1;
    }

    QDataStream inStream(&inFile);
    inStream.setByteOrder(QDataStream::LittleEndian);

    qint64 sizeInInts = inFile.size() / 4;
    qint32 checkSum = 0x12345678;

    for (qint64 curIntIndex = 0; curIntIndex < sizeInInts - 1; curIntIndex++)
    {
        qint32 curInt;
        inStream >> curInt;
        checkSum += curInt;
    }

    qint32 fileCheckSum;
    inStream >> fileCheckSum;

    qInfo() << "The file reported its checksum as being" << QString::number(fileCheckSum, 16);
    qInfo() << "checksum_tool calculated the file checksum as" << QString::number(checkSum, 16);

    return 0;
}
