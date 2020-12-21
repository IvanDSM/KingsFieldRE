#include "kfmterror.h"
#include "mixfile.h"
#include "utilities.h"
#include <QDataStream>

MIXFile::MIXFile(const QString &filename) : 
    fileName(filename.mid(filename.lastIndexOf(QRegExp("[\\/]")) + 1))
{
    QFile fileHandle(filename);
    if (!fileHandle.open(QIODevice::ReadOnly))
        return;
    
    auto wholeFile = fileHandle.readAll();
    fileHandle.close();
    
    load(wholeFile);
}

QByteArray &MIXFile::getFile(size_t index)
{
    if (index > files.size())
        KFMTError::fatalError(QString("MIXFile: getFile called for out-of-bounds file number %1").arg(index));
    
    return files[index];
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

void MIXFile::load(const QByteArray &file)
{
    // MIX files that contain TIMs or TMDs don't have a size value before the files
    // So if a MIX file is not recognized as a TIM and is not recognized as a TMD,
    // it does not store the size for each file.
    hasSizes = !Utilities::fileIsTIM(file) && !Utilities::fileIsTMD(file);
    if (hasSizes)
        loadHasSizes(file);
    else
        loadNoSizes(file);
    loaded = true;
}

void MIXFile::loadHasSizes(const QByteArray &mixFile)
{
    QDataStream stream(mixFile);
    stream.setByteOrder(QDataStream::LittleEndian);
    
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

void MIXFile::loadNoSizes(const QByteArray &mixFile)
{
    // Get the first byte so we know if this is a TIM or a TMD MIX file
    const uint8_t signature = mixFile.at(0);
    
    // Create a vector of offsets to the files and a variable for finding offsets
    std::vector<size_t> offsets;
    qsizetype curOffset = 0;
    
    // Get all offsets that match the signature
    while (curOffset + 8 < mixFile.size())
    {
        auto curOffsetSignature = mixFile.mid(curOffset, 8);
        if (signature == 0x10 && Utilities::fileIsTIM(curOffsetSignature))
        {
            // FIXME: I hate this block of code so much
            // Skip the TIM's contents
            uint32_t clutSize = 0;
            uint32_t pDataSize = 0;
            // If the pixel mode is Direct 15 or 24 bit, we have no CLUT.
            auto data = mixFile.data() + curOffset;
            uint8_t timFlag = data[4];
            if (timFlag == 0x02 || timFlag == 0x03)
                pDataSize = *reinterpret_cast<const uint32_t *>(&data[8]);
            else // Otherwise, we do have a CLUT
            {
                clutSize = *reinterpret_cast<const uint32_t *>(&data[8]);
                pDataSize = *reinterpret_cast<const uint32_t *>(&data[8 + clutSize]);
            }
            
            if (clutSize + pDataSize > 0)
                offsets.push_back(curOffset);
            curOffset += clutSize + pDataSize;
        }
        else if (signature == 0x41 && Utilities::fileIsTMD(curOffsetSignature))
        {
            offsets.push_back(curOffset);
        }
        curOffset += 8;
    }
    
    // Add EOF to list of offsets
    offsets.push_back(mixFile.size());
    
    // Read the individual files from the MIX file based on the offsets.
    for (auto offset = offsets.cbegin(); offset != offsets.cend() - 1; offset++)
        files.emplace_back(mixFile.mid(*offset, *(offset + 1)));
}
