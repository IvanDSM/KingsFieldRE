#ifndef PRETTYNAMES_H
#define PRETTYNAMES_H
#include <QDir>
#include <QHash>

namespace PrettyNames
{
extern const QHash<const QString, QString> prettyKF2;

inline const QString& kf2(const QString& filePath)
{
    const auto iterator = prettyKF2.find(filePath.mid(filePath.lastIndexOf(QDir::separator()) + 1));
    return iterator == prettyKF2.end() ? filePath : *iterator;
}
} // namespace PrettyNames
#endif // PRETTYNAMES_H
