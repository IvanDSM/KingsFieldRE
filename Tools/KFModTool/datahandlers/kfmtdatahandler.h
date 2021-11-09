#ifndef KFMTDATAHANDLER_H
#define KFMTDATAHANDLER_H

#include "core/kfmtfile.h"

class KFMTDataHandler
{
public:
    explicit KFMTDataHandler(KFMTFile& file_) : file(file_) {}
    virtual ~KFMTDataHandler(){};
    KFMTFile& getFile() { return file; }
    virtual void saveChanges() = 0;

protected:
    KFMTFile& file;
};

#endif // KFMTDATAHANDLER_H
