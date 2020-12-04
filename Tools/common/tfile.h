#ifndef TFILE_H
#define TFILE_H

#include <QDataStream>
#include <QFile>
#include <QString>
#include <unordered_map>

class TFile
{
public:
    explicit TFile(const QString &filename) : fileName(filename.mid(filename.lastIndexOf(QRegExp("[\\/]")) + 1))
    {
        QFile fileHandle(filename);
        if (fileHandle.open(QIODevice::ReadOnly))
        {
            file = fileHandle.readAll();
            load();
        }
        else
            nFiles = 0;
        fileHandle.close();
    }

    explicit TFile(const QString &filename, const QByteArray &fileContent) : file(fileContent),
        fileName(filename.mid(filename.lastIndexOf(QRegExp("[\\/]")) + 1))
    {
        load();
    }

    /*!
     * \brief Extracts all the T file's contents to the current working directory.
     * \return Whether the extraction was successful.
     */
    bool extractFiles();

    /*!
     * \brief Returns the T file's filename, without the path or extension.
     * \return T file name without path or extension.
     */
    QString getBaseFilename() const;

    /*!
     * \brief Returns the T file's filename, without the path.
     * \return T file name without path.
     */
    QString getFilename() const;

    /*!
     * \brief Returns a QByteArray that contains the desired file.
     * \param trueFileNumber True file number for the desired file.
     * \return File as a QByteArray, empty if given an invalid file number.
     */
    QByteArray getFile(unsigned int trueFileNumber) const;
    
    /*!
     * \brief Returns the file type for a given file number.
     * \param trueFileNumber True file number for the desired file.
     * \return File type as a QString, empty if given an invalid file number.
     */
    QString getFiletype(unsigned int trueFileNumber) const;

    /*!
     * \brief Retrieves the vector of de-duplicated file offsets before multiplying.
     * \return Vector of de-duplicated file offsets with no multiplication.
     */
    std::vector<unsigned int> getFileOffsets() const;

    /*!
     * \brief Returns the T file's MD5 hash.
     * \return MD5 hash for the T file.
     */
    QByteArray &getHash() const;
    
    /*!
     * \brief Retrieves the number of files reported by the T file, including duplicates.
     * \return Number of files reported by the T file, including duplicates.
     */
    unsigned int getNumFiles() const;
    
    QString getPrettyName(size_t index) const;

    /*!
     * \brief Retrieves the vector of de-duplicated and multiplied file offsets.
     * \return Vector of de-duplicated and multiplied file offsets.
     */
    std::vector<unsigned int> getTrueFileOffsets() const;

    /*!
     * \brief Retrieves the number of actual files in the T file, with duplicates removed.
     * \return True number of files in the T file, with no duplicates.
     */
    unsigned int getTrueNumFiles() const;

    QByteArray getTFile() const
    {
        return file;
    }
    
    static bool isGameDB(const QByteArray &file);
    
    /*!
     * \brief Checks whether a file is the first file of a map.
     * This is done in a very naive manner that checks if the first 4 bytes of the file are equal to
     * {0x00, 0xFA, 0x00, 0x00}. FIXME: We can probably do a better heuristic for this.
     * \param file File to check.
     * \return Whether the file is the first file of a map.
     */
    static bool isMAP1(const QByteArray &file);
    
    /*!
     * \brief Checks whether a file is the second file of a map.
     * This is done in a very naive manner that checks if the first 4 bytes of the file are equal to
     * {0xC0 0x32 0x00 0x00}. FIXME: We can probably do a better heuristic for this.
     * \param file File to check.
     * \return Whether the file is the second file of a map.
     */
    static bool isMAP2(const QByteArray &file);
    
    /*!
     * \brief Checks whether a file is the third file of a map.
     * This is done by assuming that we have a table of 32 pointers at the start of the file,
     * as a third map file would. We then check if the most significant byte in all of them is 0x80.
     * If so, this is a third map file.
     * \param file File to check
     * \return Whether the file is the third file of a map.
     */
    static bool isMAP3(const QByteArray &file);
    
    /*!
     * \brief Checks whether a file is a MO file.
     * This is done by checking if the unsigned int at offset 0x08 in the file points to a section 
     * in the file with the TMD ID (0x41).
     * \param file File to check.
     * \return Whether the file is a MO file.
     */
    static bool isMO(const QByteArray &file);
    
    /*!
     * \brief Checks whether a file is an RTMD file.
     * This is done by checking if the file starts with 4 zero bytes and is the followed by either 
     * 0x12 (4 byte long) or 0x10 (4 byte long).
     * \param file File to check.
     * \return Whether the file is an RTMD file.
     */
    static bool isRTMD(const QByteArray &file);
    
    /*!
     * \brief Checks whether a file is an RTIM file (should only be run after checking for TIM).
     * This is done by checking if the file's first 8 bytes are equal to the next 8 bytes.
     * \param file File to check.
     * \return Whether the file is an RTIM file.
     */
    static bool isRTIM(const QByteArray &file);
    
    /*!
     * \brief Checks whether a file is a SEQ file.
     * This is done by checking if the file's first 4 bytes are equal to the 
     * little-endian string "SEQp".
     * \param file File to check.
     * \return Whether the file is a SEQ file.
     */
    static bool isSEQ(const QByteArray &file);
    
    /*!
     * \brief Checks whether a file is an TIM file.
     * This is done by checking if the file's first 4 bytes as an unsigned int is 
     * equal to the TMD ID (0x10).
     * \param file File to check.
     * \return Whether the file is an TIM file.
     */
    static bool isTIM(const QByteArray &file);
    
    /*!
     * \brief Checks whether a file is a TMD file.
     * This is done by checking if the file's first 4 bytes as an unsigned int is 
     * equal to the TMD ID (0x41).
     * \param file File to check.
     * \return Whether the file is a TMD file.
     */
    static bool isTMD(const QByteArray &file);
    
    /*!
     * \brief Checks whether a file is a VB file.
     * This is done by checking if the file's first 16 bytes are zero.
     * FIXME: This is some really shitty detection.
     * \param file File to check.
     * \return Whether the file is a VB file.
     */
    static bool isVB(const QByteArray &file);
    
    /*!
     * \brief Checks whether a file is a VH file.
     * This is done by checking if the file's first 4 bytes are equal to the 
     * little-endian string "VABp".
     * \param file File to check.
     * \return Whether the file is a VH file.
     */
    static bool isVH(const QByteArray &file);

    /*!
     * \brief Writes a file to the T file. Currently super unsafe! Does not verify the checksum!
     * \param newFile The file to be written.
     * \param index The TRUE index of the file.
     */
    void writeFile(const QByteArray &newFile, int index);

    /*!
     * \brief Writes the T file's file map to a csv file.
     */
    void writeFileMap();

private:
    
    /*!
     * \brief Private function for actually loading from the 'file' member attribute.
     */
    void load();

    bool loaded = true; ///< Whether the T file was successfully loaded.
    QByteArray file; ///< Byte array for the T file
    QByteArray hash; ///< MD5 hash of the file for getting pretty names.
    QDataStream stream; ///< Data stream for reading the file
    QString fileName; ///< Name of the T file
    unsigned short nFiles; ///< Number of files in the T file
    std::vector<unsigned int> fileOffsets; ///< Vector with file offsets.
    std::map<unsigned int, unsigned int> fileMap; ///< Map that maps the T file's file indexes to the actual files.
    std::unordered_map<QString, QString> prettyMap; ///< Map with the pretty names for the file. Obtained from PrettyNamer.
};

#endif // TFILE_H
