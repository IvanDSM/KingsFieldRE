#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    qInfo() << "checksum_tool - IvanDSM 2020";

    if (argc < 2)
    {
        qInfo() << "No files provided. Exiting.";
        return 1;
    }

    for (int argi = 1; argi < argc; argi++)
    {
        QFile inFile(argv[argi]);
        auto filename = inFile.fileName();
        filename = filename.left(filename.indexOf(QRegExp("[\\/]")));
        if (!inFile.open(QIODevice::ReadOnly))
        {
            qInfo() << "Couldn't open" << filename << ". Exiting.";
            return 1;
        }

        QDataStream inStream(&inFile);
        inStream.setByteOrder(QDataStream::LittleEndian);

        qint64 sizeInInts = inFile.size() / 4;
        quint32 checkSum = 0x12345678;

        for (qint64 curIntIndex = 0; curIntIndex < sizeInInts - 1; curIntIndex++)
        {
            qint32 curInt;
            inStream >> curInt;
            checkSum += curInt;
        }

        quint32 fileCheckSum;
        inStream >> fileCheckSum;

        inFile.close();

        qInfo() << filename << "reported its checksum as being" << QString::number(fileCheckSum, 16);
        qInfo() << "checksum_tool calculated its checksum as" << QString::number(checkSum, 16);

        // The \n's here are on purpose so that we get some spacing between files when doing batches
        if (fileCheckSum == checkSum)
            qInfo() << "They match!\n";
        else
            qInfo() << "They don't match!\n";
    }

    return 0;
}
