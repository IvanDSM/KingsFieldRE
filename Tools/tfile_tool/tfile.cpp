﻿#include "prettynamer.h"
#include "tfile.h"
#include <QBuffer>
#include <QCryptographicHash>
#include <QDebug>
#include <QDir>
#include <QtEndian>

bool TFile::extractFiles()
{
    QDir outputDir(getFilename().left(getFilename().indexOf('.')));
    if (!outputDir.exists())
        outputDir.mkpath(".");

    QByteArray curFileData;
    QString curFileExt;
    QString curFileName;
    unsigned int index = 0;
    while (index < getTrueNumFiles() - 1) // -1 so we don't try to extract starting from EOF
    {
        curFileData = file.mid(fileOffsets[index], fileOffsets[index + 1] - fileOffsets[index]);

        // We try to identify the file type.
        QByteArray signatureBytes = curFileData.left(4); // Signature in PSX format

        if (signatureBytes.compare(QByteArray::fromHex("41000000")) == 0)
            curFileExt = "TMD";
        else if (signatureBytes.compare(QByteArray::fromHex("10000000")) == 0)
            curFileExt = "TIM";
        else if (signatureBytes.compare(QByteArray::fromHex("70424156")) == 0)
            curFileExt = "VH";
        else if (signatureBytes.compare(QByteArray::fromHex("70514553")) == 0)
            curFileExt = "SEQ";
        else if (curFileData.left(16).compare(QByteArray::fromHex("00000000000000000000000000000000")) == 0) // FIXME: Shitty detection
            curFileExt = "VB";
        else if (curFileData.mid(8).left(8) == curFileData.left(8))
            curFileExt = "RTIM";
        else if (isRTMD(curFileData))
            curFileExt = "RTMD";
        else if (isMO(curFileData))
            curFileExt = "MO";
        else
            curFileExt = "DAT";

        QString prettyName = "";

        auto prettyNameIt = prettyMap.find(getFilename() + QString::number(index));
        if (prettyNameIt != prettyMap.end())
            prettyName = "_" + prettyNameIt->second;

        // FIXME: The way we're making the current filename is kind of ugly and probably slow!
        // There has to be a better way to do this.

        curFileName = outputDir.path() + QDir::separator();

        curFileName += getFilename().leftRef(getFilename().indexOf('.'));

        curFileName += "_I" + QString::number(index);

        curFileName += prettyName;

        curFileName += "_OS0x" + QString::number(fileOffsets[index], 16).toUpper();

        curFileName += "." + curFileExt;

        qInfo() << "Extracting" << curFileName << "...";

        QFile curFile(curFileName);
        if (!curFile.open(QIODevice::WriteOnly))
        {
            qInfo() << "Extracting" << curFileName << "failed!";
            return false;
        }

        curFile.write(curFileData);
        curFile.close();

        index++;
    }

    return true;
}

QString TFile::getBaseFilename()
{
    return fileName.left(getFilename().indexOf('.'));
}

QString TFile::getFilename()
{
    return fileName;
}

QByteArray TFile::getFile(unsigned int trueFileNumber) const
{
    QByteArray desiredFile;

    if (trueFileNumber < getTrueNumFiles())
    {
        desiredFile = file.mid(fileOffsets[trueFileNumber],
                               fileOffsets[trueFileNumber + 1] - fileOffsets[trueFileNumber]);
    }

    return desiredFile;
}

std::vector<unsigned int> TFile::getFileOffsets()
{
    // FIXME: This is ugly, remake this when it's not 6 in the morning.
    std::vector<unsigned int> deMultiplied;

    std::transform(fileOffsets.begin(), fileOffsets.end(),
                   std::back_inserter(deMultiplied),
                   [] (unsigned int multipliedOffset) {return multipliedOffset / 2048;});

    return deMultiplied;
}

QByteArray &TFile::getHash()
{
    return hash;
}

std::vector<unsigned int> TFile::getTrueFileOffsets()
{
    return fileOffsets;
}

unsigned int TFile::getNumFiles()
{
    return nFiles;
}

unsigned int TFile::getTrueNumFiles() const
{
    return fileOffsets.size();
}

void TFile::writeFile(const QByteArray &newFile, int index)
{
    if (static_cast<unsigned int>(index) >= getTrueNumFiles())
        return;
    for (int pos = 0; pos < newFile.size(); pos++)
        file[fileOffsets[index] + pos] = newFile[pos];
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

bool TFile::isMO(const QByteArray & file)
{
    quint32 tmdOff = *reinterpret_cast<quint32 *>(file.mid(8,4).data());
    quint8 tmdSig = 0;
    if (tmdOff < static_cast<quint32>(file.size()))
        tmdSig = file.at(tmdOff);
    
    return tmdSig == 0x41;
}

bool TFile::isRTMD(const QByteArray & file)
{
    return file.left(4).compare(QByteArray::fromHex("00000000")) == 0 &&
                     (file.mid(4, 4).compare(QByteArray::fromHex("12000000")) == 0 ||
                      file.mid(4, 4).compare(QByteArray::fromHex("10000000")) == 0);
}

void TFile::load()
{
    if (file.isEmpty())
        nFiles = 0;
    else
    {
        unsigned short offset = 0;
        QBuffer fileBuffer(&file);
        fileBuffer.open(QIODevice::ReadOnly);

        unsigned int fileNum = 0;
        unsigned int trueFileNum = 0;

        stream.setDevice(&fileBuffer);
        stream.setByteOrder(QDataStream::LittleEndian); // The PSX is little-endian
        stream >> nFiles;
        for (unsigned int i = 0; i <= nFiles; i++) // The <= is so that the EOF offset is included.
        {
            unsigned int convertedOffset = 0; // Offsets must be multiplied by 2048.
            stream >> offset;
            convertedOffset = offset * 2048;
            fileNum++;
            if (fileOffsets.empty() || fileOffsets.back() != convertedOffset)
            {
                fileOffsets.push_back(convertedOffset);
                trueFileNum++;
            }

            fileMap[fileNum - 1] = trueFileNum - 1;
        }

        hash = QCryptographicHash::hash(file, QCryptographicHash::Algorithm::Md5).toHex();
        PrettyNamer prettyNamer; ///< Instance of the PrettyNamer class.
        prettyMap = prettyNamer.getPrettyMap(hash);
    }
}
