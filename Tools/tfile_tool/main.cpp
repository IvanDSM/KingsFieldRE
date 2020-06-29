#include <QCoreApplication>
#include <QDebug>
#include "tfile.h"

int main(int argc, char *argv[])
{
    bool extract = false;
    int startIndex = 1;

    qInfo() << "tfile_tool - IvanDSM 2020";
    qInfo() << "Usage:";
    qInfo() << "tfile_tool TFILE.T            Shows info about TFILE.T.";
    qInfo() << "tfile_tool extract TFILE.T    Shows info about TFILE.T and extracts contents to $(cwd)/TFILE/.";

    if (argc < 2)
    {
        qInfo() << "No T file provided. Exiting.";
        return 1;
    }

    if (QString(argv[1]).compare("extract") == 0)
    {
        if (argc == 2)
        {
            qInfo() << "No T file provided. Exiting.";
            return 1;
        }
        extract = true;
        startIndex++;
    }

    for (int i = startIndex; i < argc; i++)
    {
        TFile curTFile(argv[i]);
        qInfo() << curTFile.getFilename();
        qInfo() << "Number of files according to T file:" << curTFile.getNumFiles();
        qInfo() << "Actual number of files: " << curTFile.getTrueNumFiles();
        qInfo() << "File offsets (original): " << curTFile.getFileOffsets();
        qInfo() << "File offsets (calculated): " << curTFile.getTrueFileOffsets();
        if (extract)
        {
            curTFile.extractFiles();
            curTFile.writeFileMap();
        }
    }
}
