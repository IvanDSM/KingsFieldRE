#ifndef TFILE_H
#define TFILE_H

#include <QDataStream>
#include <QDir>
#include <QFile>
#include <QString>
#include <unordered_map>

class TFile
{
public:
    explicit TFile(const QString &filename);

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
     * \brief Returns a QByteArray reference for the desired file.
     * \param index True file number for the desired file.
     * \return Read/write QByteArray reference for the file.
     */
    QByteArray &getFile(size_t index);
    
    /*!
     * \brief Returns the file type for a given file.
     * \param file File to find type.
     * \return File type as a QString, empty if given an invalid file number.
     */
    QString getFiletype(QByteArray & file) const;

    /*!
     * \brief Retrieves the number of files contained in the T file.
     * \return Number of files in the T file.
     */
    size_t getNumFiles() const;

    void writeTo(QFile &outFile) const;

private:
    
    /*!
     * \brief Private function for actually loading from the 'file' member attribute.
     * \param tFileBlob QByteArray containing the entirety of the T file.
     */
    void load(const QByteArray &tFileBlob);

    bool loaded = false; ///< Whether the T file was successfully loaded.
    QString fileName; ///< Name of the T file
    std::vector<QByteArray> files; ///< Vector with the files contained inside the T file.
    std::vector<unsigned int> fileOffsets; ///< Vector with file offsets.
    std::map<unsigned int, unsigned int>
        fileMap; ///< Map that maps the T file's file indexes to the actual files.
};

#endif // TFILE_H
