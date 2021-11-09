#include "core/kfmterror.h"
#include "tfile.h"
#include "utilities.h"
#include <QBuffer>
#include <QCryptographicHash>
#include <QDebug>
#include <QDir>
#include <QtEndian>
#include <cmath>

TFile::TFile(const QString & filename) : 
    fileName(filename.mid(filename.lastIndexOf(QRegExp("[\\/]")) + 1))
{
    QFile fileHandle(filename);
    if (fileHandle.open(QIODevice::ReadOnly)) load(fileHandle.readAll());
}

QString TFile::getBaseFilename() const
{
    return fileName.left(getFilename().indexOf('.'));
}

QString TFile::getFilename() const
{
    return fileName;
}

QByteArray &TFile::getFile(size_t index)
{
    if (index > files.size())
        KFMTError::fatalError(QString("TFile: getFile called for out-of-bounds true file number %1").arg(index));
    
    return files.at(index);
}

QString TFile::getFiletype(QByteArray &file) const
{
    if (Utilities::fileIsTMD(file)) return QStringLiteral("TMD");
    if (Utilities::fileIsTIM(file)) return QStringLiteral("TIM");
    if (Utilities::fileIsVH(file)) return QStringLiteral("VH");
    if (Utilities::fileIsSEQ(file)) return QStringLiteral("SEQ");
    if (Utilities::fileIsVB(file)) return QStringLiteral("VB");
    if (Utilities::fileIsMAP1(file)) return QStringLiteral("MAP1");
    if (Utilities::fileIsMAP2(file)) return QStringLiteral("MAP2");
    if (Utilities::fileIsMAP3(file)) return QStringLiteral("MAP3");
    if (Utilities::fileIsRTIM(file)) return QStringLiteral("RTIM");
    if (Utilities::fileIsRTMD(file)) return QStringLiteral("RTMD");
    if (Utilities::fileIsMO(file)) return QStringLiteral("MO");
    if (Utilities::fileIsGameDB(file)) return QStringLiteral("GAMEDB");

    return QStringLiteral("DATA");
}

size_t TFile::getNumFiles() const
{
    return files.size();
}

void TFile::writeTo(QFile &outFile) const
{
    // Create data blob
    QByteArray dataBlob;
    
    std::vector<uint16_t> newTrueOffsets;
    
    for (const auto &file : files)
    {
        QByteArray alignedFile;
        auto alignedSize = static_cast<uint16_t>(file.size() / 2048u);
        if (file.size() % 2048u != 0)
            alignedSize += 1;
        
        alignedFile.resize(alignedSize * 2048u);
        alignedFile.fill(0);
        mempcpy(alignedFile.data(), file.data(), file.size());
        
        newTrueOffsets.push_back((dataBlob.size() + 2048u) / 2048u);
        dataBlob.append(file);
    }
    
    // Add EOF to the offset vector
    newTrueOffsets.push_back((dataBlob.size() + 2048u) / 2048u);
    
    // Create stream for writing to the file
    QDataStream outStream(&outFile);
    outStream.setByteOrder(QDataStream::LittleEndian);
    
    // Write number of (fake) files
    outStream << static_cast<uint16_t>(fileMap.size() - 1);
    
    // Write pointers
    for (size_t fileNum = 0; fileNum < fileMap.size(); fileNum++)
        outStream << newTrueOffsets.at(fileMap.find(fileNum)->second);
    
    // Pad out pointer table to 2048 bytes.
    // FIXME: I think this is pretty slow, but I can't think of a way around it right now.
    while(outStream.device()->pos() < 2048)
        outStream << static_cast<uint8_t>(0);
    
    outStream.writeRawData(dataBlob.data(), dataBlob.size());
}

void TFile::load(const QByteArray &tFileBlob)
{
    unsigned short offset = 0;
    unsigned int fileNum = 0;
    unsigned int trueFileNum = 0;

    QDataStream stream(tFileBlob);
    stream.setByteOrder(QDataStream::LittleEndian); // The PSX is little-endian
    
    // Read and convert offsets, excluding duplicates
    unsigned short nFiles;
    stream >> nFiles;
    fileOffsets.reserve(nFiles);
    for (unsigned int i = 0; i <= nFiles; i++) // The <= is so that the EOF offset is included.
    {
        unsigned int convertedOffset = 0; // Offsets must be multiplied by 2048.
        stream >> offset;
        convertedOffset = offset * 2048;
        fileNum++;
        // If the offset vector is empty or if this offset isn't a duplicate of the last one, 
        // we add it to the vector
        if (fileOffsets.empty() || fileOffsets.back() != convertedOffset)
        {
            fileOffsets.push_back(convertedOffset);
            // If we inserted this offset, we increase the amount of true files, which here
            // also serves as an index to which true file this is
            trueFileNum++;
        }

        // We register what true file this index points to
        fileMap[fileNum - 1] = trueFileNum - 1;
    }
    
    // Read the files in the T file
    for (auto fileOffset = fileOffsets.begin() + 1; fileOffset != fileOffsets.end(); fileOffset++)
    {
        files.push_back(tFileBlob.mid(*(fileOffset - 1), *fileOffset - *(fileOffset - 1)));
    }

    loaded = true;
}
