#ifndef ICONS_H
#define ICONS_H

#include <QIcon>
/*!
 * Namespace for icons used by multiple different places.
 * This is a memory saving measure, and unfortunately it has to be done this way due to limitations
 * with how QIcon works. This might be overengineering, but for it pleases the speed freak part of
 * my brain.
 */
namespace Icons
{
extern QIcon container;
extern QIcon gameDb;
extern QIcon gameExe;
extern QIcon map;
extern QIcon model;
extern QIcon textureDb;
extern QIcon unknown;

void init();
} // namespace Icons

#endif // ICONS_H
