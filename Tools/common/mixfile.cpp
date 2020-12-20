#include "mixfile.h"
#include <QDataStream>

MIXFile::MIXFile(const QString &filename) : 
    fileName(filename.mid(filename.lastIndexOf(QRegExp("[\\/]")) + 1))
{
    if (filename.endsWith("TIM") || filename.endsWith("TMD"))
        hasSizes = false;
    QFile fileHandle(filename);
    if (fileHandle.open(QIODevice::ReadOnly))
    {
        load(fileHandle);
        fileHandle.close();
    }
    
}

void MIXFile::write(const QDir &outDir)
{
    QFile outFile(outDir.path() + fileName);
    if (!outFile.open(QIODevice::WriteOnly))
        return;
    for (const auto &file : files)
        outFile.write(file);
    outFile.close();
}

void MIXFile::load(QFile &fileHandle)
{
    QDataStream fileStream(&fileHandle);
    fileStream.setByteOrder(QDataStream::LittleEndian);
    if (hasSizes)
        loadHasSizes(fileStream);
    else
        loadNoSizes(fileStream);
    loaded = true;
}

void MIXFile::loadHasSizes(QDataStream &stream)
{
    while(!stream.atEnd())
    {
        // FIXME: Can we use QDataStream &operator>>(QDataStream &in, QBitArray &ba) here instead?
        uint32_t size;
        stream >> size;
        QByteArray file;
        file.resize(size);
        stream.readRawData(file.data(), size);
        files.push_back(file);
    }
}

void MIXFile::loadNoSizes(QDataStream &stream)
{
    QByteArray signature;
    if (fileName.endsWith("TIM"))
        signature = QByteArray::fromHex("1000000008000000");
    else if (fileName.endsWith("TMD"))
        signature = QByteArray::fromHex("4100000000000000");
    
    std::vector<size_t> sizes;
    qsizetype curOffset = 1;
    qsizetype lastOffset = 0;
    
    QByteArray entireFile = stream.device()->readAll();
    stream.device()->reset();
    
    while (curOffset != -1)
    {
        curOffset = entireFile.indexOf(signature, curOffset);
        if (curOffset != -1)
        {
            sizes.push_back(curOffset - lastOffset);
            lastOffset = curOffset;
        }
    }
    
    for (auto size : sizes)
    {
        QByteArray file;
        file.resize(size);
        stream.readRawData(file.data(), size);
        files.push_back(file);
    }
}
