#include "core/icons.h"

namespace Icons
{
QIcon container;
QIcon gameDb;
QIcon gameExe;
QIcon map;
QIcon model;
QIcon textureDb;
QIcon unknown;

void init()
{
    container = QIcon(QStringLiteral(":/icons/tfile_icon.png"));
    gameDb = QIcon(QStringLiteral(":/icons/db_icon.png"));
    gameExe = QIcon(QStringLiteral(":/icons/gameexe_icon.png"));
    map = QIcon(QStringLiteral(":/icons/map_icon.png"));
    model = QIcon(QStringLiteral(":/icons/3d_icon.png"));
    textureDb = QIcon(QStringLiteral(":/icons/tex_icon.png"));
    unknown = QIcon(QStringLiteral(":/icons/unk_icon.png"));
}

} // namespace Icons
