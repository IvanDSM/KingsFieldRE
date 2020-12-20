#ifndef MIXFILE_H
#define MIXFILE_H

#include <QDir>
#include <QFile>
#include <QString>

class MIXFile
{
public:
    explicit MIXFile(const QString &filename);
    void write(const QDir & outDir);
    
private:
    void load(QFile &fileHandle);
    
    void loadHasSizes(QDataStream &stream);
    void loadNoSizes(QDataStream &stream);
    
    bool loaded = false;
    bool hasSizes = true;
    QString fileName;
    std::vector<QByteArray> files;
};

#endif // MIXFILE_H
