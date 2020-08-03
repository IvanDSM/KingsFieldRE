#ifndef UTILITIES_H
#define UTILITIES_H

#include <QtGlobal>

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
        return static_cast<short>(qMax(static_cast<T>(-32768), qMin(static_cast<T>(32767), value)));
    }

    template<class T>
    quint16 clampToUShort(T value)
    {
        return static_cast<quint16>(qMin(static_cast<T>(0xFFFF), value));
    }
}
#endif // UTILITIES_H
