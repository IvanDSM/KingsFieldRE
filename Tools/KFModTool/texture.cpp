#include "kfmterror.h"
#include "texture.h"

Texture::Texture(TFile & tFile, unsigned int index, QString name)
{
    auto file = tFile.getFile(index);
    
    if (TFile::isTIM(file))
        loadTIM(file);
    else if (TFile::isRTIM(file))
        loadRTIM(file);
}

void Texture::loadRTIM(const QByteArray &file)
{
    
}

void Texture::loadTIM(const QByteArray &file)
{
    QDataStream timStream(file);
    timStream.setByteOrder(QDataStream::LittleEndian);
    
    quint32 id;
    quint32 flag;
    
    timStream >> id;
    if (id != 0x10)
    {
        KFMTError::error("Texture: TIM ID is not 0x10. Bailing out.");
        return;
    }
    
    timStream >> flag;
    pMode = static_cast<PixelMode>(flag & 0b111);
    cf = static_cast<bool>((flag >> 3) & 1);
    
    if (cf)
    {
        quint32 clutSize;
        quint16 dx, dy;
        quint16 w, h;
        
        timStream >> clutSize;
        timStream >> dx;
        timStream >> dy;
        timStream >> w;
        timStream >> h;
        
        clut.reset(new CLUT(clutSize, dx, dy, w, h, pMode));
        
        // Compensate for header length on the CLUT size so we can use it as a counter
        clutSize -= 12;
        
        while (clutSize > 0)
        {
            quint16 clutEntry;
            timStream >> clutEntry;
            clut->addColor(clutEntry);
            clutSize -= 2;
        }
    }
    
    quint32 pixelDataSize;
    quint16 dx, dy;
    quint16 w, h;
    
    timStream >> pixelDataSize;
    timStream >> dx;
    timStream >> dy;
    timStream >> w;
    timStream >> h;
    
    // Adjust width properly
    if (pMode == PixelMode::CLUT4Bit)
        w = w * 4;
    else if (pMode == PixelMode::CLUT8Bit)
        w = w * 2;
    
    // Set framebuffer coordinate
    framebufferCoordinate.setX(dx);
    framebufferCoordinate.setY(dy);
    
    // Set texture size
    texture = QImage(w, h, QImage::Format_RGB555);
    
    // Compensate for header lenght on the pixel data size so we can use it as a counter
    pixelDataSize -= 12;
    int curPixel = 0;
    
    while (pixelDataSize > 0)
    {
        quint16 block0;
        timStream >> block0;
        pixelDataSize -= 2;
        
        switch (pMode)
        {
            case (PixelMode::CLUT4Bit):
            {
                quint8 pixel0 = block0 & 0b1111;
                quint8 pixel1 = (block0 >> 4) & 0b1111;
                quint8 pixel2 = (block0 >> 8) & 0b1111;
                quint8 pixel3 = (block0 >> 12) & 0b1111;
                texture.setPixelColor(curPixel % texture.size().width(), 
                                      curPixel / texture.size().width(), 
                                      clut->getColor(pixel0));
                curPixel++;
                texture.setPixelColor(curPixel % texture.size().width(), 
                                      curPixel / texture.size().width(), 
                                      clut->getColor(pixel1));
                curPixel++;
                texture.setPixelColor(curPixel % texture.size().width(), 
                                      curPixel / texture.size().width(), 
                                      clut->getColor(pixel2));
                curPixel++;
                texture.setPixelColor(curPixel % texture.size().width(), 
                                      curPixel / texture.size().width(), 
                                      clut->getColor(pixel3));
                curPixel++;
                break;
            }
            case (PixelMode::CLUT8Bit):
            {
                quint8 pixel0 = block0 & 0xFF;
                quint8 pixel1 = (block0 >> 8) & 0xFF;
                texture.setPixelColor(curPixel % texture.size().width(), 
                                      curPixel / texture.size().width(), 
                                      clut->getColor(pixel0));
                curPixel++;
                texture.setPixelColor(curPixel % texture.size().width(), 
                                      curPixel / texture.size().width(), 
                                      clut->getColor(pixel1));
                curPixel++;
                break;
            }
            default:
                KFMTError::error("Texture: Unimplemented pixel mode 0x" + 
                                 QString::number(static_cast<int>(pMode), 16));
                return;
        }
    }
}
