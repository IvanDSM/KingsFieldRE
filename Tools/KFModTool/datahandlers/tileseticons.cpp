#include "tileseticons.h"
#include "datahandlers/model.h"

TilesetIcons::TilesetIcons(KFMTFile& file_) : KFMTDataHandler(file_)
{
    if (file_.getDataType() != KFMTFile::DataType::Model)
        KFMTError::fatalError(QStringLiteral("TilesetIcons was given a non-model file!"));

    const auto model = Model(file_);

    for (const auto& tile : model.baseObjects) {}
}
