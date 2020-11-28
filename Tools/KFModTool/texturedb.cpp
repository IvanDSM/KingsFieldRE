#include "kfmterror.h"
#include "texturedb.h"

#include <memory>

TextureDB::TextureDB(TFile & tFile, unsigned int index)
{
    auto file = tFile.getFile(index);
    
    if (TFile::isTIM(file))
        loadTIM(file);
    else if (TFile::isRTIM(file))
        loadRTIM(file);
}

QPoint TextureDB::getFramebufferCoordinate(size_t textureIndex)
{
    if (textureIndex < textures.size())
        return textures[textureIndex].framebufferCoordinate;
    
    return {-999, -999};
}

QImage & TextureDB::getTexture(size_t textureIndex)
{
    try
    {
        return textures[textureIndex].image;
    }
    catch (const std::out_of_range &exception)
    {
        KFMTError::outOfRange(textureIndex, "texture", exception.what());
    }
}

void TextureDB::loadRTIM(const QByteArray &file)
{
    QDataStream rtimStream(file);
    rtimStream.setByteOrder(QDataStream::LittleEndian);
    
    uint16_t rtimID;
    uint16_t rtimUnknown;
    uint16_t clutEntryAmount;
    uint16_t clutAmount;
    
    uint16_t rtimIDDupe;
    uint16_t rtimUnknownDupe;
    uint16_t clutEntryAmountDupe;
    uint16_t clutAmountDupe;
    
    
    while (!rtimStream.atEnd())
    {
        textures.emplace_back();
        
        rtimStream >> rtimID;
        if (rtimID != 448 && rtimID != 512 && rtimID != 576)
        {
            KFMTError::error("Texture: RTIM with invalid ID " + QString::number(rtimID));
            return;
        }
        
        rtimStream >> rtimUnknown;
        rtimStream >> clutEntryAmount;
        if (clutEntryAmount == 16)
            textures.back().pMode = PixelMode::CLUT4Bit;
        else if(clutEntryAmount == 256)
            textures.back().pMode = PixelMode::CLUT8Bit;
        
        rtimStream >> clutAmount;
        if (clutAmount != 1)
        {
            KFMTError::error("Texture: Unsupported RTIM CLUT amount " + QString::number(clutAmount));
            return;
        }
        
        rtimStream >> rtimIDDupe;
        rtimStream >> rtimUnknownDupe;
        rtimStream >> clutEntryAmountDupe;
        rtimStream >> clutAmountDupe;
        
        if (rtimID != rtimIDDupe || rtimUnknown != rtimUnknownDupe ||
            clutEntryAmount != clutEntryAmountDupe || clutAmount != clutAmountDupe)
        {
            KFMTError::error("Texture: RTIM header dupes don't match.");
        }
        
        readCLUT(rtimStream, textures.back(), true);
        
        readPixelData(rtimStream, textures.back(), true);
    }
}

void TextureDB::loadTIM(const QByteArray &file)
{
    QDataStream timStream(file);
    timStream.setByteOrder(QDataStream::LittleEndian);
    
    uint32_t id;
    uint32_t flag;
    
    timStream >> id;
    if (id != 0x10)
    {
        KFMTError::error("Texture: TIM ID is not 0x10. Bailing out.");
        return;
    }
    
    textures.emplace_back();
    
    timStream >> flag;
    textures.back().pMode = static_cast<PixelMode>(flag & 0b111);
    textures.back().cf = static_cast<bool>((flag >> 3) & 1);
    
    if (textures.back().cf)
    {
        readCLUT(timStream, textures.back());
    }
    
    readPixelData(timStream, textures.back());
}

void TextureDB::readCLUT(QDataStream & stream, Texture & targetTex, bool isRtim)
{
    uint32_t clutSize;
    uint16_t dx, dy;
    uint16_t w, h;
    
    if (!isRtim)
    {
        stream >> clutSize;
        stream >> dx;
        stream >> dy;
        stream >> w;
        stream >> h;
    }
    
    targetTex.clut = std::make_unique<CLUT>(clutSize, dx, dy, w, h, targetTex.pMode);
    
    size_t clutAmount = 0;
    
    if (targetTex.pMode == PixelMode::CLUT4Bit)
        clutAmount = 16;
    else if (targetTex.pMode == PixelMode::CLUT8Bit)
        clutAmount = 255;
    
    for (size_t curEntry = 0; curEntry < clutAmount; curEntry++)
    {
        uint16_t clutEntry;
        stream >> clutEntry;
        targetTex.clut->addColor(clutEntry);
    }
}

void TextureDB::readPixelData(QDataStream & stream, Texture & targetTex, bool isRtim)
{
    uint32_t pixelDataSize;
    uint16_t dx, dy;
    uint16_t w, h;
    
    if (!isRtim)
        stream >> pixelDataSize;
    stream >> dx;
    stream >> dy;
    stream >> w;
    stream >> h;
    
    // If this is an RTIM, skip the DX/DY and W/X dupes
    if (isRtim)
        stream.skipRawData(8);
    
    // Adjust width properly
    if (targetTex.pMode == PixelMode::CLUT4Bit)
        w = w * 4;
    else if (targetTex.pMode == PixelMode::CLUT8Bit)
        w = w * 2;
    
    // Set framebuffer coordinate
    targetTex.framebufferCoordinate.setX(dx);
    targetTex.framebufferCoordinate.setY(dy);
    
    // Set texture size
    targetTex.image = QImage(w, h, QImage::Format_RGB555);
    
    int curPixel = 0;
    
    while (curPixel < w * h)
    {
        uint16_t block0;
        stream >> block0;
        
        switch (targetTex.pMode)
        {
            case (PixelMode::CLUT4Bit):
            {
                uint8_t pixel0 = block0 & 0b1111;
                uint8_t pixel1 = (block0 >> 4) & 0b1111;
                uint8_t pixel2 = (block0 >> 8) & 0b1111;
                uint8_t pixel3 = (block0 >> 12) & 0b1111;
                targetTex.image.setPixelColor(curPixel % w, curPixel / w, 
                                              targetTex.clut->getColor(pixel0));
                curPixel++;
                targetTex.image.setPixelColor(curPixel % w, curPixel / w, 
                                              targetTex.clut->getColor(pixel1));
                curPixel++;
                targetTex.image.setPixelColor(curPixel % w, curPixel / w, 
                                              targetTex.clut->getColor(pixel2));
                curPixel++;
                targetTex.image.setPixelColor(curPixel % w, curPixel / w, 
                                              targetTex.clut->getColor(pixel3));
                curPixel++;
                break;
            }
            case (PixelMode::CLUT8Bit):
            {
                uint8_t pixel0 = block0 & 0xFF;
                uint8_t pixel1 = (block0 >> 8) & 0xFF;
                targetTex.image.setPixelColor(curPixel % w, curPixel / w, 
                                              targetTex.clut->getColor(pixel0));
                curPixel++;
                targetTex.image.setPixelColor(curPixel % w, curPixel / w, 
                                              targetTex.clut->getColor(pixel1));
                curPixel++;
                break;
            }
            default:
                KFMTError::error("Texture: Unimplemented pixel mode 0x" + 
                                 QString::number(static_cast<int>(targetTex.pMode), 16));
                return;
        }
    }
}
