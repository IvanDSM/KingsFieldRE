#include <QBuffer>
#include <QDebug>
#include <QDir>
#include <QtEndian>
#include "tfile.h"

TFile::TFile(const QString &filename)
{
    QFile fileHandle(filename);
    if (fileHandle.open(QIODevice::ReadOnly))
    {
        file = fileHandle.readAll();
        fileName = fileHandle.fileName().mid(fileHandle.fileName().lastIndexOf(QDir::separator()) + 1);
        fileHandle.close();
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

            fileMap[fileNum] = trueFileNum;
        }
    }
    else
        nFiles = 0;
}

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
        else if (curFileData.mid(8).left(4) == curFileData.left(4)) // RTIM
            curFileExt = "RTIM";
        else
            curFileExt = "DAT";

        QString prettyName = "";

        auto prettyNameIt = prettyMapper.find(getFilename() + QString::number(index));
        if (prettyNameIt != prettyMapper.end())
            prettyName = "_" + prettyNameIt->second;

        // FIXME: The way we're making the current filename is kind of ugly and probably slow! There has to be a better way to do this.

        curFileName = outputDir.path() + QDir::separator();

        curFileName += getFilename().leftRef(getFilename().indexOf('.'));

        curFileName += "_I" + QString::number(index);

        curFileName += prettyName;

        curFileName += "_OS" + QString::number(fileOffsets[index] / 2048);

        curFileName += "_TOS" + QString::number(fileOffsets[index]);

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

std::vector<unsigned int> TFile::getFileOffsets()
{
    // FIXME: This is ugly, remake this when it's not 6 in the morning.
    std::vector<unsigned int> deMultiplied;

    std::transform(fileOffsets.begin(), fileOffsets.end(),
                   std::back_inserter(deMultiplied),
                   [] (unsigned int multipliedOffset) {return multipliedOffset / 2048;});

    return deMultiplied;
}

std::vector<unsigned int> TFile::getTrueFileOffsets()
{
    return fileOffsets;
}

unsigned int TFile::getNumFiles()
{
    return nFiles;
}

unsigned int TFile::getTrueNumFiles()
{
    return fileOffsets.size();
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
        for (auto mapping : fileMap)
            mapWriteStream << mapping.first << "," << mapping.second << "\n";
    }
}
