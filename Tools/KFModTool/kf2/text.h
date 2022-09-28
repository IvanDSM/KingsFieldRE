#ifndef KF2_TEXT_H
#define KF2_TEXT_H

#include <cstdint>
#include <QString>

namespace KF2
{

    // Structs

    struct String
    {
        char str[24];
    } __attribute__((packed, aligned(1)));

    struct LongString
    {
        char str[308];
    } __attribute__((packed, aligned(1)));

    struct PosString
    {
        short X;
        short Y;
        char str[24];
    } __attribute__((packed, aligned(1)));

    namespace TextConversion
    {
        /*!
         * \brief Converts a string from KF2 format to a unicode QString.
         * \param kf2String Pointer to the KF2 string.
         * \param length Length of the KF2 string.
         * \return Unicode QString.
         */
        QString from(const char* kf2String, int length);

        /*!
         * \brief Converts a unicode QString to KF2 format.
         * \param qString Unicode QString to convert.
         * \return KF2 format string.
         */
        QByteArray to(const QString& qString);
    }
}

#endif // KF2_TEXT_H
