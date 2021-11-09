#ifndef TILESETICONS_H
#define TILESETICONS_H

#include "core/kfmterror.h"
#include "datahandlers/kfmtdatahandler.h"

class TilesetIcons : KFMTDataHandler
{
public:
    TilesetIcons(KFMTFile& file_);
    const QImage& getIcon(size_t index) const
    {
        if (index >= icons.size()) KFMTError::outOfRange(index, QStringLiteral("tileset icons"));

        return icons[index];
    }
    void saveChanges() override {}

private:
    std::vector<QImage> icons;
};

#endif // TILESETICONS_H
