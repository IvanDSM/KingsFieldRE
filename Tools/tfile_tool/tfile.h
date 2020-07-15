#ifndef TFILE_H
#define TFILE_H

#include <QDataStream>
#include <QFile>
#include <QString>
#include <unordered_map>

class TFile
{
public:
    explicit TFile(const QString &filename);

    /*!
     * \brief Extracts all the T file's contents to the current working directory.
     * \return Whether the extraction was successful.
     */
    bool extractFiles();

    /*!
     * \brief Returns the T file's filename, without the path or extension.
     * \return T file name without path or extension.
     */
    QString getBaseFilename();

    /*!
     * \brief Returns the T file's filename, without the path.
     * \return T file name without path.
     */
    QString getFilename();

    /*!
     * \brief Returns a QByteArray that contains the desired file.
     * \param trueFileNumber True file number for the desired file.
     * \return File as a QByteArray, empty if given an invalid file number.
     */
    QByteArray getFile(unsigned int trueFileNumber) const;

    /*!
     * \brief Retrieves the vector of de-duplicated file offsets before multiplying.
     * \return Vector of de-duplicated file offsets with no multiplication.
     */
    std::vector<unsigned int> getFileOffsets();

    /*!
     * \brief Returns the T file's MD5 hash.
     * \return MD5 hash for the T file.
     */
    QByteArray &getHash();

    /*!
     * \brief Retrieves the vector of de-duplicated and multiplied file offsets.
     * \return Vector of de-duplicated and multiplied file offsets.
     */
    std::vector<unsigned int> getTrueFileOffsets();

    /*!
     * \brief Retrieves the number of files reported by the T file, including duplicates.
     * \return Number of files reported by the T file, including duplicates.
     */
    unsigned int getNumFiles();

    /*!
     * \brief Retrieves the number of actual files in the T file, with duplicates removed.
     * \return True number of files in the T file, with no duplicates.
     */
    unsigned int getTrueNumFiles() const;

    QByteArray getTFile() const
    {
        return file;
    }

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
