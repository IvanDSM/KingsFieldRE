#include "text.h"

QString KF2::TextConversion::from(const char* kf2String, int length)
{
    QString result;
    result.resize(length);

    for (int i = 0; i < length; i++)
    {
        switch (kf2String[i])
        {
            case 0x0: result[i] = 'A'; break;
            case 0x1: result[i] = 'B'; break;
            case 0x2: result[i] = 'C'; break;
            case 0x3: result[i] = 'D'; break;
            case 0x4: result[i] = 'E'; break;
            case 0x5: result[i] = 'F'; break;
            case 0x6: result[i] = 'G'; break;
            case 0x7: result[i] = 'H'; break;
            case 0x8: result[i] = 'I'; break;
            case 0x9: result[i] = 'J'; break;
            case 0xa: result[i] = 'K'; break;
            case 0xb: result[i] = 'L'; break;
            case 0xc: result[i] = 'M'; break;
            case 0xd: result[i] = 'N'; break;
            case 0xe: result[i] = 'O'; break;
            case 0xf: result[i] = 'P'; break;
            case 0x10: result[i] = 'Q'; break;
            case 0x11: result[i] = 'R'; break;
            case 0x12: result[i] = 'S'; break;
            case 0x13: result[i] = 'T'; break;
            case 0x14: result[i] = 'U'; break;
            case 0x15: result[i] = 'V'; break;
            case 0x16: result[i] = 'W'; break;
            case 0x17: result[i] = 'X'; break;
            case 0x18: result[i] = 'Y'; break;
            case 0x19: result[i] = 'Z'; break;
            case 0x20: result[i] = '0'; break;
            case 0x21: result[i] = '1'; break;
            case 0x22: result[i] = '2'; break;
            case 0x23: result[i] = '3'; break;
            case 0x24: result[i] = '4'; break;
            case 0x25: result[i] = '5'; break;
            case 0x26: result[i] = '6'; break;
            case 0x27: result[i] = '7'; break;
            case 0x28: result[i] = '8'; break;
            case 0x29: result[i] = '9'; break;
            case 0x30: result[i] = '.'; break;
            case 0x31: result[i] = ','; break;
            case 0x32: result[i] = '\''; break;
            case 0x33: result[i] = '-'; break;
            case 0x34: result[i] = '='; break;
            case 0x35: result[i] = '/'; break;
            case 0x36: result[i] = '*'; break;
            case 0x37: result[i] = '#'; break;
            case 0x38: result[i] = '!'; break;
            case 0x39: result[i] = L'•'; break;
            case 0x3a: result[i] = '?'; break;
            case 0x7f: result[i] = ' '; break;
            case static_cast<char>(0xffu):
                result[i] = '\0';
                result.resize(i);
                i = length; // Leave the loop
                break;

            default: break;
        }
    }

    return result;
}

QByteArray KF2::TextConversion::to(const QString& qString)
{
    QByteArray result;
    result.resize(qString.size());

    for (int i = 0; i < result.size(); i++)
    {
        switch (qString[i].unicode())
        {
            case 'A': result[i] = 0x0; break;
            case 'B': result[i] = 0x1; break;
            case 'C': result[i] = 0x2; break;
            case 'D': result[i] = 0x3; break;
            case 'E': result[i] = 0x4; break;
            case 'F': result[i] = 0x5; break;
            case 'G': result[i] = 0x6; break;
            case 'H': result[i] = 0x7; break;
            case 'I': result[i] = 0x8; break;
            case 'J': result[i] = 0x9; break;
            case 'K': result[i] = 0xa; break;
            case 'L': result[i] = 0xb; break;
            case 'M': result[i] = 0xc; break;
            case 'N': result[i] = 0xd; break;
            case 'O': result[i] = 0xe; break;
            case 'P': result[i] = 0xf; break;
            case 'Q': result[i] = 0x10; break;
            case 'R': result[i] = 0x11; break;
            case 'S': result[i] = 0x12; break;
            case 'T': result[i] = 0x13; break;
            case 'U': result[i] = 0x14; break;
            case 'V': result[i] = 0x15; break;
            case 'W': result[i] = 0x16; break;
            case 'X': result[i] = 0x17; break;
            case 'Y': result[i] = 0x18; break;
            case 'Z': result[i] = 0x19; break;
            case '0': result[i] = 0x20; break;
            case '1': result[i] = 0x21; break;
            case '2': result[i] = 0x22; break;
            case '3': result[i] = 0x23; break;
            case '4': result[i] = 0x24; break;
            case '5': result[i] = 0x25; break;
            case '6': result[i] = 0x26; break;
            case '7': result[i] = 0x27; break;
            case '8': result[i] = 0x28; break;
            case '9': result[i] = 0x29; break;
            case '.': result[i] = 0x30; break;
            case ',': result[i] = 0x31; break;
            case '\'': result[i] = 0x32; break;
            case '-': result[i] = 0x33; break;
            case '=': result[i] = 0x34; break;
            case '/': result[i] = 0x35; break;
            case '*': result[i] = 0x36; break;
            case '#': result[i] = 0x37; break;
            case '!': result[i] = 0x38; break;
            case L'•': result[i] = 0x39; break;
            case '?': result[i] = 0x3a; break;
            case ' ': result[i] = 0x7f; break;
            case '\0':
                result[i] = static_cast<char>(0xffu);
                result.resize(i);
                i = result.size(); // Leave the loop
                break;
            default: break;
        }
    }

    return result;
}
