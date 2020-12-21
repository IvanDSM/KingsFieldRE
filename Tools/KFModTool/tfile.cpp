﻿#include "../common/prettynamer.h"
#include "kfmterror.h"
#include "tfile.h"
#include "utilities.h"
#include <QBuffer>
#include <QCryptographicHash>
#include <QDebug>
#include <QDir>
#include <QtEndian>

TFile::TFile(const QString & filename) : 
    fileName(filename.mid(filename.lastIndexOf(QRegExp("[\\/]")) + 1))
{
    QFile fileHandle(filename);
    if (fileHandle.open(QIODevice::ReadOnly))
    {
        auto wholeFile = fileHandle.readAll();
        fileHandle.close();
        
        hash = QCryptographicHash::hash(wholeFile, QCryptographicHash::Algorithm::Md5).toHex();
        load(wholeFile);
    }
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
    if (Utilities::fileIsTMD(file))
        return "TMD";
    if (Utilities::fileIsTIM(file))
        return "TIM";
    if (Utilities::fileIsVH(file))
        return "VH";
    if (Utilities::fileIsSEQ(file))
        return "SEQ";
    if (Utilities::fileIsVB(file))
        return "VB";
    if (Utilities::fileIsRTIM(file))
        return "RTIM";
    if (Utilities::fileIsRTMD(file))
        return "RTMD";
    if (Utilities::fileIsMO(file))
        return "MO";
    if (Utilities::fileIsMAP1(file))
        return "MAP1";
    if (Utilities::fileIsMAP2(file))
        return "MAP2";
    if (Utilities::fileIsMAP3(file))
        return "MAP3";
    if (Utilities::fileIsGameDB(file))
        return "GAMEDB";

    return "DATA";
}

QByteArray TFile::getHash() const
{
    return hash;
}

size_t TFile::getNumFiles() const
{
    return files.size();
}

QString TFile::getPrettyName(size_t index) const
{
    auto prettyNameIt = prettyMap.find(getFilename() + QString::number(index));
    
    if (prettyNameIt != prettyMap.end())
        return prettyNameIt->second;
    
    return getFilename() + ' ' + QString::number(index);
}

void TFile::writeFileMap()
{
    QDir outputDir(getBaseFilename());
    if (!outputDir.exists())
        outputDir.mkpath(".");

    qInfo() << "Writing file map for" << getFilename();

    QFile mapOutFile(outputDir.path() + QDir::separator() + getBaseFilename() + "_MAP.csv");
    if (!mapOutFile.open(QIODevice::WriteOnly))
        qInfo() << "Creating map for " << getFilename() << " failed!";
    else
    {
        QTextStream mapWriteStream(&mapOutFile);
        mapWriteStream << getBaseFilename() << ",MAP" << "\n";
        for (const auto &mapping : fileMap)
            mapWriteStream << mapping.first << "," << mapping.second << "\n";
    }

    
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
    for (auto offset = fileOffsets.begin() + 1; offset != fileOffsets.end(); offset++)
    {
        files.push_back(tFileBlob.mid(*(offset - 1), *offset - *(offset - 1)));
    }

    PrettyNamer prettyNamer; ///< Instance of the PrettyNamer class.
    prettyMap = prettyNamer.getPrettyMap(hash);
    
    loaded = true;
}
