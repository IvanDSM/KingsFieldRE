#ifndef MIXFILE_H
#define MIXFILE_H

#include <QDir>
#include <QFile>
#include <QString>

class MIXFile
{
public:
    explicit MIXFile(const QString &filename);
    QByteArray &getFile(size_t index);
    size_t size() const { return files.size(); }
    void writeTo(QFile & outFile) const;
    
private:
    void load(const QByteArray & file);
    
    void loadHasSizes(const QByteArray &mixFile);
    void loadNoSizes(const QByteArray& mixFile);

    bool loaded = false;
    enum class Type
    {
        HasSizes,     ///< KF1 MIX with file size before each file
        NoSizes,      ///< KF1 MIX with just TIMs/TMDs back-to-back
        MIMCollection ///< KF1 MIX for MIM files with 06 or 07 at the beginning
    } type;
    QString fileName;
    std::vector<QByteArray> files;
    uint32_t mimColSignature; ///< Signature to write in case type == Type::MIMCollection
};

#endif // MIXFILE_H
