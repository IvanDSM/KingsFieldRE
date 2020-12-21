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
    void write(const QDir & outDir);
    
private:
    void load(const QByteArray & file);
    
    void loadHasSizes(const QByteArray &mixFile);
    void loadNoSizes(const QByteArray &mixFile);
    
    bool loaded = false;
    bool hasSizes = true;
    QString fileName;
    std::vector<QByteArray> files;
};

#endif // MIXFILE_H
