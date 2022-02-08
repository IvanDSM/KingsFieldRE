#ifndef KFMTFILE_H
#define KFMTFILE_H

#include <memory>
#include <QDir>

class KFMTFile
{
public:
    enum class FileType
    {
        MIX,
        Raw,
        T
    };

    enum class DataType
    {
        Container,
        GameDB,
        GameEXE,
        MapTilemap,
        MapDB,
        MapScript,
        Model,
        SoundBankBody,
        SoundBankHeader,
        TextureDB,
        Unknown
    };

    /*!
     * \brief Standard KFMTFile Constructor
     * \param srcDir Path to the source directory for the game files.
     * \param path Path to this file in the source directory.
     * \param fileType Type of file (MIX, Raw or T).
     */
    KFMTFile(const QString& srcDir, const QString& path, FileType fileType);

    /*!
     * \brief Constructor for making subfiles.
     * \param srcPath Path to the container for this file (incl. source directory) + file number.
     * \param data Byte array with data for this file.
     */
    KFMTFile(const QString& srcPath_, const QByteArray& data);

    /*!
     * \brief Method to extract files from a container onto a directory.
     * \param outDir Directory which to extract files to.
     */
    void extractTo(const QDir& outDir);

    inline DataType getDataType() const { return dataType; }
    const QString& getFileExtension() const;
    inline FileType getFileType() const { return fileType; }
    inline KFMTFile* getSubFile(size_t index)
    {
        return index < subFiles.size() ? &subFiles[index] : nullptr;
    }
    void writeFile(const QDir& outDir);

    QString filePath;
    QByteArray rawData;

private:
    void detectDataType();
    /*!
     * \brief Calculates and writes the checksum to a file.
     * THIS SHOULD ONLY BE RUN FOR T FILE SUBFILES.
     */
    void recalculateChecksum();
    void loadMIX(QFile& fileHandle);
    void loadT(QFile& fileHandle);
    void writeMIX(QFile& fileHandle);
    void writeT(QFile& fileHandle);

    FileType fileType;
    DataType dataType;

    // Container specific stuff
    enum ContainerType
    {
        MIX_HasSizes,      ///< MIX with file size before each file
        MIX_NoSizes,       ///< MIX with just TIMs/TMDs back-to-back
        MIX_MIMCollection, ///< MIX for MIM files with 06 or 07 at the beginning
        T                  ///< KF2 T file
    } containerType;
    std::vector<KFMTFile> subFiles; ///< Vector of subfiles if this file is a container
    uint32_t mixMimSignature;       ///< Signature to write in case type == Type::MIMCollection
    /*!
     * \brief Maps a T file's original file numbers to the true file numbers.
     * This is necessary because T files usually have many file numbers that point to the same
     * actual file. These are duplicates that we ignore, but the game might depend on. Therefore,
     * when rebuilding a T file it is necessary to rebuild the file offset table with the same
     * "duplicate order" as the original.
     */
    std::map<uint32_t, uint32_t> tFileMap;

    // FileListModel needs access to the subFiles member.
    friend class FileListModel;
};

#endif // KFMTFILE_H
