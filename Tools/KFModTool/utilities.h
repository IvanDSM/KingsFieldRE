#ifndef UTILITIES_H
#define UTILITIES_H

#include <QtGlobal>
#include <QByteArray>

namespace Utilities
{
    template<class T>
    quint8 clampToByte(T value)
    {
        return static_cast<quint8>(qMin(static_cast<T>(0xFF), value));
    }

    template<class T>
    short clampToShort(T value)
    {
        return static_cast<short>(qMax(static_cast<T>(-32767), qMin(static_cast<T>(32767), value)));
    }

    template<class T>
    quint16 clampToUShort(T value)
    {
        return static_cast<quint16>(qMin(static_cast<T>(0xFFFF), value));
    }
    
    inline bool fileIsGameDB(const QByteArray &file)
    {
        if (file.mid(4, 6).compare(QByteArray::fromHex("4010FF000000")) != 0)
            return false;
        
        if (file.mid(20, 14).compare(QByteArray::fromHex("00000000000000004010FF000000")) != 0)
            return false;
        
        return true;
    }
    
    /*!
     * \brief Checks whether a file is the first file of a map.
     * This is done in a very naive manner that checks if the first 4 bytes of the file are equal to
     * {0x00, 0xFA, 0x00, 0x00}. FIXME: We can probably do a better heuristic for this.
     * \param file File to check.
     * \return Whether the file is the first file of a map.
     */
    inline bool fileIsMAP1(const QByteArray &file)
    {
        return file.left(4).compare(QByteArray::fromHex("00FA0000")) == 0;
    }
    
    /*!
     * \brief Checks whether a file is the second file of a map.
     * This is done in a very naive manner that checks if the first 4 bytes of the file are equal to
     * {0xC0 0x32 0x00 0x00}. FIXME: We can probably do a better heuristic for this.
     * \param file File to check.
     * \return Whether the file is the second file of a map.
     */
    inline bool fileIsMAP2(const QByteArray &file)
    {
        return file.left(4).compare(QByteArray::fromHex("C0320000")) == 0;
    }
    
    /*!
     * \brief Checks whether a file is the third file of a map.
     * This is done by assuming that we have a table of 32 pointers at the start of the file,
     * as a third map file would. We then check if the most significant byte in all of them is 0x80.
     * If so, this is a third map file.
     * \param file File to check
     * \return Whether the file is the third file of a map.
     */
    inline bool fileIsMAP3(const QByteArray &file)
    {
        return file.at(0x03) == '\x80' && file.at(0x07) == file.at(0x0b)
               && file.at(0x0b) == file.at(0x0f) && file.at(0x13) == file.at(0x17)
               && file.at(0x17) == file.at(0x1b) && file.at(0x1b) == file.at(0x1f)
            /*&& file.at(0x23) == file.at(0x27) && file.at(0x27) == file.at(0x2b)
               && file.at(0x2b) == file.at(0x2f) && file.at(0x33) == file.at(0x37)
               && file.at(0x37) == file.at(0x3b) && file.at(0x3b) == file.at(0x3f)
               && file.at(0x43) == file.at(0x47) && file.at(0x47) == file.at(0x4b)
               && file.at(0x4b) == file.at(0x4f) && file.at(0x53) == file.at(0x57)
               && file.at(0x57) == file.at(0x5b) && file.at(0x5b) == file.at(0x5f)
               && file.at(0x63) == file.at(0x67) && file.at(0x67) == file.at(0x6b)
               && file.at(0x6b) == file.at(0x6f) && file.at(0x73) == file.at(0x77)
               && file.at(0x77) == file.at(0x7b) && file.at(0x7b) == file.at(0x7f)*/
            ;
    }
    
    /*!
     * \brief Checks whether a file is a MO file.
     * This is done by checking if the unsigned int at offset 0x08 in the file points to a section 
     * in the file with the TMD ID (0x41).
     * \param file File to check.
     * \return Whether the file is a MO file.
     */
    inline bool fileIsMO(const QByteArray &file)
    {
        quint32 tmdOff = *reinterpret_cast<quint32 *>(file.mid(8,4).data());
        quint8 tmdSig = 0;
        if (tmdOff < static_cast<quint32>(file.size()))
            tmdSig = file.at(tmdOff);
        
        return tmdSig == 0x41;
    }
    
    /*!
     * \brief Checks whether a file is an RTMD file.
     * This is done by checking if the file starts with 4 zero bytes and is the followed by either 
     * 0x12 (4 byte long) or 0x10 (4 byte long).
     * \param file File to check.
     * \return Whether the file is an RTMD file.
     */
    inline bool fileIsRTMD(const QByteArray &file)
    {
        return file.left(4).compare(QByteArray::fromHex("00000000")) == 0 &&
                         (file.mid(4, 4).compare(QByteArray::fromHex("12000000")) == 0 ||
                          file.mid(4, 4).compare(QByteArray::fromHex("10000000")) == 0);
    }

    /*!
     * \brief Checks whether a file is an RTIM file (should only be run after checking for TIM).
     * This is done by checking if the file's first 8 bytes are equal to the next 8 bytes.
     * We also make sure the first 4 bytes aren't equal to the next 4 bytes. This is necessary to
     * avoid false positives in the AC proto.
     * \param file File to check.
     * \return Whether the file is an RTIM file.
     */
    inline bool fileIsRTIM(const QByteArray &file)
    {
        return file.mid(8).left(8) == file.left(8) && file.mid(4).left(4) != file.left(4);
    }
    
    /*!
     * \brief Checks whether a file is a SEQ file.
     * This is done by checking if the file's first 4 bytes are equal to the 
     * little-endian string "SEQp".
     * \param file File to check.
     * \return Whether the file is a SEQ file.
     */
    inline bool fileIsSEQ(const QByteArray &file)
    {
        return file.left(4).compare(QByteArray::fromHex("70514553")) == 0;
    }
    
    /*!
     * \brief Checks whether a file is an TIM file.
     * This is done by checking if the file's first 4 bytes as an unsigned int is 
     * equal to the TMD ID (0x10).
     * \param file File to check.
     * \return Whether the file is an TIM file.
     */
    inline bool fileIsTIM(const QByteArray &file)
    {
        return file.left(4).compare(QByteArray::fromHex("10000000")) == 0 && 
               file.at(4) > 0 && file.at(4) <= 15 &&
               file.mid(5, 3).compare(QByteArray::fromHex("000000")) == 0;
    }
    
    /*!
     * \brief Checks whether a file is a TMD file.
     * This is done by checking if the file's bytes 0 - 3 as an unsigned int are 
     * equal to the TMD ID (0x41) and if the file's bytes 4-7 as an unsigned int
     * are equal to 0 or 1, which are valid values for the FIXP field.
     * \param file File to check.
     * \return Whether the file is a TMD file.
     */
    inline bool fileIsTMD(const QByteArray &file)
    {
        // FIXME: This is janky. I'm only doing this because I'm really tired.
        return file.left(8).compare(QByteArray::fromHex("4100000000000000")) == 0 ||
               file.left(8).compare(QByteArray::fromHex("4100000001000000")) == 0;
    }
    
    /*!
     * \brief Checks whether a file is a VB file.
     * This is done by checking if the file's first 16 bytes are zero.
     * FIXME: This is some really shitty detection.
     * \param file File to check.
     * \return Whether the file is a VB file.
     */
    inline bool fileIsVB(const QByteArray &file)
    {
        return file.left(16).compare(QByteArray::fromHex("00000000000000000000000000000000")) == 0;
    }
    
    /*!
     * \brief Checks whether a file is a VH file.
     * This is done by checking if the file's first 4 bytes are equal to the 
     * little-endian string "VABp".
     * \param file File to check.
     * \return Whether the file is a VH file.
     */
    inline bool fileIsVH(const QByteArray &file)
    {
        return file.left(4).compare(QByteArray::fromHex("70424156")) == 0;
    }
}
#endif // UTILITIES_H
