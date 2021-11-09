#include "kfmtfile.h"
#include "kfmterror.h"
#include "utilities.h"

KFMTFile::KFMTFile(const QString& srcDir, const QString& path, FileType fileType)
    : filePath(path), fileType(fileType)
{
    QFile fileHandle(srcDir + QDir::separator() + path);
    switch (fileType)
    {
        case FileType::MIX:
            dataType = DataType::Container;
            loadMIX(fileHandle);
            break;
        case FileType::Raw: {
            if (!fileHandle.open(QIODevice::ReadOnly)) return;
            rawData = fileHandle.readAll();
            detectDataType();
            break;
        }
        case FileType::T:
            dataType = DataType::Container;
            loadT(fileHandle);
            break;
    }
}

KFMTFile::KFMTFile(const QString& path, const QByteArray& data)
    : filePath(path), rawData(data), fileType(FileType::Raw)
{
    detectDataType();
}

void KFMTFile::extractTo(const QDir& outDir)
{
    if (dataType != DataType::Container)
    {
        KFMTError::error("KFMTFile::extractTo: Called on non-container file!");
        return;
    }

    size_t fileIndex = 0;
    for (const auto& subFile : subFiles)
    {
        auto fn = filePath.mid(filePath.lastIndexOf(QRegExp(QStringLiteral("[\\/]"))) + 1)
                  + QString::number(fileIndex) + '.' + subFile.getFileExtension();
        QFile output(outDir.filePath(fn));
        if (!output.open(QIODevice::WriteOnly))
            KFMTError::fatalError("Unable to open output file for " + output.fileName());
        output.write(subFile.rawData);
        output.close();
        fileIndex++;
    }
}

const QString& KFMTFile::getFileExtension() const
{
    static const auto data = QStringLiteral("data");
    static const auto exe = QStringLiteral("exe");
    static const auto gamedb = QStringLiteral("gamedb");
    static const auto maptile = QStringLiteral("maptile");
    static const auto mapdb = QStringLiteral("mapdb");
    static const auto mapscript = QStringLiteral("mapscript");
    static const auto mim = QStringLiteral("mim");
    static const auto mo = QStringLiteral("mo");
    static const auto rtmd = QStringLiteral("rtmd");
    static const auto rtim = QStringLiteral("rtim");
    static const auto tim = QStringLiteral("tim");
    static const auto tmd = QStringLiteral("tmd");

    if (Utilities::fileIsPSXEXE(rawData)) return exe;
    if (Utilities::fileIsTMD(rawData)) return tmd;
    if (Utilities::fileIsTIM(rawData)) return tim;
    if (Utilities::fileIsRTIM(rawData)) return rtim;
    if (Utilities::fileIsRTMD(rawData)) return rtmd;
    if (Utilities::fileIsMIM(rawData)) return mim;
    if (Utilities::fileIsMO(rawData)) return mo;
    if (Utilities::fileIsMAP1(rawData)) return maptile;
    if (Utilities::fileIsMAP2(rawData)) return mapdb;
    if (Utilities::fileIsMAP3(rawData)) return mapscript;
    if (Utilities::fileIsGameDB(rawData)) return gamedb;

    return data;
}

void KFMTFile::writeFile(const QDir& outDir)
{
    QString dirToCreate = filePath.left(filePath.lastIndexOf(QRegExp(QStringLiteral("[\\/]"))) + 1);
    outDir.mkpath(dirToCreate);

    QFile output(outDir.filePath(filePath));
    if (!output.open(QIODevice::WriteOnly))
        KFMTError::fatalError("Unable to open output file for " + filePath);

    switch (fileType)
    {
        case FileType::MIX: writeMIX(output); break;
        case FileType::Raw: output.write(rawData); break;
        case FileType::T: writeT(output); break;
    }

    output.close();
}

void KFMTFile::detectDataType()
{
    if (Utilities::fileIsPSXEXE(rawData))
        dataType = DataType::GameEXE;
    else if (Utilities::fileIsTMD(rawData))
        dataType = DataType::Model;
    else if (Utilities::fileIsTIM(rawData) || Utilities::fileIsRTIM(rawData))
        dataType = DataType::TextureDB;
    else if (Utilities::fileIsRTMD(rawData) || Utilities::fileIsMO(rawData))
        dataType = DataType::Model;
    else if (Utilities::fileIsMAP1(rawData))
        dataType = DataType::MapTilemap;
    else if (Utilities::fileIsMAP2(rawData))
        dataType = DataType::MapDB;
    else if (Utilities::fileIsMAP3(rawData))
        dataType = DataType::MapScript;
    else if (Utilities::fileIsGameDB(rawData))
        dataType = DataType::GameDB;
    else
        dataType = DataType::Unknown;
}

void KFMTFile::recalculateChecksum()
{
    // FIXME: Use direct pointer stuff or std::accumulate to take advantage of vectorization.
    // Should also help avoid QDataStream overhead.
    auto ints = rawData.size() / 4 - 1;
    QDataStream fileStream(&rawData, QIODevice::ReadWrite);
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

void KFMTFile::loadMIX(QFile& fileHandle)
{
    if (!fileHandle.open(QIODevice::ReadOnly)) return;
    const auto file = fileHandle.readAll();

    // MIX files that contain MIMs, TIMs or TMDs don't have a size value before the files
    // So if a MIX file is not recognized as a MIM, TIM or TMD, it does not store the
    // size for each file.

    if (!Utilities::fileIsMIM(file.mid(4)) && !Utilities::fileIsTIM(file)
        && !Utilities::fileIsTMD(file))
        containerType = ContainerType::MIX_HasSizes;
    else if (Utilities::as<uint32_t>(file) == 0x06 || Utilities::as<uint32_t>(file) == 0x07)
    {
        containerType = ContainerType::MIX_MIMCollection;
        mixMimSignature = Utilities::as<uint32_t>(file);
    }
    else
        containerType = ContainerType::MIX_NoSizes;

    QDataStream stream(file);
    stream.setByteOrder(QDataStream::LittleEndian);

    if (containerType == ContainerType::MIX_HasSizes)
    {
        size_t fileNo = 0;
        while (!stream.atEnd())
        {
            // FIXME: Can we use QDataStream &operator>>(QDataStream &in, QBitArray &ba) here instead?
            uint32_t size;
            stream >> size;
            QByteArray file;
            file.resize(size);
            stream.readRawData(file.data(), size);
            subFiles.emplace_back(filePath + QString::number(fileNo), file);
            fileNo++;
        }
    }
    else
    {
        // Create a vector of offsets to the files and a variable for finding offsets
        std::vector<size_t> offsets;
        size_t curOffset = 0;

        // Get all offsets that match the signature
        while (curOffset + 8 < file.size())
        {
            auto curOffsetSignature = file.mid(curOffset, 8);
            if (Utilities::fileIsTIM(curOffsetSignature))
            {
                // FIXME: I hate this block of code so much
                // Skip the TIM's contents
                uint32_t clutSize = 0;
                uint32_t pDataSize = 0;
                // If the pixel mode is Direct 15 or 24 bit, we have no CLUT.
                uint8_t timFlag = Utilities::as<uint8_t>(file, curOffset + 4u);
                if (timFlag == 0x02 || timFlag == 0x03)
                    pDataSize = Utilities::as<uint32_t>(file, curOffset + 8u);
                else // Otherwise, we do have a CLUT
                {
                    clutSize = Utilities::as<uint32_t>(file, curOffset + 8u);
                    pDataSize = Utilities::as<uint32_t>(file, curOffset + 8u + clutSize);
                }

                if (clutSize + pDataSize > 0) offsets.push_back(curOffset);
                curOffset += clutSize + pDataSize;
            }
            else if (Utilities::fileIsTMD(curOffsetSignature))
                offsets.push_back(curOffset);
            else if (Utilities::fileIsMIM(
                         file.mid(curOffset, Utilities::as<uint32_t>(curOffsetSignature))))
            {
                offsets.push_back(curOffset);
                curOffset += Utilities::as<uint32_t>(curOffsetSignature) - 8;
            }
            curOffset += 4u;
        }

        // Add EOF to list of offsets
        offsets.push_back(file.size());

        // Read the individual files from the MIX file based on the offsets.
        for (auto offset = offsets.cbegin(), nextOffset = offsets.cbegin() + 1;
             nextOffset != offsets.cend();
             offset++, nextOffset++)
            subFiles.emplace_back(filePath
                                      + QString::number(std::distance(offsets.cbegin(), offset)),
                                  file.mid(*offset, *nextOffset - *offset));
    }
}

void KFMTFile::loadT(QFile& fileHandle)
{
    // BUG: KF2 RTMD.T does not load RTMD.T8 for some reason!!!

    containerType = ContainerType::T;

    if (!fileHandle.open(QIODevice::ReadOnly)) return;

    QDataStream stream(&fileHandle);
    stream.setByteOrder(QDataStream::LittleEndian);

    uint16_t nFiles;
    stream >> nFiles;
    std::vector<uint32_t> offsets;
    offsets.reserve(nFiles);

    uint16_t offset = 0;
    size_t fileNum = 0;
    size_t trueFileNum = 0;
    for (uint16_t i = 0; i <= nFiles; i++)
    {
        stream >> offset;
        if (offset == 0) break;

        // If the offset vector is empty or if this offset isn't a duplicate of the last one,
        // we add it to the vector
        if (offsets.empty() || offsets.back() != static_cast<uint32_t>(offset))
        {
            // Offsets must be multiplied by 2048.
            offsets.push_back(static_cast<uint32_t>(offset));

            // If we inserted this offset, we increase the amount of true files, which here
            // also serves as an index to which true file this is
            trueFileNum++;
        }

        // We register what true file this index points to
        tFileMap[fileNum] = trueFileNum - 1;

        fileNum++;
    }

    // Multiply all offsets by 2048
    for (auto& o : offsets) o *= 2048u;

    // Preallocate the subfile vector to avoid overhead
    subFiles.reserve(trueFileNum);

    // Read the files in the T file
    fileHandle.seek(0u);                    // Reset file position...
    const auto blob = fileHandle.readAll(); // and read the whole file into a temporary blob
    for (auto offset = offsets.cbegin(); offset != offsets.end() - 1; offset++)
    {
        subFiles.emplace_back(filePath + QString::number(std::distance(offsets.cbegin(), offset)),
                              blob.mid(*(offset), *(offset + 1) - *offset));
    }
}

void KFMTFile::writeMIX(QFile& fileHandle)
{
    QDataStream outStream(&fileHandle);
    outStream.setByteOrder(QDataStream::LittleEndian);

    if (containerType == ContainerType::MIX_MIMCollection) outStream << mixMimSignature;

    for (const auto& file : subFiles)
    {
        if (containerType == ContainerType::MIX_HasSizes)
            outStream << static_cast<uint32_t>(file.rawData.size());
        outStream.writeRawData(file.rawData.data(), file.rawData.size());
    }
}

void KFMTFile::writeT(QFile& fileHandle)
{
    for (auto& file : subFiles) file.recalculateChecksum();

    // Create data blob
    QByteArray dataBlob;

    std::vector<uint16_t> newTrueOffsets;

    for (const auto& file : subFiles)
    {
        QByteArray alignedFile;
        auto alignedSize = static_cast<uint16_t>(file.rawData.size() / 2048u);
        if (file.rawData.size() % 2048u != 0) alignedSize += 1;

        alignedFile.resize(alignedSize * 2048u);
        alignedFile.fill(0);
        std::memcpy(alignedFile.data(), file.rawData.data(), file.rawData.size());

        newTrueOffsets.push_back((dataBlob.size() + 2048u) / 2048u);
        dataBlob.append(file.rawData);
    }

    // Add EOF to the offset vector
    newTrueOffsets.push_back((dataBlob.size() + 2048u) / 2048u);

    // Create stream for writing to the file
    QDataStream outStream(&fileHandle);
    outStream.setByteOrder(QDataStream::LittleEndian);

    // Write number of (fake) files
    outStream << static_cast<uint16_t>(tFileMap.size() - 1);

    // Write pointers
    for (size_t fileNum = 0; fileNum < tFileMap.size(); fileNum++)
        outStream << newTrueOffsets.at(tFileMap.find(fileNum)->second);

    // Pad out pointer table to 2048 bytes.
    // FIXME: I think this is pretty slow, but I can't think of a way around it right now.
    while (outStream.device()->pos() < 2048) outStream << static_cast<uint8_t>(0);

    outStream.writeRawData(dataBlob.data(), dataBlob.size());
}
