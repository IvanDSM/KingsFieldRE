#include "kfmterror.h"
#include "texturedb.h"
#include "libimagequant/libimagequant.h"
#include <memory>

TextureDB::TextureDB(TFile &tFile_, unsigned int index) : tFile(tFile_), fileIndex(index)
{
    auto file = tFile_.getFile(index);
    fileId = tFile_.getFilename() + QString::number(index);
    
    if (TFile::isTIM(file))
        loadTIM(file);
    else if (TFile::isRTIM(file))
    {
        isRtim = true;
        loadRTIM(file);
    }
}

QPoint TextureDB::getFramebufferCoordinate(size_t textureIndex)
{
    if (textureIndex < textures.size())
        return textures[textureIndex].framebufferCoordinate;
    
    return {-999, -999};
}

TextureDB::Texture & TextureDB::getTexture(size_t textureIndex)
{
    try
    {
        return textures[textureIndex];
    }
    catch (const std::out_of_range &exception)
    {
        KFMTError::outOfRange(textureIndex, "texture", exception.what());
    }
}

void TextureDB::replaceTexture(QImage & newTexture, size_t textureIndex, bool smooth)
{
    if (textureIndex >= textures.size())
    {
        KFMTError::error("Texture: Tried to replace a non-existent texture.");
        return;
    }
    
    auto &texture = textures[textureIndex];
    
    
    
    auto newTex = newTexture.scaled(texture.pxWidth, texture.pxHeight, Qt::IgnoreAspectRatio,
                                    static_cast<Qt::TransformationMode>(smooth))
                            .convertToFormat(QImage::Format_RGBA8888, Qt::DiffuseDither);
    
    if (texture.pMode == PixelMode::CLUT4Bit || texture.pMode == PixelMode::CLUT8Bit)
    {
        liq_attr *iQAttr = liq_attr_create();
        liq_result *iQRes = nullptr;
        
        liq_image *iQImg = liq_image_create_rgba(iQAttr, newTex.bits(),
                                                 newTex.width(), newTex.height(), 0.0);
        
        if (texture.pMode == PixelMode::CLUT4Bit)
            liq_set_max_colors(iQAttr, 16);
        
        
        if (liq_set_speed(iQAttr, 1) != LIQ_OK)
        {
            KFMTError::error("Texture: Failed to set libimagequant speed to 1, will use default.");
        }
        
        if (liq_image_quantize(iQImg, iQAttr, &iQRes) != LIQ_OK)
        {
            KFMTError::error("Texture: libimagequant failed to quantize the new texture.");
            liq_attr_destroy(iQAttr);
            return;
        }
        
        if (liq_set_dithering_level(iQRes, 1.0) != LIQ_OK)
        {
            KFMTError::error("Texture: Failed to set libimagequant dither level to 1.0, will use default.");
        }
        
        const liq_palette *iQPal = liq_get_palette(iQRes);
        
        QVector<QRgb> clut;
        
        for (size_t entryIndex = 0; entryIndex < iQPal->count; entryIndex++)
        {
            auto entry = iQPal->entries[entryIndex];
            clut.push_back(QColor(entry.r, entry.g, entry.b, entry.a).rgba());
        }
        
        texture.image.setColorTable(clut);
        
        liq_write_remapped_image(iQRes, iQImg, texture.image.bits(),
                                 newTex.width() * newTex.height());
        
        liq_result_destroy(iQRes);
        liq_image_destroy(iQImg);
        liq_attr_destroy(iQAttr);
    }
    else
    {
        KFMTError::error("Texture: Unhandled pixel mode for replacing textures.");
        return;
    }
}

void TextureDB::writeChanges()
{
    QByteArray outFile;
    QDataStream outStream(&outFile, QIODevice::WriteOnly);
    outStream.setByteOrder(QDataStream::LittleEndian);
    
    if (!isRtim) // TIM File
    {
    }
    else // RTIM File
    {
        for (auto &texture : textures)
        {
            uint16_t clutEntryAmount = 16;
            if (texture.pMode == PixelMode::CLUT8Bit)
                clutEntryAmount = 256;
            
            // Write CLUT header
            outStream << texture.clutVramX;
            outStream << texture.clutVramY;
            outStream << clutEntryAmount;
            outStream << static_cast<uint16_t>(1);
            
            // Write CLUT header dupe
            outStream << texture.clutVramX;
            outStream << texture.clutVramY;
            outStream << clutEntryAmount;
            outStream << static_cast<uint16_t>(1);
            
            // Write CLUT
            for (auto entry : texture.getCLUTEntries())
                outStream << entry;
            
            // Adjust width before writing
            uint16_t fixedPixelWidth = texture.pxWidth;
            if (texture.pMode == PixelMode::CLUT4Bit)
                fixedPixelWidth /= 4;
            else if (texture.pMode == PixelMode::CLUT8Bit)
                fixedPixelWidth /= 2;
            
            // Write pixel data header
            outStream << texture.pxVramX;
            outStream << texture.pxVramY;
            outStream << fixedPixelWidth;
            outStream << texture.pxHeight;
            
            // Write pixel data header dupe
            outStream << texture.pxVramX;
            outStream << texture.pxVramY;
            outStream << fixedPixelWidth;
            outStream << texture.pxHeight;
            
            auto imageByteData = texture.image.bits();
            auto imagePixelSize = texture.image.width() * texture.image.height();
            auto imageCurPixel = 0;
            
            while (imageCurPixel < imagePixelSize)
            {
                switch (texture.pMode)
                {
                case PixelMode::CLUT4Bit:
                {
                    uint8_t px0 = imageByteData[imageCurPixel] & 15;
                    uint8_t px1 = imageByteData[imageCurPixel + 1] & 15;
                    uint8_t px2 = imageByteData[imageCurPixel + 2] & 15;
                    uint8_t px3 = imageByteData[imageCurPixel + 3] & 15;
                    
                    uint16_t packet = px0 | (px1 << 4) | (px2 << 8) | (px3 << 12);
                    
                    outStream << packet;
                    
                    imageCurPixel += 4;
                }
                break;
                case PixelMode::CLUT8Bit:
                {
                    outStream << imageByteData[imageCurPixel];
                    outStream << imageByteData[imageCurPixel + 1];
                    imageCurPixel += 2;
                }
                break;
                default:
                    KFMTError::error("Texture: Unhandled pixel mode!");
                    return;
                    break;
                }
            }
        }
    }
    
    tFile.writeFile(outFile, fileIndex);
}

void TextureDB::loadRTIM(const QByteArray &file)
{
    QDataStream rtimStream(file);
    rtimStream.setByteOrder(QDataStream::LittleEndian);
    
    uint16_t clutEntryAmount;
    uint16_t clutAmount;
    
    uint16_t clutVramXDupe;
    uint16_t clutVramYDupe;
    uint16_t clutEntryAmountDupe;
    uint16_t clutAmountDupe;
    
    
    while (!rtimStream.atEnd())
    {        
        textures.emplace_back();
        
        uint16_t &clutVramX = textures.back().clutVramX;
        uint16_t &clutVramY = textures.back().clutVramY;
        
        rtimStream >> clutVramX;
        rtimStream >> clutVramY;
        
        rtimStream >> clutEntryAmount;
        if (clutEntryAmount == 16)
            textures.back().pMode = PixelMode::CLUT4Bit;
        else if (clutEntryAmount == 256)
            textures.back().pMode = PixelMode::CLUT8Bit;
        
        rtimStream >> clutAmount;
        
        rtimStream >> clutVramXDupe;
        rtimStream >> clutVramYDupe;
        rtimStream >> clutEntryAmountDupe;
        rtimStream >> clutAmountDupe;
        
        if (clutVramX != clutVramXDupe || clutVramY != clutVramYDupe ||
            clutEntryAmount != clutEntryAmountDupe || clutAmount != clutAmountDupe ||
            (clutVramX == 0 && clutVramY == 0 && clutEntryAmount == 0 && clutAmount == 0) ||
            (clutVramX == 0xFFFF && clutVramY == 0xFFFF && clutEntryAmount == 0xFFFF && clutAmount == 0xFFFF))
        {
            textures.pop_back();
            KFMTError::log("Texture: Invalid RTIM header.");
            KFMTError::log(QString("%1 @ %2").arg(fileId).arg(rtimStream.device()->pos() - 16, 0, 16));
            KFMTError::log(QString::asprintf("vramx = %u, vramy = %u clutentries = %u clutcnt = %u",
                                             clutVramX, clutVramY, clutEntryAmount, clutAmount));
            return;
        }
//        else if (clutVramX == 0xFFFF && clutVramY == 0xFFFF && clutEntryAmount == 0xFFFF && clutAmount == 0xFFFF)
//        {
//            // FIXME: VERY JANKY LOADING THING FOR THE WEIRD PICTURE
//            rtimStream.skipRawData(48);
//            int curPixel = 0;
//            textures.back().image = QImage(96, 8, QImage::Format_RGB888);
            
//            while (!rtimStream.atEnd())
//            {
//                uint8_t pixel;
//                rtimStream >> pixel;
                
//                textures.back().image.setPixel(curPixel % 96, curPixel / 96, qRgb(pixel, pixel, pixel));
//                curPixel++;
//            }
            
//            break;
//        }
        
        if (clutAmount != 1)
        {
            KFMTError::error("Texture: Unsupported RTIM CLUT amount " + QString::number(clutAmount));
            return;
        }
        
        readCLUT(rtimStream, textures.back());
        
        readPixelData(rtimStream, textures.back());
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

void TextureDB::readCLUT(QDataStream & stream, Texture & targetTex)
{
    if (!isRtim)
    {
        stream >> targetTex.clutSize;
        stream >> targetTex.clutVramX;
        stream >> targetTex.clutVramY;
        stream >> targetTex.clutWidth;
        stream >> targetTex.clutHeight;
    }
    
    size_t clutAmount = 0;
    
    if (targetTex.pMode == PixelMode::CLUT4Bit)
        clutAmount = 16;
    else if (targetTex.pMode == PixelMode::CLUT8Bit)
        clutAmount = 255;
    else
    {
        KFMTError::error("Texture: Tried to read CLUT when pixel mode isn't a CLUT mode.");
        return;
    }
    
    for (size_t curEntry = 0; curEntry < clutAmount; curEntry++)
    {
        uint16_t clutEntry;
        stream >> clutEntry;
        
        const uint8_t r = (clutEntry & 31) * 8;
        const uint8_t g = ((clutEntry >> 5) & 31) * 8;
        const uint8_t b = ((clutEntry >> 10) & 31) * 8;
        uint8_t a = clutEntry >> 15;
        if (a == 0 && r == 0 && g == 0 && b == 0)
            a = 0;
        else if (a == 0 && (r != 0 || g != 0 || b != 0))
            a = 255;
        else if (a == 1 && (r != 0 || g != 0 || b != 0))
            a = 127;
        else if (a == 1 && r == 0 && g == 0 && b == 0)
            a = 255;
        
        unsigned int color = b | (g << 8) | (r << 16) | (a << 24);
        
        targetTex.clutColorTable.push_back(color);
    }
    
    targetTex.image.setColorTable(targetTex.clutColorTable);
}

void TextureDB::readPixelData(QDataStream & stream, Texture & targetTex)
{
    if (!isRtim)
        stream >> targetTex.pxDataSize;
    stream >> targetTex.pxVramX;
    stream >> targetTex.pxVramY;
    stream >> targetTex.pxWidth;
    stream >> targetTex.pxHeight;
    
    // If this is an RTIM, skip the DX/DY and W/X dupes
    if (isRtim)
        stream.skipRawData(8);
    
    // Adjust width properly
    if (targetTex.pMode == PixelMode::CLUT4Bit)
        targetTex.pxWidth *= 4;
    else if (targetTex.pMode == PixelMode::CLUT8Bit)
        targetTex.pxWidth *= 2;
    
    // Set framebuffer coordinate
    targetTex.framebufferCoordinate.setX(targetTex.pxVramX);
    targetTex.framebufferCoordinate.setY(targetTex.pxVramY);
    
    // Set texture size
    targetTex.image = QImage(targetTex.pxWidth, targetTex.pxHeight, QImage::Format_Indexed8);
    targetTex.image.setColorTable(targetTex.clutColorTable);
    
    int curPixel = 0;
    
    while (curPixel < targetTex.pxWidth * targetTex.pxHeight)
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
                targetTex.image.setPixel(curPixel % targetTex.pxWidth, curPixel / targetTex.pxWidth,
                                         pixel0);
                curPixel++;
                targetTex.image.setPixel(curPixel % targetTex.pxWidth, curPixel / targetTex.pxWidth,
                                         pixel1);
                curPixel++;
                targetTex.image.setPixel(curPixel % targetTex.pxWidth, curPixel / targetTex.pxWidth,
                                         pixel2);
                curPixel++;
                targetTex.image.setPixel(curPixel % targetTex.pxWidth, curPixel / targetTex.pxWidth,
                                         pixel3);
                curPixel++;
                break;
            }
            case (PixelMode::CLUT8Bit):
            {
                uint8_t pixel0 = block0 & 0xFF;
                uint8_t pixel1 = (block0 >> 8) & 0xFF;
                targetTex.image.setPixel(curPixel % targetTex.pxWidth, curPixel / targetTex.pxWidth,
                                         pixel0);
                curPixel++;
                targetTex.image.setPixel(curPixel % targetTex.pxWidth, curPixel / targetTex.pxWidth,
                                         pixel1);
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

std::vector<uint16_t> TextureDB::Texture::getCLUTEntries()
{
    std::vector<uint16_t> result;
    if (pMode == PixelMode::CLUT4Bit)
        result.reserve(16);
    else if (pMode == PixelMode::CLUT8Bit)
        result.reserve(256);
    else
    {
        KFMTError::error("Texture: Tried to get CLUT entries when pixel mode isn't a CLUT mode.");
        return {};
    }
    
    for (auto &color : image.colorTable())
    {
        uint8_t r = (color >> 16) & 0xFF;
        uint8_t g = (color >> 8) & 0xFF;
        uint8_t b = color & 0xFF;
        uint8_t a = (color >> 24) & 0xFF;
        if (a == 0 && r == 0 && g == 0 && b == 0)
            a = 0;
        else if (a == 255 && (r != 0 || g != 0 || b != 0))
            a = 0;
        else if (a == 127)
            a = 1;
        else if (a == 255 && r == 0 && g == 0 && b == 0)
            a = 1;
        
        r /= 8;
        g /= 8;
        b /= 8;
        
        result.push_back(r | ((g & 31) << 5) | ((b & 31) << 10) | ((a & 1) << 15)) ;
    }
    
    return result;
}
