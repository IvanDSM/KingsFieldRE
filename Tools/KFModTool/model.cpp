#include "model.h"

Model::Model(TFile & tFile, unsigned int fileIndex)
{
    auto file = tFile.getFile(fileIndex);
    if (!file.isEmpty())
    {
        if (TFile::isMO(file)) // MO File
            loadMO(file);
        else if (TFile::isRTMD(file)) // RTMD File
            loadRTMD(file);
        else if (TFile::isTMD(file)) // TMD File
            loadTMD(file);
        else
            KFMTError::error("Model: Tried to build a model from a file that's not MO, RTMD or TMD.");
    }
}

void Model::loadMO(const QByteArray & file)
{
    
}

void Model::loadRTMD(const QByteArray & file)
{
    
}

void Model::loadTMD(const QByteArray & file)
{
    
}
