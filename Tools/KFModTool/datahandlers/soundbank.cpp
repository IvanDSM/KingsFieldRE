#include "soundbank.h"
#include "utilities.h"
/*
SoundBank::SoundBank(KFMTFile& vh, KFMTFile& vb) : KFMTDataHandler(vh)
{
    if (vh.rawData.left(4) != QByteArray::fromHex(QByteArrayLiteral("56414270")))
        KFMTError::error("SoundBank: VH/VB constructor but VH doesn't start with VABp!");

    auto& header = Utilities::as<VABHeader>(vh.rawData);
    //auto* toneAttrs = &Utilities::as<ToneAttributes>(vh.rawData);
    auto& origOffsets = Utilities::as<uint16_t[256]>(vh.rawData,
                                                     sizeof(VABHeader) + 512 * header.programCount);

    uint16_t vagOffsets[256];
    for (auto v = std::begin(vagOffsets), o = std::begin(origOffsets);
         v != std::end(vagOffsets) && o != std::end(origOffsets);
         v++, o++)
    {
        *v = *o << 3;
        KFMTError::log("OFFSET: " + QString::number(*v));
    }
}
*/
