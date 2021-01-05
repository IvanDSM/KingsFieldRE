#include "kfmterror.h"
#include "libimagequant/libimagequant.h"
#include "texturedb.h"
#include "utilities.h"
#include <memory>

TextureDB::TextureDB(QByteArray &textureDBFile) : file(textureDBFile)
{
    if (Utilities::fileIsTIM(file))
    {
        type = TexDBType::TIM;
        loadTIM();
    }
    else if (Utilities::fileIsRTIM(file))
    {
        type = TexDBType::RTIM;
        loadRTIM();
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
        KFMTError::error("TextureDB: Tried to replace a non-existent texture.");
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
            KFMTError::error("TextureDB: Failed to set libimagequant speed to 1, will use default.");
        }
        
        if (liq_image_quantize(iQImg, iQAttr, &iQRes) != LIQ_OK)
        {
            KFMTError::error("TextureDB: libimagequant failed to quantize the new texture.");
            liq_attr_destroy(iQAttr);
            return;
        }
        
        if (liq_set_dithering_level(iQRes, 1.0) != LIQ_OK)
        {
            KFMTError::error("TextureDB: Failed to set libimagequant dither level to 1.0, will use default.");
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
        KFMTError::error("TextureDB: Unhandled pixel mode for replacing textures.");
        return;
    }
}

void TextureDB::writeChanges()
{
    if (type == TexDBType::RTIM) // RTIM File
        writeRTIM();
    else if (type == TexDBType::TIM) // TIM File
        writeTIM();
    else
        KFMTError::error("TextureDB: Invalid type " + QString::number(type, 16));
}

void TextureDB::loadRTIM()
{
    QDataStream rtimStream(file);
    rtimStream.setByteOrder(QDataStream::LittleEndian);
    
    while (!rtimStream.atEnd())
    {        
        textures.emplace_back();
        
        if (!readCLUT(rtimStream, textures.back()))
        {
            textures.pop_back();
            break;
        }
        
        readPixelData(rtimStream, textures.back());
    }
}

void TextureDB::loadTIM()
{
    QDataStream timStream(file);
    timStream.setByteOrder(QDataStream::LittleEndian);
    
    uint32_t id;
    uint32_t flag;
    
    timStream >> id;
    if (id != 0x10)
    {
        KFMTError::error("TextureDB: TIM ID is not 0x10. Bailing out.");
        return;
    }
    
    textures.emplace_back();
    
    timStream >> flag;
    textures.back().pMode = static_cast<PixelMode>(flag & 0b111u);
    textures.back().cf = static_cast<bool>((flag >> 3u) & 1u);
    
    bool clutOk = false;
    
    if (textures.back().cf)
        clutOk = readCLUT(timStream, textures.back());
    
    if (clutOk || !textures.back().cf)
        readPixelData(timStream, textures.back());
    else
        textures.pop_back();
}

bool TextureDB::readCLUT(QDataStream & stream, Texture & targetTex)
{
    // RTIM does not have the clut size at the beginning of the header.
    if (type != TexDBType::RTIM)
        stream >> targetTex.clutSize;
    stream >> targetTex.clutVramX;
    stream >> targetTex.clutVramY;
    stream >> targetTex.clutWidth;
    stream >> targetTex.clutHeight;
    
    // For RTIM, read the clut header dupe
    if (type == TexDBType::RTIM)
    {
        uint16_t clutVramXDupe;
        uint16_t clutVramYDupe;
        uint16_t clutWidthDupe;
        uint16_t clutHeightDupe;
        stream >> clutVramXDupe;
        stream >> clutVramYDupe;
        stream >> clutWidthDupe;
        stream >> clutHeightDupe;
        
        // We check if the dupes match the original values
        if (targetTex.clutVramX != clutVramXDupe || targetTex.clutVramY != clutVramYDupe ||
            targetTex.clutWidth != clutWidthDupe || targetTex.clutHeight != clutHeightDupe)
        {
            KFMTError::error("Texture: Invalid RTIM CLUT Header: Dupes don't match.");
            return false;
        }
        
        // This next if checks whether the values on the CLUT header are all the same. This only
        // happens when we're at the weird texture section (all 00 or FF).
        if (targetTex.clutVramX == targetTex.clutVramY && targetTex.clutVramY == targetTex.clutWidth
            && targetTex.clutWidth == targetTex.clutHeight)
            return false;
    }
    
    const auto clutAmount = targetTex.clutWidth * targetTex.clutHeight;
        
    for (auto curEntry = 0; curEntry < clutAmount; curEntry++)
    {
        uint16_t clutEntry;
        stream >> clutEntry;
        
        const uint8_t r = (clutEntry & 31u) * 8;
        const uint8_t g = (static_cast<uint8_t>(clutEntry >> 5u) & 31u) * 8;
        const uint8_t b = (static_cast<uint8_t>(clutEntry >> 10u) & 31u) * 8;
        uint8_t a = clutEntry >> 15u;
        if (a == 0 && r == 0 && g == 0 && b == 0)
            a = 0;
        else if ((a == 0 && (r != 0 || g != 0 || b != 0)) || (a == 1 && r == 0 && g == 0 && b == 0))
            a = 255;
        else if (a == 1 && (r != 0 || g != 0 || b != 0))
            a = 127;
        
        const unsigned int color = b | static_cast<unsigned int>(g << 8u) | 
                static_cast<unsigned int>(r << 16u) | static_cast<unsigned int>(a << 24u);
        
        targetTex.clutColorTable.push_back(color);
    }
    
    targetTex.image.setColorTable(targetTex.clutColorTable);
    return true;
}

void TextureDB::readPixelData(QDataStream & stream, Texture & targetTex)
{
    // RTIM does not have the pixel data size at the beginning of the header.
    if (type != TexDBType::RTIM)
        stream >> targetTex.pxDataSize;
    stream >> targetTex.pxVramX;
    stream >> targetTex.pxVramY;
    stream >> targetTex.pxWidth;
    stream >> targetTex.pxHeight;
    
    // FIXME: We should check the dupes just like we do for the CLUT.
    // If this is an RTIM, skip the DX/DY and W/X dupes
    if (type == TexDBType::RTIM)
        stream.skipRawData(8);
    
    // Adjust width properly
    if (targetTex.pMode == PixelMode::CLUT4Bit)
        targetTex.pxWidth *= 4;
    else if (targetTex.pMode == PixelMode::CLUT8Bit)
        targetTex.pxWidth *= 2;
    
    // Set framebuffer coordinate
    targetTex.framebufferCoordinate.setX(targetTex.pxVramX);
    targetTex.framebufferCoordinate.setY(targetTex.pxVramY);
    
    // Initialize texture
    if (targetTex.pMode == PixelMode::CLUT4Bit || targetTex.pMode == PixelMode::CLUT8Bit)
    {
        targetTex.image = QImage(targetTex.pxWidth, targetTex.pxHeight, QImage::Format_Indexed8);
        targetTex.image.setColorTable(targetTex.clutColorTable);
    }
    else if (targetTex.pMode == PixelMode::Direct15Bit)
        targetTex.image = QImage(targetTex.pxWidth, targetTex.pxHeight, QImage::Format_RGB555);
    
    int curPixel = 0;
    
    while (curPixel < targetTex.pxWidth * targetTex.pxHeight)
    {
        uint16_t block0;
        stream >> block0;
        
        switch (targetTex.pMode)
        {
            case (PixelMode::CLUT4Bit):
            {
                const uint8_t pixel0 = block0 & 0b1111u;
                const uint8_t pixel1 = static_cast<uint8_t>(block0 >> 4u) & 0b1111u;
                const uint8_t pixel2 = static_cast<uint8_t>(block0 >> 8u) & 0b1111u;
                const uint8_t pixel3 = static_cast<uint8_t>(block0 >> 12u) & 0b1111u;
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
                const uint8_t pixel0 = block0 & 0xFFu;
                const uint8_t pixel1 = static_cast<uint8_t>(block0 >> 8u) & 0xFFu;
                targetTex.image.setPixel(curPixel % targetTex.pxWidth, curPixel / targetTex.pxWidth,
                                         pixel0);
                curPixel++;
                targetTex.image.setPixel(curPixel % targetTex.pxWidth, curPixel / targetTex.pxWidth,
                                         pixel1);
                curPixel++;
                break;
            }
            case (PixelMode::Direct15Bit):
            {
                const uint8_t r = (block0 & 31u) * 8;
                const uint8_t g = (static_cast<uint8_t>(block0 >> 5u) & 31u) * 8;
                const uint8_t b = (static_cast<uint8_t>(block0 >> 10u) & 31u) * 8;
                uint8_t a = block0 >> 15u;
                if (a == 0 && r == 0 && g == 0 && b == 0)
                    a = 0;
                else if ((a == 0 && (r != 0 || g != 0 || b != 0)) || (a == 1 && r == 0 && g == 0 && b == 0))
                    a = 255;
                else if (a == 1 && (r != 0 || g != 0 || b != 0))
                    a = 127;
                targetTex.image.setPixelColor(curPixel % targetTex.pxWidth, curPixel / targetTex.pxWidth, 
                                              QColor(r, g, b, a));
                curPixel++;
                break;
            }
            default:
                KFMTError::error("TextureDB: Unimplemented pixel mode 0x" + 
                                 QString::number(static_cast<int>(targetTex.pMode), 16));
                return;
        }
    }
}

void TextureDB::writeRTIM()
{
    QDataStream outStream(&file, QIODevice::WriteOnly);
    outStream.setByteOrder(QDataStream::LittleEndian);
    
    for (const auto &texture : textures)
    {
        writeCLUT(outStream, texture, TexDBType::RTIM);
        writePixelData(outStream, texture, TexDBType::RTIM);
    }
}

void TextureDB::writeTIM()
{
    QDataStream outStream(&file, QIODevice::WriteOnly);
    outStream.setByteOrder(QDataStream::LittleEndian);
    
    auto &texture = textures.front();
    
    uint32_t id = 0x10;
    uint32_t flag = static_cast<uint32_t>(texture.pMode) | (static_cast<uint32_t>(texture.cf) << 3u);
    
    outStream << id;
    outStream << flag;

    writeCLUT(outStream, texture, TexDBType::TIM);
    writePixelData(outStream, texture, TexDBType::TIM);
}

void TextureDB::writeCLUT(QDataStream &stream, const TextureDB::Texture &targetTex, TexDBType type)
{
    // RTIM does not have the clut size at the beginning of the header.
    if (type != TexDBType::RTIM)
        stream << targetTex.clutSize;
    stream << targetTex.clutVramX;
    stream << targetTex.clutVramY;
    stream << targetTex.clutWidth;
    stream << targetTex.clutHeight;
    
    // For RTIM, write the clut header dupe
    if (type == TexDBType::RTIM)
    {
        stream << targetTex.clutVramX;
        stream << targetTex.clutVramY;
        stream << targetTex.clutWidth;
        stream << targetTex.clutHeight;
    }
    
    for (const auto entry : targetTex.getCLUTEntries())
        stream << entry;
}

void TextureDB::writePixelData(QDataStream &stream, const TextureDB::Texture &targetTex, TexDBType type)
{
    // Adjust width before writing
    uint16_t fixedPixelWidth = targetTex.pxWidth;
    if (targetTex.pMode == PixelMode::CLUT4Bit)
        fixedPixelWidth /= 4;
    else if (targetTex.pMode == PixelMode::CLUT8Bit)
        fixedPixelWidth /= 2;
    
    // RTIM does not have the pixel data size at the beginning of the header.
    if (type != TexDBType::RTIM)
        stream << targetTex.pxDataSize;
    stream << targetTex.pxVramX;
    stream << targetTex.pxVramY;
    stream << fixedPixelWidth;
    stream << targetTex.pxHeight;
    
    // For RTIM, write the pixel data header dupe
    if (type == TexDBType::RTIM)
    {
        stream << targetTex.pxVramX;
        stream << targetTex.pxVramY;
        stream << fixedPixelWidth;
        stream << targetTex.pxHeight;
    }
    
    auto *imageByteData = targetTex.image.bits();
    auto imagePixelSize = targetTex.image.width() * targetTex.image.height();
    auto imageCurPixel = 0;
    
    while (imageCurPixel < imagePixelSize)
    {
        switch (targetTex.pMode)
        {
            case (PixelMode::CLUT4Bit):
            {
                const uint8_t px0 = imageByteData[imageCurPixel] & 15u;
                const uint8_t px1 = imageByteData[imageCurPixel + 1] & 15u;
                const uint8_t px2 = imageByteData[imageCurPixel + 2] & 15u;
                const uint8_t px3 = imageByteData[imageCurPixel + 3] & 15u;
                
                const uint16_t packet = px0 | static_cast<uint16_t>(px1 << 4u) | 
                        static_cast<uint16_t>(px2 << 8u) | static_cast<uint16_t>(px3 << 12u);
                
                stream << packet;
                
                imageCurPixel += 4;
                break;
            }
            case (PixelMode::CLUT8Bit):
            {
                stream << imageByteData[imageCurPixel];
                stream << imageByteData[imageCurPixel + 1];
                imageCurPixel += 2;
                break;
            }
            case (PixelMode::Direct15Bit):
            {
                const auto pxColor = targetTex.image.pixelColor(imageCurPixel % targetTex.pxWidth,
                                                                imageCurPixel / targetTex.pxWidth);
                // FIXME: Figure this out, too sleepy to do it right now.
                uint8_t true_a = 0;
                const uint8_t r = std::min(pxColor.red() / 8u, 31u);
                const uint8_t g = std::min(pxColor.green() / 8u, 31u);
                const uint8_t b = std::min(pxColor.blue() / 8u, 31u);
                
                if (pxColor.alpha() == 127)
                    true_a = 1u;
                else if (pxColor.alpha() == 255)
                {
                    if ((r != 0 || g != 0 || b != 0))
                        true_a = 0u;
                    else if (r == 0 && g == 0 && b == 0)
                        true_a = 1u;
                }
                
                const uint16_t packet = r | (g << 5u) | (b << 10u) | (true_a << 15u);
                stream << packet;
                imageCurPixel++;
                break;
            }
            default:
                KFMTError::fatalError("Texture: Unhandled pixel mode!");
                return;
        }
    }
}

std::vector<uint16_t> TextureDB::Texture::getCLUTEntries() const
{
    std::vector<uint16_t> result;
    if (pMode != PixelMode::CLUT4Bit && pMode != PixelMode::CLUT8Bit)
    {
        KFMTError::error("TextureDB: Tried to get CLUT entries when pixel mode isn't a CLUT mode.");
        return {};
    }
    result.reserve(clutWidth * clutHeight);
    
    for (const auto &color : image.colorTable())
    {
        uint8_t r = (color >> 16u) & 0xFFu;
        uint8_t g = (color >> 8u) & 0xFFu;
        uint8_t b = color & 0xFFu;
        uint8_t a = (color >> 24u) & 0xFFu;
        if ((a == 0 && r == 0 && g == 0 && b == 0) || (a == 255u && (r != 0 || g != 0 || b != 0)))
            a = 0u;
        else if (a == 127u || (a == 255u && r == 0 && g == 0 && b == 0))
            a = 1u;
        
        r /= 8u;
        g /= 8u;
        b /= 8u;
        
        result.push_back(r | ((g & 31u) << 5u) | ((b & 31u) << 10u) | ((a & 1u) << 15u)) ;
    }
    
    return result;
}
